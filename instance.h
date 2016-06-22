#ifndef INSTANCE_H
#define INSTANCE_H
#include "GroupeManager.h"
#include "Table.h"
#include "Individu.h"

#include <QObject>
/*!
 * \brief La classe instance décrit les données d'une instance d'un problème
 * Elle est gérée par la classe Meeting
 */
class Instance : public QObject
{
    Q_OBJECT
    QList<Table> tables;
    QList<Individu> participants;
    GroupeManager groupes;
    int nombreTours;
signals:
  void tableCree(QString _label, int _id, int _capacite);
  void tableSupprimee(int _id);
  void individuCree(QString _nom, int _id);
  void individuSupprime(int _id);
  void modifierTours(int _nombreTours);
  void individuChange();
  void supprimerSolution();
public:
    explicit Instance(QObject *parent = 0);

    //Gestion des individus
    void ajoutIndividu(QString _nom, QList<QString> _groupes);
    void ajoutIndividu(QString _nom, int _id, QList<int>& _groupes);
    void supprimerIndividu(int _id);
    void modifierIndividu(int _id, QString _nom, QList<int> _groupes);

    int obtenirIndividuId();
    bool idIndividuExiste(int _id);
    Individu* obtenirIndividuParId(int _id);

    QList<Individu> &obtenirIndividus();

    //Gestion des tables
    void ajoutTable(QString _label, int _capacite, int _id);
    void ajoutTable(int _capacite);
    void ajoutTables(int _nombre, int _capacite);
    void supprimerTable(int _id);

    const QList<Table> obtenirTables() const {return tables;};
    int obtenirTableId();
    bool idTableExiste(int _id);
    Table* obtenirTableParId(int _id);

    void definirNombreTours(int _nombreTours);
    int obtenirNombreTours(){return nombreTours;};

    //Le problème comporte-t-il tous les paramètres nécessaires pour générer une solution ?
    bool problemeComplet();

    GroupeManager& obtenirGroupeManager (){return groupes;};

    void vider();

    void signalerChangementIndividu(){emit individuChange();};




public slots:
};

#endif // INSTANCE_H
