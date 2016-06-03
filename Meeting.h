#ifndef MEETING
#define MEETING

#include "GroupeManager.h"
#include "Table.h"
#include "Tour.h"
#include "Individu.h"
#include "Solution.h"
#include "instance.h"
#include <QList>

/// class Meeting - 
class Meeting:public QObject {
    Q_OBJECT
  // Attributes
private:
  static Meeting* instance;

  Instance probleme;
  Solution solution;
  // Operations
public:
  static Meeting& obtenirInstance(bool create=false);

  void vider();
  Instance& obtenirProbleme(){return probleme;}

  //Gestion solution
  void nouvelleSolution();
  Solution &obtenirSolution();

  //Debug function
  void print();
private:
  Meeting();
  ~Meeting(){};
private slots:
  void supprimerSolution();
};

#endif
