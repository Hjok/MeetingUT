#ifndef MEETING
#define MEETING

#include "GroupeManager.h"
#include "Table.h"
#include "Tour.h"
#include "Individu.h"
#include "Solution.h"
#include "instance.h"
#include <QList>

/*!
 * \brief La classe Meeting est un singleton qui gère les l'instance du problème et sa solution.
 */
class Meeting:public QObject {
    Q_OBJECT
  // Attributes
private:
  static Meeting* instance;
  /*! L'instance du problème */
  Instance probleme;
  /*! La solution proposée */
  Solution solution;
  // Operations
public:
  static Meeting& obtenirInstance(bool create=false);

  void vider();
  Instance& obtenirProbleme();

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
