#include "Individu.h"
#include "QDebug"

int Individu::idCount=0;

void Individu::print()
{
    qDebug() << obtNomComplet();
    qDebug() << id;
    qDebug() << "Liste de groupes : ";
    for(int i=0; i<groupes.size(); i++)
    {
        qDebug() << groupes[i]->obtNom();
    }
}

void Individu::retirerGroupe(Groupe *_groupe)
{
    int i = groupes.indexOf(_groupe);
    if(i>=0)
        groupes.removeAt(i);
}
