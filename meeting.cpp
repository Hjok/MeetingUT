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
    emit individuCree(participants.last().obtNom(), participants.last().obtId());
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
     emit individuCree(participants.last().obtNom(), participants.last().obtId());
}

void Meeting::supprimerIndividu(int _id)
{
    emit solutionSupprimee();
    delete solution;
    qDebug() << "Solution supprimée";
    solution=NULL;
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtId() == _id)
            participants.removeAt(i);
    }
    emit individuSupprime(_id);
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
Individu *Meeting::obtIndividuParId(int _id)
{
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtId()==_id)
            return &participants[i];
    }
    return NULL;
}

void Meeting::modifierIndividu(int _id, QString _nom, QList<int> _groupes)
{
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtId()==_id)
        {
            participants[i].defNom(_nom);
            participants[i].retirerGroupes();
            for(int i =0; i<_groupes.size(); i++)
            {
                Groupe* nouveauGroupe = groupes.obtGroupeParId(_groupes[i]);
                if(nouveauGroupe)
                    participants[i].ajouterGroupe(nouveauGroupe);
            }
        }
    }
}

void Meeting::ajoutTable(QString _label, int _capacite, int _id)
{
    tables.append(Table(_label, _capacite, _id));
    emit tableCree(_label, _id, _capacite);
}
void Meeting::ajoutTable(int _capacite)
{
    tables.append(Table("Table n° " + QString::number(obtTableId()), _capacite));
    emit tableCree(tables.last().obtLabel(), tables.last().obtId(), tables.last().obtNombreDePlaces());
}
void Meeting::ajoutTables(int _nombre, int _capacite)
{
    for(int i=0; i<_nombre; i++)
        ajoutTable(_capacite);

}

void Meeting::supprimerTable(int _id)
{
    emit solutionSupprimee();
    delete solution; //Le solution utilise les tables existantes, une modification entraine donc son invalidation
    solution=NULL;
    int index=-1;
    for(int i =0; i<tables.size(); i++)
    {
        if(tables[i].obtId()==_id)
            index=i;
    }
    emit tableSupprimee(tables.at(index).obtId());
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

void Meeting::defNombreTours(int _nombreTours)
{
    nombreTours=_nombreTours;
    emit modifierTours(nombreTours);
}

void Meeting::vider()
{
    emit solutionSupprimee();
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
    emit solutionSupprimee();
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
