#include "Meeting.h"
#include "chargeur.h"

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

void Meeting::chargeInstance(QString _chemin, QString _cheminSolution)
{
    Meeting& meeting=getInstance();
    meeting.vider();
    chargeur charge(meeting);
    charge.chargeMeeting(_chemin);
    if(!_cheminSolution.isEmpty())
        charge.chargeSolution(_cheminSolution);

}

void Meeting::sauvegarder(QString _cheminMeeting, QString _cheminSolution)
{
    chargeur sauve(getInstance());
    sauve.sauveMeeting(_cheminMeeting);
    /*if(!_cheminSolution.isEmpty())
        charge.chargeSolution(_cheminSolution);*/
}

QList<Individu> &Meeting::obtIndividus()
{
    return participants;
}

void Meeting::ajoutIndividu(QString _nom, QList<QString> _groupes)
{
    participants.append(Individu(_nom, obtIndividuId()));
    for(int i =0; i<_groupes.size(); i++)
    {
        Groupe* nouveauGroupe = groupes.obtGroupeParNom(_groupes[i]);
        if(nouveauGroupe)
            participants.last().ajouterGroupe(nouveauGroupe);
    }
}


void Meeting::ajoutIndividu(QString _nom, int _id, QList<int> &_groupes)
{
     participants.append(Individu(_nom, _id));
     for(int i =0; i<_groupes.size(); i++)
     {
         Groupe* nouveauGroupe = groupes.obtGroupeParId(_groupes[i]);
         if(nouveauGroupe)
             participants.last().ajouterGroupe(nouveauGroupe);
     }
}

void Meeting::supprimerIndividu(int _id)
{
    delete solution;
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtId() == _id)
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

int Meeting::obtIndividuId()
{
    int id=0;
    while(idIndividuExiste(id))
        id++;
    return id;
}

bool Meeting::idIndividuExiste(int _id)
{
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtId()==_id)
            return true;
    }
    return false;
}
Individu* Meeting::obtIndividuParId(int _id)
{
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtId()==_id)
            return &participants[i];
    }
    return NULL;
}



void Meeting::ajoutTable(QString _label, int _capacite, int _id)
{
    tables.append(Table(_label, _capacite, _id));
}
void Meeting::ajoutTable(QString _label, int _capacite)
{
    tables.append(Table(_label, _capacite));
}

void Meeting::supprimerTable(int _id)
{
    delete solution; //Le solution utilise les tables existantes, une modification entraine donc son invalidation
    int index=-1;
    for(int i =0; i<tables.size(); i++)
    {
        if(tables[i].obtId()==_id)
            index=i;
    }
    tables.removeAt(index);
}

int Meeting::obtTableId()
{
    int id=0;
    while(idTableExiste(id))
        id++;
    return id;
}

bool Meeting::idTableExiste(int _id)
{
    for(int i =0; i<tables.size(); i++)
    {
        if(tables[i].obtId()==_id)
            return true;
    }
    return false;
}
Table* Meeting::obtTableParId(int _id)
{
    for(int i =0; i<tables.size(); i++)
    {
        if(tables[i].obtId()==_id)
            return &tables[i];
    }
    return NULL;
}

void Meeting::vider()
{
    if(solution != NULL)
    {
        delete solution;
        solution=NULL;
    }
    participants.clear();
    tables.clear();
    groupes.vider();
}

void Meeting::nouvelleSolution()
{
    if(solution != NULL)
        delete solution;
    solution=new Solution();
}

Solution* Meeting::obtSolution()
{
    return solution;
}

void Meeting::print()
{
    groupes.print();
    qDebug() << "Liste des personnes : ";
    qDebug() << "Nombre de tours : " << nombreTours;
    for(int i =0; i< participants.size(); i++)
    {
        participants[i].print();
    }
    for(int i =0; i< tables.size(); i++)
    {
        tables[i].print();
    }
}
