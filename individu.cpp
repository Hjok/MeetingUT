#include "Individu.h"
#include "QDebug"
#include "Meeting.h"

/*!
 * \brief Individu::Individu construit un individu
 * \param _nom le nom du bonhomme
 * \param _id l'id a attribuer, si il existe déjà on lance une erreur de valeur 1
 */
Individu::Individu(QString _nom, int _id):nom(_nom)
{
    if(Meeting::obtenirInstance().obtenirProbleme().idIndividuExiste(_id))
        throw 1;
    id=_id;
}
/*!
 * \brief Individu::Individu construit un individu
 * \param _nom le nom du bonhomme
 * \param _groupes la liste des groupes auxquels la personne appartient
 */
Individu::Individu(QString _nom, QList<Groupe*> _groupes):nom(_nom), groupes(_groupes)
{
    id=Meeting::obtenirInstance().obtenirProbleme().obtenirIndividuId();
}
/*!
 * \brief Individu::retirerGroupe retire un groupe de la liste de la personne
 * \param _groupe un pointeur sur le groupe à retirer
 */
void Individu::retirerGroupe(Groupe *_groupe)
{
    int i = groupes.indexOf(_groupe);
    if(i>=0)
    {
        groupes.removeAt(i);
        Meeting::obtenirInstance().obtenirProbleme().signalerChangementIndividu();
    }
}
/*!
 * \brief Individu::retirerGroupe retire tous les groupes
 */
void Individu::retirerGroupes()
{
    groupes.clear();
    Meeting::obtenirInstance().obtenirProbleme().signalerChangementIndividu();
}

/*!
 * \brief Individu::obtenirInteretRencontre Retourne l'interet qu'à cette personne à en rencontrer une autre
 * \param _personneRencontree un pointeur sur la personne rencontrée
 * \return la valeur de la rencontres
 */
int Individu::obtenirInteretRencontre(const Individu *_personneRencontree) const
{
    int interet =0;
    //Pour chaque groupe auquel appartient notre bonhomme
    for(int i=0; i<groupes.length(); i++)
    {
        //On somme les interet du groupe à tous ceux auxquels appartient la personne rencontrée
        for(int j=0; j<_personneRencontree->groupes.length(); j++)
        {
            interet+=Meeting::obtenirInstance().obtenirProbleme().obtenirGroupeManager().obtenirInteret(groupes[i], _personneRencontree->groupes[j]);
        }
    }
    return interet;
}
/*!
 * \brief Individu::ajouterGroupe l'individu a un groupe en plus !
 * \param _groupe le groupe auquel ajouter l'individu
 */
void Individu::ajouterGroupe(Groupe *_groupe)
{
    if(!groupes.contains(_groupe))
    {
        groupes.append(_groupe);
        Meeting::obtenirInstance().obtenirProbleme().signalerChangementIndividu();
    }
}
