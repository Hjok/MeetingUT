#include "GroupeManager.h"

Groupe* GroupeManager::obtGroupeParNom(QString _nom)
{
    for(int i=0; i<groupes.size(); i++)
    {
        if(groupes[i].obtNom() == _nom)
            return &groupes[i];
    }
    return 0;
}

void GroupeManager::ajouterGroupe(QString _nom)
{
    if(obtGroupeParNom(_nom))
        throw 1;
    groupes.append(Groupe( _nom));
}

void GroupeManager::construireMatriceInteret()
{

}

void GroupeManager::print()
{
    qDebug() << "Liste de groupes : ";
    for(int i=0; i<groupes.size(); i++)
    {
        qDebug() << groupes[i].obtNom();
    }
}
