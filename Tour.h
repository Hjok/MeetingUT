#ifndef TOUR
#define TOUR

#include "Individu.h"
#include "Rencontre.h"
#include <QList>

/// class Tour - 
class Tour {
  // Attributes
private:
  QList<Rencontre> rencontres;
  QList<const Individu*> personnesNonPlacees;
  bool estRescence(const Individu* _personne);
  // Operations
public:
  void echangerPersonnes (Individu *_personne1, Individu *_personne2);
  void ajoutRencontre(Rencontre _rencontre){rencontres.append(_rencontre);};
  void ajoutPersonneNonPlacee(Individu* _personne){personnesNonPlacees.append(_personne);};
  void completerPersonnesNonPlacees();
};

#endif
