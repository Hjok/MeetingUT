#ifndef MEETING
#define MEETING

#include "GroupeManager.h"
#include "Table.h"
#include "Tour.h"
#include "Individu.h"
#include "Solution.h"
#include <QList>

/// class Meeting - 
class Meeting:public QObject {
    Q_OBJECT
  // Attributes
private:
  static Meeting* instance;

  QList<Table> tables;
  QList<Individu> participants;
  Solution* solution;
  GroupeManager groupes;
  int nombreTours;
  // Operations
public:
  static Meeting& obtenirenirInstance(bool create=false);

  //Gestion des individus
  void ajoutIndividu(QString _nom, QList<QString> _groupes);
  void ajoutIndividu(QString _nom, int _id, QList<int>& _groupes);
  void retirerIndividuSupprimes();
  void supprimerIndividu(int _id);
  int obtenirIndividuId();
  bool idIndividuExiste(int _id);
  Individu* obtenirIndividuParId(int _id);
  void modifierIndividu(int _id, QString _nom, QList<int> _groupes);

  QList<Individu> &obtenirIndividus();

  //Gestion des tables
  void ajoutTable(QString _label, int _capacite, int _id);
  void ajoutTable(int _capacite);
  void ajoutTables(int _nombre, int _capacite);
  const QList<Table> obtenirTables() const {return tables;};
  void supprimerTable(int _id);
  int obtenirTableId();
  bool idTableExiste(int _id);
  Table* obtenirTableParId(int _id);



  void vider();
  void definirNombreTours(int _nombreTours);
  int obtenirNombreTours(){return nombreTours;};

  //Le problème comporte-t-il tous les paramètres nécessaires pour générer une solution ?
  bool problemeComplet();

  //Gestion solution
  void nouvelleSolution();
  Solution* obtenirSolution();
  void solutionConstruite(){emit solutionCree();};

  GroupeManager& obtenirGroupeManager (){return groupes;};

  //Debug function
  void print();

signals:
  void tableCree(QString _label, int _id, int _capacite);
  void tableSupprimee(int _id);
  void individuCree(QString _nom, int _id);
  void individuSupprime(int _id);
  void modifierTours(int _nombreTours);
  void solutionCree();
  void solutionSupprimee();
private:
  Meeting(){solution=NULL; nombreTours=0; emit modifierTours(0);};
  ~Meeting(){if(solution!=NULL) delete solution;};
};

#endif
