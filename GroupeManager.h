#ifndef GROUPE_MANAGER
#define GROUPE_MANAGER

#include "Groupe.h"
#include <QList>
#include <QMap>
#include <QDebug>

/// class GroupeManager - 
class GroupeManager {
  // Attributes
private:
  QMap<Groupe* , QMap<Groupe*, int>> matriceInteret;
  QList<Groupe> groupes;
  // Operations
public:
  void ajouterGroupe (QString _nom);
  void retirerGroupe (Groupe _groupe);
  void retirerGroupe (Groupe& groupe);
  void defInteret (Groupe& g1, Groupe& g2, unsigned int interet);
  int obtInteret (Groupe groupe1, Groupe groupe2);
  Groupe* obtGroupeParNom(QString _nom);


  void print();

private:
  void construireMatriceInteret();

};

#endif
