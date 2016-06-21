#ifndef TOUR
#define TOUR

#include "Individu.h"
#include "Rencontre.h"
#include <QList>
#include <QAbstractListModel>

/*!
 * \brief La classe Tour rerésente un tour de rencontres
 * Elle implémente un modèle de liste qui correspond à la liste des personnes non placées durant le tour
 */
class Tour : public QAbstractListModel{
  // Attributes
private:
  /*! La liste des rencontres */
  QList<Rencontre> rencontres;
  /*! La liste des personnes non placées */
  QList<const Individu*> personnesNonPlacees;
  /*! Le numéro du tour */
  int numero;

  // Operations
  bool estRescence(const Individu* _personne);
public:
  Tour(QObject *parent=0):QAbstractListModel(parent){};
  Tour(const Tour& _tour):QAbstractListModel(){(*this)=_tour;};
  Tour& operator =(const Tour &_tour);


  void echangerPersonnes (Individu *_personne1, Individu *_personne2);

  //Gestion des personnes non placées
  void completerPersonnesNonPlacees();
  void ajoutPersonneNonPlacee(Individu* _personne){personnesNonPlacees.append(_personne);};
  QList<const Individu*> obtenirPersonnesNonPlacees(){return personnesNonPlacees;};

  void ajouterRencontre(Rencontre _rencontre){rencontres.append(_rencontre);};

  void definirNumeroTour(int _numero){numero=_numero;};
  int obtenirNombreRencontre(){return rencontres.length();};

  Rencontre &obtenirRencontre(int _numero);

  int obtenirValeur() const;

  int rowCount(const QModelIndex &parent) const{return personnesNonPlacees.length();};


  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

};

#endif
