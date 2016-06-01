#include "Groupe.h"
#include "Meeting.h"


/*!
 * Constructeur de Groupe avec un nom. Il attribue automatiquement un id au groupe
 */
Groupe::Groupe(QString _nom):nom(_nom)
{
    id = Meeting::getInstance().obtGroupeManager().obtProcId();
}
/*!
 * Constructeur de Groupe avec un nom et un id. Si l'id est déjà utilisé par un autre groupe il throw une erreur.
 */
Groupe::Groupe(QString _nom, int _id):nom(_nom)
{
    if(Meeting::getInstance().obtGroupeManager().idExiste(_id))
        throw 1;
    id=_id;
}
/*!
 * Opérateur d'égalité. Comme on a la garantie que les ids sont uniques, on peut s'n servir comme point de comparaison
 * L'implémentation est nécessaire pour pouvoir utiliser les Groupes dans des QList
 */
bool Groupe::operator ==(Groupe _groupe)
{
    return id==_groupe.obtId();
}
