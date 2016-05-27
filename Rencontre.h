#ifndef RENCONTRE
#define RENCONTRE

#include "Individu.h"
#include "Table.h"
#include <QList>
#include <QAbstractTableModel>

/// class Rencontre - 
class Rencontre : public QAbstractTableModel{
  // Attributes
private:
  Table* table;
  QList<const Individu*> personnes;
  int valeur;
  // Operations
public:
  Rencontre(Table* _table, QList<const Individu*> _personnes, int _valeur):table(_table), personnes(_personnes), valeur(_valeur){};
  Rencontre(int _table, QList<int> _personnes, int _valeur);
  Rencontre(const Rencontre& _rencontre){(*this)=_rencontre;};

  Rencontre& operator =(const Rencontre& _rencontre);

  bool ajouterPersonne (const Individu* _personne);
  void retirerPersonne (const Individu* _personne);
  int obtValeurRencontre()const {return valeur;};
  bool contientPersonne(const Individu* _personne);
  void remplacePersonne(const Individu* _personneARemplacer, const Individu* _personneRemplacante);


  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};
#endif
