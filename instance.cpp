#include "instance.h"

Instance::Instance(QObject *parent) : QObject(parent)
{
    nombreTours=0;

}
/*!
 * \brief Instance::obtenirIndividus retourne la liste des personnes concernées par le problème
 * \return Une réference sur la Qlist d'individus
 */
QList<Individu> &Instance::obtenirIndividus()
{
    return participants;
}
/*!
 * \brief Instance::ajoutIndividu ajoute un individu au problème
 * \param _nom le nom du bonhomme à ajouter
 * \param _groupes une liste de noms des groupes auxquels il appartient
 */
void Instance::ajoutIndividu(QString _nom, QList<QString> _groupes)
{
    participants.append(Individu(_nom, obtenirIndividuId()));
    for(int i =0; i<_groupes.size(); i++)
    {
        Groupe* nouveauGroupe = groupes.obtenirGroupeParNom(_groupes[i]);
        if(nouveauGroupe)
            participants.last().ajouterGroupe(nouveauGroupe);
    }
    //On signale l'ajout
    emit individuCree(participants.last().obtenirNom(), participants.last().obtenirId());
}
/*!
 * \brief Instance::ajoutIndividu ajoute un individu au problème
 * \param _nom le nom de la personne
 * \param _id son id, si un autre individu a déjà la même id, on lance une erreur de valeur 1, elle n'est pas ratrappée ici
 * \param _groupes  une liste des ids des groupes auxquels appartient le bonhomme si l'un d'eux n'existe pas, on l'ignore
 */
void Instance::ajoutIndividu(QString _nom, int _id, QList<int> &_groupes)
{
     participants.append(Individu(_nom, _id));
     for(int i =0; i<_groupes.size(); i++)
     {
         Groupe* nouveauGroupe = groupes.obtenirGroupeParId(_groupes[i]);
         if(nouveauGroupe)
             participants.last().ajouterGroupe(nouveauGroupe);
     }
     //On signale l'ajout
     emit individuCree(participants.last().obtenirNom(), participants.last().obtenirId());
}
/*!
 * \brief Instance::supprimerIndividu supprime un individu
 * \param _id l'id de la personne a supprimer
 */
void Instance::supprimerIndividu(int _id)
{
    //On commence par supprimer la solution
    emit supprimerSolution();

    //Puis l'on supprime
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtenirId() == _id)
            participants.removeAt(i);
    }
    //On signale la supression
    emit individuSupprime(_id);
}
/*!
 * \brief Instance::obtenirIndividuId retourne un id libre pour les individus
 * \return le plus petit id libre
 */
int Instance::obtenirIndividuId()
{
    int id=0;
    while(idIndividuExiste(id))
        id++;
    return id;
}
/*!
 * \brief Instance::idIndividuExiste indique si l'id est déjà utilisé par un individu
 * \param _id l'id à tester
 * \return un booléen
 */
bool Instance::idIndividuExiste(int _id)
{
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtenirId()==_id)
            return true;
    }
    return false;
}
/*!
 * \brief Instance::obtenirIndividuParId retrouve un individu à partir de son id
 * \param _id l'id à chercher
 * \return un pointeur sur l'individu, null si il n'existe pas
 */
Individu *Instance::obtenirIndividuParId(int _id)
{
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtenirId()==_id)
            return &participants[i];
    }
    return NULL;
}
/*!
 * \brief Instance::modifierIndividu modifie un individu
 * \param _idn l'id de l'individu à modifier
 * \param _nom le nouveau nom à lui donner
 * \param _groupes la liste des ids des groupes à lui attribuer
 */
