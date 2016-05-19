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
  void ajouterGroupe(QString _nom, int _id);
  void retirerGroupe (Groupe* _groupe);
  void defInteret (Groupe* _g1, Groupe* _g2, unsigned int _interet);
  int obtInteret (Groupe *_groupe1, Groupe *_groupe2);

  int obtProcId();

  bool idExiste(int _id);

  Groupe* obtGroupeParNom(QString _nom);
  Groupe* obtGroupeParId(int _id);


  void print();

private:
  void initInterets(Groupe *_groupeAInit);

};

#endif
