#ifndef RENCONTRE
#define RENCONTRE

#include "Individu.h"
#include "Table.h"
#include <QList>

/// class Rencontre - 
class Rencontre {
  // Attributes
private:
  Table* table;
  QList<const Individu*> personnes;
  int valeur;
  // Operations
public:
  Rencontre(Table* _table, QList<const Individu*> _personnes, int _valeur):table(_table), personnes(_personnes), valeur(_valeur){};
  Rencontre(int _table, QList<int> _personnes, int _valeur);
  bool ajouterPersonne (const Individu* _personne);
  void retirerPersonne (const Individu* _personne);
  int obtValeurRencontre();
  bool contientPersonne(const Individu* _personne);
  void remplacePersonne(const Individu* _personneARemplacer, const Individu* _personneRemplacante);
};
#endif
