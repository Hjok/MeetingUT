#ifndef TOUR
#define TOUR

#include "Individu.h"
#include "Rencontre.h"
#include <QList>

/// class Tour - 
class Tour {
  // Attributes
private:
  unsigned int id;
  unsigned int duree;
  QList<Rencontre> rencontres;
  // Operations
public:
  void echangerPersonnes (Individu personne1, Individu personne2);
};

#endif
