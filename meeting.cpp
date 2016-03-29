#include "Meeting.h"

Meeting* Meeting::instance=0;
Meeting& Meeting::getInstance(bool create)
{
    if(Meeting::instance)
    {
        if(!create)
            return *Meeting::instance;
        delete Meeting::instance;
    }
    Meeting::instance = new Meeting();
    return *Meeting::instance;

}

void Meeting::ajoutIndividu(QString _nom, QString _prenom, QList<QString> _groupes)
{
    participants.append(Individu(_nom, _prenom));
    for(int i =0; i<_groupes.size(); i++)
    {
        Groupe* nouveauGroupe = groupes.obtGroupeParNom(_groupes[i]);
        if(nouveauGroupe)
            participants.last().ajouterGroupe(nouveauGroupe);
    }
}

void Meeting::supprimer(int id)
{
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtId() == id)
            participants[i].supprimer();
    }
}


void Meeting::retirerIndividuSupprimes()
{
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].estSupprime())
            participants.removeAt(i);
    }
}

void Meeting::print()
{
    groupes.print();
    qDebug() << "Liste des personnes : ";
    for(int i =0; i< participants.size(); i++)
    {
        participants[i].print();
    }
}
