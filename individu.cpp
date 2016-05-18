#include "Individu.h"
#include "QDebug"

int Individu::idCount=0;

void Individu::print()
{
    qDebug() << obtNomComplet();
    qDebug() << "Id : " + id;
    QString grou =  "Liste de groupes : ";
    for(int i=0; i<groupes.size(); i++)
    {
        grou = grou + groupes[i]->obtNom() + " / ";
    }
    qDebug()<<grou;
}

void Individu::retirerGroupe(Groupe *_groupe)
{
    int i = groupes.indexOf(_groupe);
    if(i>=0)
        groupes.removeAt(i);
}
