#include "GroupeManager.h"
#include "Meeting.h"

/*!
 * \brief GroupeManager::obtenirGroupeParNom permet d'obtenir un groupe à partir de son nom
 * \param _nom le nom du groupe recherché
 * \return un pointeur sur le groupe trouvé, null sinon
 */
Groupe* GroupeManager::obtenirGroupeParNom(QString _nom)
{
    for(int i=0; i<groupes.size(); i++)
    {
        if(groupes[i].obtenirNom() == _nom)
            return &groupes[i];
    }
    return 0;
}
/*!
 * \brief GroupeManager::obtenirGroupeParId permet d'obtenir un groupe à partir de son id
 * \param _id l'id du groupe recherché
 * \return un pointeur sur le groupe trouvé, null sinon
 */
Groupe* GroupeManager::obtenirGroupeParId(int _id)
{
    for(int i=0; i<groupes.size(); i++)
    {
        if(groupes[i].obtenirId() == _id)
            return &groupes[i];
    }
    return 0;
}
/*!
 * \brief GroupeManager::obtenirProcId fournit une id non encore utilisé par un groupe
 * \return une id libre
 */
int GroupeManager::obtenirProcId()
{
    int id=0;
    //Tant qu'aucun créneau n'est libre, on incrémente
    while(idExiste(id))
        id++;
    return id;
}
/*!
 * \brief GroupeManager::ajouterGroupe crée un groupe et l'ajoute à la liste
 * \param _nom le nom du groupe à ajouter
 */
void GroupeManager::ajouterGroupe(QString _nom)
{
    //Si le groupe n'existe pas
    if(obtenirGroupeParNom(_nom))
        throw 1;
    //On le crée
    groupes.append(Groupe( _nom));
    //Et on initialise ses interets à 0
    initInterets(&groupes.last());
    emit listeGroupeAjout(groupes.last().obtenirNom());
}
/*!
 * \brief GroupeManager::ajouterGroupe crée un groupe et l'ajoute à la liste
 * \param _nom le nom du groupe à ajouter
 * \param _id l'id du groupe à ajouter, si cet id existe déjà, le groupe n'est pas crée et une erreur de valeur 1 est déclenchée
 */
void GroupeManager::ajouterGroupe(QString _nom, int _id)
{
    //Si le groupe n'existe pas
    if(obtenirGroupeParNom(_nom))
        throw 1;
    //On le crée
    groupes.append(Groupe( _nom, _id));
    //Et on initialise ses interets à 0
    initInterets(&groupes.last());
    emit listeGroupeAjout(groupes.last().obtenirNom());
}
/*!
 * \brief GroupeManager::definirInteret définit l'interet entre deux groupe
 * \param _g1 le groupe acteur de l'interet
 * \param _g2 le groupe objet de l'interet
 * \param _interet la valeur de l'interet
 */
void GroupeManager::definirInteret (const Groupe* _g1, const Groupe* _g2, unsigned int _interet)
{
    matriceInteret.definirInteret(_g1, _g2, _interet);
}
void GroupeManager::print()
{
    qDebug() << "Liste de groupes : ";
    for(int i=0; i<groupes.size(); i++)
    {
        qDebug() << groupes[i].obtenirNom();
    }

    qDebug() << "Matrice d'interet : ";
    QMap<const Groupe*, QMap<const Groupe*, int>>::iterator i;
    QMap<const Groupe*, int>::iterator j;

    for(i=matriceInteret.obtenirMatrice().begin(); i!= matriceInteret.obtenirMatrice().end(); ++i)
    {
        qDebug() << "Pour le groupe : " << i.key()->obtenirId();
        for(j=i.value().begin(); j!= i.value().end(); ++j)
        {
            qDebug() << j.key()->obtenirId() << " = " << j.value();
        }
    }

}
/*!
 * \brief GroupeManager::obtenirListeInteretIds retourne les interet qu'un groupe trouve chez les les autres
 * \param _groupe
 * \return une map avec en indice l'id des groupes et en valeur l'interet
 */
