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

Rencontre& Rencontre::operator =(const Rencontre& _rencontre)
{
    this->personnes=_rencontre.personnes;
    this->valeur=_rencontre.valeur;
    this->table=_rencontre.table;
    return (*this);
}

int Rencontre::rowCount(const QModelIndex &parent) const
{
    return this->personnes.size();
}

int Rencontre::columnCount(const QModelIndex &parent) const
{
    return 2;
}
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
QVariant Rencontre::data(const QModelIndex &index, int role) const
{
    if(role== Qt::DisplayRole)
    {
        if(index.column()==0)
        {
            return personnes.at(index.row())->obtNom();
        }
        if(index.column()==1)
        {
            int interet=0;
            for(int i=0; i< personnes.length(); i++)
            {
                //On ne calcule pas l'interet de se rencontrer soi-même
                if(i!=index.row())
                {
                    interet+=personnes.at(index.row())->obtInteretRencontre(personnes.at(i));
                }
            }
            return interet;
        }
    }
    return QVariant();
}
