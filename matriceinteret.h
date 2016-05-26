#ifndef MATRICEINTERET_H
#define MATRICEINTERET_H
#include <QAbstractTableModel>
#include "Groupe.h"
#include <QDebug>

class MatriceInteret : public QAbstractTableModel
{
    Q_OBJECT
private:
    QMap<const Groupe* , QMap<const Groupe*, int>> matrice;
public:
    MatriceInteret(QObject *parent=0);
    QMap<const Groupe*, QMap<const Groupe*, int>> & obtMatrice(){return matrice;};
    QMap<int, int> obtInteretsId (const Groupe *_groupe)const;
    void defInteret (const Groupe* _g1, const Groupe* _g2, unsigned int _interet);
    void retirerGroupe(const Groupe* _g);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const ;
private:
    const Groupe *obtIndex(int _index) const;
    int obtPlace(const Groupe* _g) const;
};

#endif // MATRICEINTERET_H