QMap<int, int> GroupeManager::obtenirListeInteretIds (const Groupe *_groupe)const
{
    return matriceInteret.obtenirInteretsId(_groupe);
}
/*!
 * \brief GroupeManager::idExiste vérifie si un id existe
 * \param _id la valeur de l'id à tester
 * \return booléen indiquant la réponse
 */
bool GroupeManager::idExiste(int _id)
{
    if(obtenirGroupeParId(_id)!=0)
        return true;
    return false;
}
/*!
 * \brief GroupeManager::initInterets remet tous les interets de et pour un groupe à zéro
 * Est appelée à la création d'un groupe
 * \param _groupeAInit pointeur sur le groupe à initialiser
 */
void GroupeManager::initInterets(const Groupe* _groupeAInit)
{
    //On indique que pour le groupe à initialiser, chaque groupe a un interet nul
    for(int i=0; i<groupes.size(); i++)
    {
        matriceInteret.definirInteret(_groupeAInit, &groupes[i],0);
    }
    //Pour chaque groupe existant, on indique que le groupe à initialiser a un interet nul
    for(int i=0; i<groupes.size(); i++)
    {
        matriceInteret.definirInteret(&groupes[i],_groupeAInit, 0);
    }
}
/*!
 * \brief GroupeManager::retirerGroupe retire un groupe et le supprime
 * \param _groupe un pointeur vers le groupe à éliminer
 */
void GroupeManager::retirerGroupe (Groupe* _groupe)
{
    //retrait de la matrice
    matriceInteret.retirerGroupe(_groupe);

    //Retrait de l'appartenance des individus
    for(int i=0; i<Meeting::obtenirenirInstance().obtenirIndividus().size(); i++)
    {
        Meeting::obtenirenirInstance().obtenirIndividus()[i].retirerGroupe(_groupe);
    }
    //Envoi du signal de retrait pour l'ui
    emit listeGroupeRetrait(_groupe->obtenirNom());
    //Retrait de la liste
    groupes.removeAll(*_groupe);
}
/*!
 * \brief GroupeManager::obtenirInteret donne l'interet d'un groupe pour l'autre
 * \param _groupe1 le groupe sujet
 * \param _groupe2 le groupe objet
 * \return un entier positif ou nul de valeur l'interet
 */
int GroupeManager::obtenirInteret (const Groupe *_groupe1, const Groupe *_groupe2)
{
    if(matriceInteret.obtenirMatrice().contains(_groupe1) && matriceInteret.obtenirMatrice()[_groupe1].contains(_groupe2))
        return matriceInteret.obtenirMatrice()[_groupe1][_groupe2];
    return 0;
}
/*!
 * \brief GroupeManager::definirMatriceInteret construit la matrice d'interet
 * \param _matriceIds un double mappage dans lequel les groupes sont identifiés par leur id
 */
void GroupeManager::definirMatriceInteret(QMap<int, QMap<int, int>>& _matriceIds)
{
    QMap<int, QMap<int, int>>::iterator i;
    QMap<int, int>::iterator j;
    Groupe* groupe;

    //On parcourt la première map
    for(i=_matriceIds.begin(); i!= _matriceIds.end(); ++i)
    {
        //Pour chaque id, on récupère le groupe associé
        groupe=obtenirGroupeParId(i.key());
        for(j=i.value().begin(); j!= i.value().end(); ++j)
        {
            //On définit les interet un à un
            matriceInteret.obtenirMatrice()[groupe][obtenirGroupeParId(j.key())] = j.value();
        }
    }
}
/*!
 * \brief GroupeManager::vider remet à zéro le groupe manager en supprimant tours les groupes et vidant la matrice d'interet
 */
void GroupeManager::vider()
{
    matriceInteret.obtenirMatrice().clear();
    groupes.clear();
}
