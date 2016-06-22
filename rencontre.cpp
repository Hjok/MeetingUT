#include "Rencontre.h"
#include "Meeting.h"
/*!
 * \brief Rencontre::Rencontre
 * \param _table l'id de la table
 * \param _personnes la liste des ids des personnes
 * \param _valeur la valeur de la rencontre
 */
Rencontre::Rencontre(int _table, QList<int> _personnes)
{
    //On récupère la table
    table=Meeting::obtenirInstance().obtenirProbleme().obtenirTableParId(_table);
    //On récupère chaqu individu
    for(int i=0; i<_personnes.length(); ++i)
    {
        if(Meeting::obtenirInstance().obtenirProbleme().obtenirIndividuParId(_personnes[i]))
            personnes.append(Meeting::obtenirInstance().obtenirProbleme().obtenirIndividuParId(_personnes[i]));
    }
}
/*!
 * \brief Rencontre::ajouterPersonne ajoute une personne à une rencontre
 * \param _personne le pointeur sur la personne à ajouter
 * \return true si l'ajout a été fait, false si il n'y avait pas la place
 */
bool Rencontre::ajouterPersonne(const Individu *_personne)
{
    if(table->obtenirNombreDePlaces() <= personnes.length())
        return false;
    personnes.append(_personne);
    return true;
}
/*!
 * \brief Rencontre::retirerPersonne retire une personne de la liste
 * \param _personne le pointeur sur la personne à retirer
 */
void Rencontre::retirerPersonne(const Individu *_personne)
{
    personnes.removeAll(_personne);
}
/*!
 * \brief Rencontre::contientPersonne indique si une personne participe à la rencontre
 * \param _personne le pointeur sur la personne
 * \return true si la parsonne participe, false sinon
 */
bool Rencontre::contientPersonne(const Individu *_personne)
{
    for(int i=0; i< personnes.length(); i++)
    {
        if(personnes[i] == _personne)
            return true;
    }
    return false;
}
/*!
 * \brief Rencontre::remplacePersonne Remplace un individu de la rencontre par un autre
 * \param _personneARemplacer pointeur sur la personne à remplacer
 * \param _personneRemplacante pointeur sur la personne à ajouter
 */
void Rencontre::remplacePersonne(const Individu* _personneARemplacer, const Individu* _personneRemplacante)
{
    personnes.replace(personnes.indexOf(_personneARemplacer), _personneRemplacante);
}
/*!
 * \brief Rencontre::operator = opérateur d'agalité nécessaire pour faire une QList de rencontres
 * \param _rencontre
 * \return
 */
Rencontre& Rencontre::operator =(const Rencontre& _rencontre)
{
    this->personnes=_rencontre.personnes;
    this->table=_rencontre.table;
    return (*this);
}
//Fonctions du modèle
/*!
 * \brief Rencontre::rowCount renvoie le nombre de ligne du tableau
 * \param parent null
 * \return le nombre de personnes de la rencontre
 */
int Rencontre::rowCount(const QModelIndex &parent) const
{
    return this->personnes.size();
}
/*!
 * \brief Rencontre::columnCount renvoie le nombre de colonnes du tableau
 * \param parent null
 * \return retourne 2 (une colonne pour les personnes, une autre pour les valeurs individuelles)
 */
int Rencontre::columnCount(const QModelIndex &parent) const
{
    return 2;
}
/*!
 * \brief Rencontre::headerData renvoie la valeur du titre d'une ligne ou colonne du tableau
 * \param section l'index de la ligne ou de la colonne
 * \param orientation si il s'agit d'une ligne ou d'une colonne
 * \param role le role
 * \return le texte à afficher
 */
QVariant Rencontre::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation==Qt::Horizontal)
    {
        if(section==0)
            return "Nom";
        if(section==1)
            return "Valeur";
    }
    return QVariant();
}
/*!
 * \brief Rencontre::data renvoie la valeur d'une case du tableau
 * \param index l'index de la case
 * \param role le role (lecture, écriture, ...)
 * \return la valeur à afficher
 */
QVariant Rencontre::data(const QModelIndex &index, int role) const
{
    if(role== Qt::DisplayRole)
    {
        //On renvoie le nom de la personne
        if(index.column()==0)
        {
            return personnes.at(index.row())->obtenirNom();
        }
        //On renvoie la valeur qu'il tire de la rencontre
        if(index.column()==1)
        {
            //On calcule la valeur individuelle de la rencontre
            int interet=0;
            //On parcourt tous les individus de la rencontre
            for(int i=0; i< personnes.length(); i++)
            {
                //Sauf l'individu dont la valeur doit être elle-même calculée, qui n'a aucun interet à se rencontrer lui-même
                if(i!=index.row())
                {
                    //Et pour chaque autre individu qu'il rencontre on ajoute l'interet qu'il a à le voir
                    interet+=personnes.at(index.row())->obtenirInteretRencontre(personnes.at(i));
                }
            }
            return interet;
        }
    }
    return QVariant();
}
/*!
 * \brief Rencontre::obtenirValeurRencontre calcule la valeur de la rencontre
 * \return la valeur de la rencontre
 */
int Rencontre::obtenirValeurRencontre() const
{
    int valeur=0;
    //Pour chaque individu
    for(int i=0; i<personnes.length(); i++)
    {
        //Pour chaque autre individu
        for(int j=0; j<personnes.length(); j++)
        {
            //On ne calcule pas la valeur de la rencontre avec soi-même !
            if(i != j)
            {
                //On somme foutredieu !
                valeur += personnes[i]->obtenirInteretRencontre(personnes[j]);
            }
        }
    }
    return valeur;
}
