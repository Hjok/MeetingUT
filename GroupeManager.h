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
  QMap<const Groupe* , QMap<const Groupe*, int>> matriceInteret;
  QList<Groupe> groupes;
  // Operations
public:
  void ajouterGroupe (QString _nom);
  void ajouterGroupe(QString _nom, int _id);
  void retirerGroupe (Groupe* _groupe);
  void defInteret (const Groupe* _g1, const Groupe* _g2, unsigned int _interet);
  void defMatriceInteret(QMap<int, QMap<int, int>>& _matriceIds);
  QMap<int, int> obtListeInteretIds (const Groupe *_groupe)const;
  int obtInteret (const Groupe *_groupe1, const Groupe *_groupe2);

  const QList<Groupe>& obtGroupes() const {return groupes;};

  int obtProcId();

  bool idExiste(int _id);

  Groupe* obtGroupeParNom(QString _nom);
  Groupe* obtGroupeParId(int _id);

  void vider();


  void print();

private:
  void initInterets(const Groupe *_groupeAInit);

};

#endif
