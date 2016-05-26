#ifndef GROUPE_MANAGER
#define GROUPE_MANAGER

#include "Groupe.h"
#include <QList>
#include <QMap>
#include "matriceinteret.h"
#include <QObject>

/// class GroupeManager - 
class GroupeManager:public QObject {
    Q_OBJECT
  // Attributes
private:
  MatriceInteret matriceInteret;
  QList<Groupe> groupes;
  // Operations
public:
  void ajouterGroupe (QString _nom);
  void ajouterGroupe(QString _nom, int _id);
  void retirerGroupe (Groupe* _groupe);
  void defInteret (const Groupe* _g1, const Groupe* _g2, unsigned int _interet);
  void defMatriceInteret(QMap<int, QMap<int, int>>& _matriceIds);
  MatriceInteret* obtMatriceInteret(){return &matriceInteret;};
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

signals:
  void listeGroupeAjout(QString _nomGroupe);
  void listeGroupeRetrait(QString _nomGroupe);

};

#endif
