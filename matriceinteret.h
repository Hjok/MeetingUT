#ifndef MATRICEINTERET_H
#define MATRICEINTERET_H
#include <QAbstractTableModel>
#include "Groupe.h"
#include <QDebug>

/*!
 * \brief La classe MatriceInteret gère la matrice d'interet entre les groupes
 * Elle implémente un modèle de table
 */
class MatriceInteret : public QAbstractTableModel
{
    Q_OBJECT
private:
    /*! La map qui contient les données d'interet*/
    QMap<const Groupe* , QMap<const Groupe*, int>> matrice;
public:
    //Gestion des données
    MatriceInteret(QObject *parent=0);
    QMap<const Groupe*, QMap<const Groupe*, int>> & obtenirMatrice(){return matrice;};
    QMap<int, int> obtenirInteretsId (const Groupe *_groupe)const;
    void definirInteret (const Groupe* _g1, const Groupe* _g2, unsigned int _interet);
    void retirerGroupe(const Groupe* _g);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const ;
private:
    //Convertisseurs d'index
    const Groupe *obtenirIndex(int _index) const;
    int obtenirPlace(const Groupe* _g) const;
};

#endif // MATRICEINTERET_H
