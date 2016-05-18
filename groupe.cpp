#include "Groupe.h"
#include "Meeting.h"

Groupe::Groupe(QString _nom):nom(_nom)
{
    id = Meeting::getInstance().obtGroupeManager().obtProcId();
}

Groupe::Groupe(QString _nom, int _id):nom(_nom)
{
    if(Meeting::getInstance().obtGroupeManager().idExiste(_id))
        throw 0;
    id=_id;
}

bool Groupe::operator ==(Groupe _groupe)
{
    return id==_groupe.obtId();
}
