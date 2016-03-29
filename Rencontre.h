#ifndef RENCONTRE
#define RENCONTRE

#include "Individu.h"
#include "Table.h"
#include <QList>

/// class Rencontre - 
class Rencontre {
  // Attributes
private:
  Table& table;
  QList<Individu*> personnes;
  // Operations
public:
  Rencontre(Table& t):table(t){};
  bool ajouterPersonne (Individu personne);
  void retirerPersonne (Individu personne);
  int obtValeurRencontre();
};
#endif
