#ifndef RENCONTRE
#define RENCONTRE

#include "Individu.h"
#include "Table.h"
#include <QList>
#include <QAbstractTableModel>

/*!
 * \brief La classe Rencontre correspond à une rencontre de personne lors d'un tour autour d'une table donnée
 * Il alimente une tableview représentant graphiquement une rencontre et de ce fait implémente un modèle de table
 */
class Rencontre : public QAbstractTableModel{
  // Attributes
private:
    /*! La table à laquelle a lieu la rencontre */
  Table* table;
  /*! La liste des personnes assistant à cette rencontre */
  QList<const Individu*> personnes;
  // Operations
public:
  Rencontre(Table* _table, QList<const Individu*> _personnes):table(_table), personnes(_personnes){};
  Rencontre(int _table, QList<int> _personnes);
  Rencontre(const Rencontre& _rencontre){(*this)=_rencontre;};
  Rencontre& operator =(const Rencontre& _rencontre);

  //Gestion des personnes
  bool ajouterPersonne (const Individu* _personne);
  void retirerPersonne (const Individu* _personne);
  int obtenirValeurRencontre()const;
  bool contientPersonne(const Individu* _personne);
  void remplacePersonne(const Individu* _personneARemplacer, const Individu* _personneRemplacante);


  //Les fonctions du modèle de table
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};
#endif
