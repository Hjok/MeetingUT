#include "Meeting.h"
#include "chargeur.h"

Meeting* Meeting::instance=0;
Meeting& Meeting::obtenirenirInstance(bool create)
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

QList<Individu> &Meeting::obtenirIndividus()
{
    return participants;
}

void Meeting::ajoutIndividu(QString _nom, QList<QString> _groupes)
{
    participants.append(Individu(_nom, obtenirIndividuId()));
    for(int i =0; i<_groupes.size(); i++)
    {
        Groupe* nouveauGroupe = groupes.obtenirGroupeParNom(_groupes[i]);
        if(nouveauGroupe)
            participants.last().ajouterGroupe(nouveauGroupe);
    }
    emit individuCree(participants.last().obtenirNom(), participants.last().obtenirId());
}


void Meeting::ajoutIndividu(QString _nom, int _id, QList<int> &_groupes)
{
     participants.append(Individu(_nom, _id));
     for(int i =0; i<_groupes.size(); i++)
     {
         Groupe* nouveauGroupe = groupes.obtenirGroupeParId(_groupes[i]);
         if(nouveauGroupe)
             participants.last().ajouterGroupe(nouveauGroupe);
     }
     emit individuCree(participants.last().obtenirNom(), participants.last().obtenirId());
}

void Meeting::supprimerIndividu(int _id)
{
    emit solutionSupprimee();
    delete solution;
    qDebug() << "Solution supprimée";
    solution=NULL;
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtenirId() == _id)
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

int Meeting::obtenirIndividuId()
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
        if(participants[i].obtenirId()==_id)
            return true;
    }
    return false;
}
Individu *Meeting::obtenirIndividuParId(int _id)
{
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtenirId()==_id)
            return &participants[i];
    }
    return NULL;
}

void Meeting::modifierIndividu(int _id, QString _nom, QList<int> _groupes)
{
    for(int i =0; i<participants.size(); i++)
    {
        if(participants[i].obtenirId()==_id)
        {
            participants[i].definirNom(_nom);
            participants[i].retirerGroupes();
            for(int i =0; i<_groupes.size(); i++)
            {
                Groupe* nouveauGroupe = groupes.obtenirGroupeParId(_groupes[i]);
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
    tables.append(Table("Table n° " + QString::number(obtenirTableId()), _capacite));
    emit tableCree(tables.last().obtenirLabel(), tables.last().obtenirId(), tables.last().obtenirNombreDePlaces());
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
        if(tables[i].obtenirId()==_id)
            index=i;
    }
    emit tableSupprimee(tables.at(index).obtenirId());
    tables.removeAt(index);
}

int Meeting::obtenirTableId()
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
        if(tables[i].obtenirId()==_id)
            return true;
    }
    return false;
}
Table* Meeting::obtenirTableParId(int _id)
{
    for(int i =0; i<tables.size(); i++)
    {
        if(tables[i].obtenirId()==_id)
            return &tables[i];
    }
    return NULL;
}

void Meeting::definirNombreTours(int _nombreTours)
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

Solution* Meeting::obtenirSolution()
{
    return solution;
}

bool Meeting::problemeComplet()
{
    if(participants.length()>1 && tables.length()>0 && nombreTours>0 && groupes.obtenirGroupes().length()>0)
        return true;
    return false;
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
