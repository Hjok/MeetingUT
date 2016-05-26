#ifndef INDIVIDU
#define INDIVIDU

#include <QString>
#include <QList>
#include <QDebug>
#include "Groupe.h"

/// class Individu - 
class Individu {
  // Attributes
private:
  static int idCount;
  QString nom;
  bool supprime;
  QList<Groupe*> groupes;
  int id;
  // Operations
public:
  Individu(QString _nom, int _id);
  Individu(QString _nom, QList<Groupe*> _groupes);

  void retirerGroupe(Groupe* _groupe);
  void retirerGroupes(){groupes.clear();};
  void ajouterGroupe(Groupe* _groupe){if(!groupes.contains(_groupe))groupes.append(_groupe);};

  const QList<Groupe*> obtGroupes()const{return groupes;};

  QString obtNom()const{return nom;};

  int obtId() const{return id;}

  void defNom(QString _nom){nom=_nom;};
  bool estSupprime(){return supprime;};
  void supprimer(){supprime =true;};

  void print();
};

#endif

