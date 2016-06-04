#include "Tour.h"
#include "Meeting.h"

/*!
 * \brief Tour::echangerPersonnes permet d'échanger les places de deux personnes lors de ce tour
 * \param _personne1
 * \param _personne2
 */
void Tour::echangerPersonnes(Individu* _personne1, Individu* _personne2)
{
    //On commence par chercher à uelle rencontre les individus participent ce tour
    int rencontrePersonne1=-1;
    int rencontrePersonne2=-1;
    for(int i=0; i<rencontres.size(); i++)
    {
        if(rencontres[i].contientPersonne(_personne1))
            rencontrePersonne1=i;
        if(rencontres[i].contientPersonne(_personne2))
            rencontrePersonne2=i;
    }
    //Si la personne  participe à une rencontre à ce tour
    if(rencontrePersonne1 > -1)
        //On la remplace par la seconde personne
        rencontres[rencontrePersonne1].remplacePersonne(_personne1, _personne2);
    else
        //Sinon on la remplace dans les personnes non placées
        personnesNonPlacees[personnesNonPlacees.indexOf(_personne1)] = _personne2;
    //Même procédure pour la seconde personne
    if(rencontrePersonne2 > -1)
        rencontres[rencontrePersonne2].remplacePersonne(_personne2, _personne1);
    else
        personnesNonPlacees[personnesNonPlacees.indexOf(_personne2)] = _personne1;
}
/*!
 * \brief Tour::completerPersonnesNonPlacees remplit la liste des personnes non placées
 */
void Tour::completerPersonnesNonPlacees()
{
    //On parcourt tous les individus du problème
    for(int i=0; i<Meeting::obtenirInstance().obtenirProbleme().obtenirIndividus().length(); ++i)
    {
        //Si ils ne sont pas recencés
        if(!estRescence(&Meeting::obtenirInstance().obtenirProbleme().obtenirIndividus().at(i)))
        {
            //on les ajoute aux personnes non-placées
            personnesNonPlacees.append(&Meeting::obtenirInstance().obtenirProbleme().obtenirIndividus().at(i));
        }
    }
}
/*!
 * \brief Tour::estRescence indique si une personne s'est vue attribuer un rôle (rencontre ou non placée) ce tour
 * \param _personne
 * \return vrai si la personnes a un role
 */
bool Tour::estRescence(const Individu* _personne)
{
    //Si la personne apparait dans les non placés, on renvoie vrai
    if(personnesNonPlacees.contains(_personne))
    {
        return true;
    }
    //Si elle apparait dans une des rencontres aussi
    for(int i=0; i<rencontres.size(); i++)
    {
        if(rencontres[i].contientPersonne(_personne))
            return true;
    }
    //Sinon faux
    return false;
}
/*!
 * \brief Tour::operator = nécessaire pour utiliser une QList
 * \param _tour
 * \return
 */
Tour& Tour::operator =(const Tour& _tour)
{
    this->personnesNonPlacees=_tour.personnesNonPlacees;
    this->rencontres=_tour.rencontres;
    return *this;
}
/*!
 * \brief Tour::obtenirRencontre retourne une réference non-constante sur la rencontre de place indiquée
 * Lance une erreur  si la rencontre n'existe pas
 * \param _numero
 * \return
 */
Rencontre& Tour::obtenirRencontre(int _numero)
{
    int j=0;
    for (QList<Rencontre>::iterator i = rencontres.begin(); i != rencontres.end(); ++i)
    {
        if(j== _numero)
            return *i;
        j++;
    }
    throw 1;
}
/*!
 * \brief Tour::obtenirValeur calcule la valeur d'un tour
 * \return la somme des valeurs des rencontres
 */
int Tour::obtenirValeur() const
{
    int valeur=0;
    for(int i=0; i<rencontres.size(); i++)
        valeur+=rencontres[i].obtenirValeurRencontre();
    return valeur;
}

/*!
 * \brief Tour::data fonction du modèle retournant la valeur à afficher
 * \param index l'index de la valeur demandée
 * \param role le role, seule l'affichage est traité
 * \return le nom de la personne de l'index correspondant
 */
QVariant Tour::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if(index.row()<personnesNonPlacees.length())
            return personnesNonPlacees.at(index.row())->obtenirNom();
    }
    return QVariant();
}
/*!
 * \brief Tour::headerData fonction du modèle retournant le titre de la liste
 * \param section
 * \param orientation
 * \param role
 * \return
 */
QVariant Tour::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if(orientation==Qt::Horizontal)
            return "Personnes non placées";
    }
    return QVariant();
}

