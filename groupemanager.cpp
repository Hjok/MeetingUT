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

void GroupeManager::defInteret (const Groupe* _g1, const Groupe* _g2, unsigned int _interet)
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

    qDebug() << "Matrice d'interet : ";
    QMap<const Groupe*, QMap<const Groupe*, int>>::iterator i;
    QMap<const Groupe*, int>::iterator j;

    for(i=matriceInteret.begin(); i!= matriceInteret.end(); ++i)
    {
        qDebug() << "Pour le groupe : " << i.key()->obtId();
        for(j=i.value().begin(); j!= i.value().end(); ++j)
        {
            qDebug() << j.key()->obtId() << " = " << j.value();
        }
    }

}
QMap<int, int> GroupeManager::obtListeInteretIds (const Groupe *_groupe)const
{
    QMap<const Groupe*, int>::const_iterator j;
    QMap<int, int> liste;
    for(j=matriceInteret[_groupe].begin(); j!= matriceInteret[_groupe].end(); ++j)
    {
        liste[j.key()->obtId()]=j.value();
    }

    return liste;
}

bool GroupeManager::idExiste(int _id)
{
    if(obtGroupeParId(_id)!=0)
        return true;
    return false;
}
void GroupeManager::initInterets(const Groupe* _groupeAInit)
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
int GroupeManager::obtInteret (const Groupe *_groupe1, const Groupe *_groupe2)
{
    if(matriceInteret.contains(_groupe1) && matriceInteret[_groupe1].contains(_groupe2))
        return matriceInteret[_groupe1][_groupe2];
    return 0;
}
void GroupeManager::defMatriceInteret(QMap<int, QMap<int, int>>& _matriceIds)
{
    QMap<int, QMap<int, int>>::iterator i;
    QMap<int, int>::iterator j;
    Groupe* groupe;

    for(i=_matriceIds.begin(); i!= _matriceIds.end(); ++i)
    {
        groupe=obtGroupeParId(i.key());
        for(j=i.value().begin(); j!= i.value().end(); ++j)
        {
            matriceInteret[groupe][obtGroupeParId(j.key())] = j.value();
        }
    }
}

void GroupeManager::vider()
{
    matriceInteret.clear();
    groupes.clear();
}
