#include "Tour.h"
#include "Meeting.h"

void Tour::echangerPersonnes(Individu* _personne1, Individu* _personne2)
{
    int rencontrePersonne1=-1;
    int rencontrePersonne2=-1;
    for(int i=0; i<rencontres.size(); i++)
    {
        if(rencontres[i].contientPersonne(_personne1))
            rencontrePersonne1=i;
        if(rencontres[i].contientPersonne(_personne2))
            rencontrePersonne2=i;
    }
    if(rencontrePersonne1 > -1)
        rencontres[rencontrePersonne1].remplacePersonne(_personne1, _personne2);
    else
        personnesNonPlacees[personnesNonPlacees.indexOf(_personne1)] = _personne2;
    if(rencontrePersonne2 > -1)
        rencontres[rencontrePersonne2].remplacePersonne(_personne2, _personne1);
    else
        personnesNonPlacees[personnesNonPlacees.indexOf(_personne2)] = _personne1;
}
void Tour::completerPersonnesNonPlacees()
{
    for(int i=0; i<Meeting::getInstance().obtIndividus().length(); ++i)
    {
        if(!estRescence(&Meeting::getInstance().obtIndividus().at(i)))
        {
            personnesNonPlacees.append(&Meeting::getInstance().obtIndividus().at(i));
        }
    }
}
bool Tour::estRescence(const Individu* _personne)
{
    if(personnesNonPlacees.contains(_personne))
    {
        return true;
    }
    for(int i=0; i<rencontres.size(); i++)
    {
        if(rencontres[i].contientPersonne(_personne))
            return true;
    }
    return false;
}
QVariant Tour::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if(index.row()<personnesNonPlacees.length())
            return personnesNonPlacees.at(index.row());
    }
    return QVariant();
}

Tour& Tour::operator =(const Tour& _tour)
{
    this->personnesNonPlacees=_tour.personnesNonPlacees;
    this->rencontres=_tour.rencontres;
    return *this;
}
