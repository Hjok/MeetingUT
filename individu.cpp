#include "Individu.h"
#include "QDebug"
#include "Meeting.h"

int Individu::idCount=0;

Individu::Individu(QString _nom, int _id):nom(_nom), supprime(false)
{
    if(Meeting::getInstance().idIndividuExiste(_id))
        throw 0;
    id=_id;
}
Individu::Individu(QString _nom, QList<Groupe*> _groupes):nom(_nom), supprime(false), groupes(_groupes)
{
    id=Meeting::getInstance().obtIndividuId();
}


void Individu::print()
{
    qDebug() << obtNom();
    qDebug() <<  id;
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
