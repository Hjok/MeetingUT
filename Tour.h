#ifndef TOUR
#define TOUR

#include "Individu.h"
#include "Rencontre.h"
#include <QList>
#include <QAbstractListModel>

/// class Tour - 
class Tour : public QAbstractListModel{
  // Attributes
private:
  QList<Rencontre> rencontres;
  QList<const Individu*> personnesNonPlacees;
  int numero;
  // Operations
  bool estRescence(const Individu* _personne);
public:
  Tour(QObject *parent=0):QAbstractListModel(parent){};
  Tour(const Tour& _tour):QAbstractListModel(){(*this)=_tour;};
  void echangerPersonnes (Individu *_personne1, Individu *_personne2);
  void ajoutRencontre(Rencontre _rencontre){rencontres.append(_rencontre);};
  void ajoutPersonneNonPlacee(Individu* _personne){personnesNonPlacees.append(_personne);};
  void completerPersonnesNonPlacees();
  void defNumeroTour(int _numero){numero=_numero;};

  int rowCount(const QModelIndex &parent) const{return personnesNonPlacees.length();};

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  Tour& operator =(const Tour &_tour);

};

#endif
