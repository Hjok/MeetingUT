#include "matriceinteret.h"
#include "QDebug"
MatriceInteret::MatriceInteret(QObject *parent):QAbstractTableModel(parent)
{

}

int MatriceInteret::rowCount(const QModelIndex &parent) const
{

    return matrice.size();
}
int MatriceInteret::columnCount(const QModelIndex &parent) const
{
    return matrice.size();
}
QVariant MatriceInteret::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if(obtIndex(index.row()) && obtIndex(index.column()))
            return matrice[obtIndex(index.row())][obtIndex(index.column())];
    }
    return QVariant();

}
QVariant MatriceInteret::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if(obtIndex(section))
            return obtIndex(section)->obtNom();
    }
    return QVariant();
}
bool MatriceInteret::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role == Qt::EditRole)
    {
        if(obtIndex(index.row()) && obtIndex(index.column()))
            matrice[obtIndex(index.row())][obtIndex(index.column())] = value.toInt();
    }
    return true;
}
Qt::ItemFlags MatriceInteret::flags(const QModelIndex &) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}
QMap<int, int> MatriceInteret::obtInteretsId (const Groupe *_groupe)const
{
    QMap<const Groupe*, int>::const_iterator j;
    QMap<int, int> liste;
    for(j=matrice[_groupe].begin(); j!= matrice[_groupe].end(); ++j)
    {
        liste[j.key()->obtId()]=j.value();
    }

    return liste;
}

void MatriceInteret::defInteret(const Groupe *_g1, const Groupe *_g2, unsigned int _interet)
{
    bool nouvCol=false;
    bool nouvLigne=false;
    if(!matrice.contains(_g1))
        nouvLigne=true;
    if(matrice.size()<=1 || !matrice.begin().value().contains(_g2))
        nouvCol=true;
    if(nouvLigne)
        beginInsertRows(QModelIndex(), 0, 0);
    if(nouvCol)
        beginInsertColumns(QModelIndex(), 0, 0);

    matrice[_g1][_g2] = _interet;
    QModelIndex index =createIndex(obtPlace(_g1), obtPlace(_g2));
    emit dataChanged(index, index);

    if(nouvLigne)
        endInsertRows();
    if(nouvCol)
        endInsertColumns();
}
void MatriceInteret::retirerGroupe(const Groupe *_g)
{
    QMap<const Groupe*, QMap<const Groupe*, int>>::const_iterator j;
    beginRemoveRows(QModelIndex(), obtPlace(_g), obtPlace(_g));
    beginRemoveColumns(QModelIndex(), obtPlace(_g), obtPlace(_g));

    QModelIndex index;
    matrice.remove(_g);
    int i=0;
    int k=obtPlace(_g);
    for(j=matrice.begin(); j!= matrice.end(); ++j)
    {
        index =createIndex(i, k);
        emit dataChanged(index, index);
        matrice[j.key()].remove(_g);
        index =createIndex(k, i);
        emit dataChanged(index, index);
        i++;
    }
    endRemoveColumns();
    endRemoveRows();
}

const Groupe* MatriceInteret::obtIndex(int _index) const
{
    QMap<const Groupe*, QMap<const Groupe*, int>>::const_iterator j;
    int i=0;
    for(j=matrice.begin(); j!= matrice.end(); ++j)
    {
        if(i== _index)
            return j.key();
        i++;
    }
    return NULL;
}
int MatriceInteret::obtPlace(const Groupe *_g) const
{
    QMap<const Groupe*, QMap<const Groupe*, int>>::const_iterator j;
    int i=0;
    for(j=matrice.begin(); j!= matrice.end(); ++j)
    {
        if(j.key()==_g)
            return i;
        i++;
    }
    return -1;
}
