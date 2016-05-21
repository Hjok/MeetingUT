#ifndef MEETING
#define MEETING

#include <QDebug>
#include "GroupeManager.h"
#include "Table.h"
#include "Tour.h"
#include "Individu.h"
#include "Solution.h"
#include <QList>

/// class Meeting - 
class Meeting {
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
  static Meeting& getInstance(bool create=false);

  //Gestion des flux
  static void chargeInstance(QString _chemin, QString _cheminSolution=QString());
  void sauvegarder(QString _cheminMeeting, QString _cheminSolution=QString());

  //Gestion des individus
  void ajoutIndividu(QString _nom, QList<QString> _groupes);
  void ajoutIndividu(QString _nom, int _id, QList<int>& _groupes);
  void retirerIndividuSupprimes();
  void supprimerIndividu(int _id);
  int obtIndividuId();
  bool idIndividuExiste(int _id);
  Individu* obtIndividuParId(int _id);

  QList<Individu> &obtIndividus();

  //Gestion des tables
  void ajoutTable(QString _label, int _capacite, int _id);
  void ajoutTable(QString _label, int _capacite);
  const QList<Table> obtTables() const {return tables;};
  void supprimerTable(int _id);
  int obtTableId();
  bool idTableExiste(int _id);
  Table* obtTableParId(int _id);



  void vider();
  void defNombreTours(int _nombreTours){nombreTours=_nombreTours;};
  int obtNombreTours(){return nombreTours;};


  //Gestion solution
  void nouvelleSolution();
  Solution* obtSolution();

  GroupeManager& obtGroupeManager (){return groupes;};

  //Debug function
  void print();

private:
  Meeting(){solution=NULL;};
  ~Meeting(){if(solution!=NULL) delete solution;};
};

#endif
