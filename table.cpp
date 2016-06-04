#include "Table.h"
#include "Meeting.h"
/*!
 * \brief Table::Table constructeur
 * \param _label
 * \param _nombreDePlaces
 * \param _id l'id de la table à créer si une autre table a déjà cet id, une erreur valant 1 est lancée
 */
Table::Table(QString _label, int _nombreDePlaces, int _id):label(_label), nombreDePlaces(_nombreDePlaces)
{
    if(Meeting::obtenirInstance().obtenirProbleme().idTableExiste(_id))
        throw 1;
    id=_id;
}
/*!
 * \brief Table::Table un constructeur qui gère l'attribution d'id
 * \param _label
 * \param _nombreDePlaces
 */
Table::Table(QString _label, int _nombreDePlaces):label(_label), nombreDePlaces(_nombreDePlaces)
{
    id=Meeting::obtenirInstance().obtenirProbleme().obtenirTableId();
}
void Table::print()
{
    qDebug() << label << id << " / " << nombreDePlaces;
}
