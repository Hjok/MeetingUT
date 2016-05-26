#include "Rencontre.h"
#include "Meeting.h"
Rencontre::Rencontre(int _table, QList<int> _personnes, int _valeur)
{
    table=Meeting::getInstance().obtTableParId(_table);
    for(int i=0; i<_personnes.length(); ++i)
    {
        personnes.append(Meeting::getInstance().obtIndividuParId(_personnes[i]));
    }
    valeur=_valeur;
}

bool Rencontre::ajouterPersonne(const Individu *_personne)
{
    if(table->obtNombreDePlaces() <= personnes.length())
        return false;
    personnes.append(_personne);
    return true;
}

void Rencontre::retirerPersonne(const Individu *_personne)
{
    personnes.removeAll(_personne);
}

bool Rencontre::contientPersonne(const Individu *_personne)
{
    for(int i=0; i< personnes.length(); i++)
    {
        if(personnes[i] == _personne)
            return true;
    }
    return false;
}


void Rencontre::remplacePersonne(const Individu* _personneARemplacer, const Individu* _personneRemplacante)
{
    personnes.replace(personnes.indexOf(_personneARemplacer), _personneRemplacante);
}
