#include "GroupeManager.h"
#include "Meeting.h"


Groupe* GroupeManager::obtGroupeParNom(QString _nom)
{
    for(int i=0; i<groupes.size(); i++)
    {
        if(groupes[i].obtNom() == _nom)
            return &groupes[i];
    }
    return 0;
}

Groupe* GroupeManager::obtGroupeParId(int _id)
{
    for(int i=0; i<groupes.size(); i++)
    {
        if(groupes[i].obtId() == _id)
            return &groupes[i];
    }
    return 0;
}

int GroupeManager::obtProcId()
{
    int id=0;
    while(idExiste(id))
        id++;
    return id;
}

void GroupeManager::ajouterGroupe(QString _nom)
{
    //Si le groupe n'existe pas
    if(obtGroupeParNom(_nom))
        throw 1;
    //On le crée
    groupes.append(Groupe( _nom));
    //Et on initialise ses interets à 0
    initInterets(&groupes.last());
}

void GroupeManager::ajouterGroupe(QString _nom, int _id)
{
    //Si le groupe n'existe pas
    if(obtGroupeParNom(_nom))
        throw 1;
    //On le crée
    groupes.append(Groupe( _nom, _id));
    //Et on initialise ses interets à 0
    initInterets(&groupes.last());
}

void GroupeManager::defInteret (Groupe* _g1, Groupe* _g2, unsigned int _interet)
{
    matriceInteret[_g1][_g2] = _interet;
}

void GroupeManager::print()
{
    qDebug() << "Liste de groupes : ";
    for(int i=0; i<groupes.size(); i++)
    {
        qDebug() << groupes[i].obtNom();
    }
}

bool GroupeManager::idExiste(int _id)
{
    if(obtGroupeParId(_id)!=0)
        return true;
    return false;
}
void GroupeManager::initInterets(Groupe* _groupeAInit)
{
    for(int i=0; i<groupes.size(); i++)
    {
        matriceInteret[_groupeAInit][&groupes[i]]=0;
    }
}
void GroupeManager::retirerGroupe (Groupe* _groupe)
{
    for(int i=0; i<groupes.size(); i++)
    {
        matriceInteret[&groupes[i]].remove(_groupe);
    }
    matriceInteret.remove(_groupe);

    for(int i=0; i<Meeting::getInstance().obtIndividus().size(); i++)
    {
        Meeting::getInstance().obtIndividus()[i].retirerGroupe(_groupe);
    }
    groupes.removeAll(*_groupe);

}
int GroupeManager::obtInteret (Groupe* _groupe1, Groupe* _groupe2)
{
    if(matriceInteret.contains(_groupe1) && matriceInteret[_groupe1].contains(_groupe2))
        return matriceInteret[_groupe1][_groupe2];
    return 0;
}