void Instance::modifierIndividu(int _id, QString _nom, QList<int> _groupes)
{
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtenirId()==_id)
        {
            //On remplace son nom
            participants[i].definirNom(_nom);
            //On retire tous ses groupes
            participants[i].retirerGroupes();
            //Et on ajoute ceux dont les ids ont été indiqués
            for(int i =0; i<_groupes.size(); i++)
            {
                Groupe* nouveauGroupe = groupes.obtenirGroupeParId(_groupes[i]);
                if(nouveauGroupe)
                    participants[i].ajouterGroupe(nouveauGroupe);
            }
        }
    }
}
/*!
 * \brief Instance::ajoutTable ajoute une table au problème
 * \param _label le nom de la table
 * \param _capacite la capacité de la table
 * \param _id l'id de la table si cet id est déjà utilisé, l'erreur lancée par la création n'est pas ratrapée ici
 */
void Instance::ajoutTable(QString _label, int _capacite, int _id)
{
    tables.append(Table(_label, _capacite, _id));
    //On signale la création
    emit tableCree(_label, _id, _capacite);
}
/*!
 * \brief Instance::ajoutTable ajoute une table au problème
 * \param _capacite la capacité de la table
 */
void Instance::ajoutTable(int _capacite)
{
    tables.append(Table("Table n° " + QString::number(obtenirTableId()), _capacite));
    emit tableCree(tables.last().obtenirLabel(), tables.last().obtenirId(), tables.last().obtenirNombreDePlaces());
}
/*!
 * \brief Instance::ajoutTables ajoute des table au problème
 * \param _nombre le nombre de tables a créer
 * \param _capacite leur capacité
 */
void Instance::ajoutTables(int _nombre, int _capacite)
{
    for(int i=0; i<_nombre; i++)
        ajoutTable(_capacite);

}
/*!
 * \brief Instance::supprimerTable supprime une table
 * \param _id l'id de la table à supprimer
 */
void Instance::supprimerTable(int _id)
{
    //On commence par supprimer la solution
    emit supprimerSolution();
    int index=-1;
    for(int i =0; i<tables.size(); i++)
    {
        if(tables[i].obtenirId()==_id)
            index=i;
    }
    emit tableSupprimee(tables.at(index).obtenirId());
    tables.removeAt(index);
}
/*!
 * \brief Instance::obtenirTableId fournit un id libre pour les tables
 * \return le plus petit id non encore occupé par une table
 */
int Instance::obtenirTableId()
{
    int id=0;
    while(idTableExiste(id))
        id++;
    return id;
}
/*!
 * \brief Instance::idTableExiste indique si un id est occupé par une table
 * \param _id l'id à tester
 * \return un booléen
 */
bool Instance::idTableExiste(int _id)
{
    for(int i =0; i<tables.size(); i++)
    {
        if(tables[i].obtenirId()==_id)
            return true;
    }
    return false;
}
/*!
 * \brief Instance::obtenirTableParId trouve une table à partir de son id
 * \param _id l'id de la table à trouver
 * \return un pointeur sur la table, null si on ne l'a pas trouvée
 */
Table* Instance::obtenirTableParId(int _id)
{
    for(int i =0; i<tables.size(); i++)
    {
        if(tables[i].obtenirId()==_id)
            return &tables[i];
    }
    return NULL;
}
/*!
 * \brief Instance::definirNombreTours permet de fixer le nombre de tour
 * \param _nombreTours
 */
void Instance::definirNombreTours(int _nombreTours)
{
    nombreTours=_nombreTours;
    emit modifierTours(nombreTours);
}
/*!
 * \brief Instance::vider remet à zéro une instance du problème
 */
void Instance::vider()
{
    emit supprimerSolution();
    participants.clear();
    tables.clear();
    groupes.vider();
}
/*!
 * \brief Instance::problemeComplet indique si l'instance permet de calculer une solution
 * \return
 */
bool Instance::problemeComplet()
{
    if(participants.length()>1 && tables.length()>0 && nombreTours>0 && groupes.obtenirGroupes().length()>0)
        return true;
    return false;
}

void Instance::print()
{
    groupes.print();
    qDebug() << "Liste des personnes : ";
    qDebug() << "Nombre de tours : " << nombreTours;
    for(int i =0; i< participants.size(); i++)
    {
        participants[i].print();
    }
    for(int i =0; i< tables.size(); i++)
    {
        tables[i].print();
    }
}
