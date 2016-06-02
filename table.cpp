#include "Table.h"
#include "Meeting.h"

Table::Table(QString _label, int _nombreDePlaces, int _id):label(_label), nombreDePlaces(_nombreDePlaces)
{
    if(Meeting::obtenirenirInstance().idTableExiste(_id))
        throw 1;
    id=_id;
}
Table::Table(QString _label, int _nombreDePlaces):label(_label), nombreDePlaces(_nombreDePlaces)
{
    id=Meeting::obtenirenirInstance().obtenirTableId();
}
void Table::print()
{
    qDebug() << label << id << " / " << nombreDePlaces;
}
