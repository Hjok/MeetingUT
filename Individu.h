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
  void ajouterGroupe(Groupe* _groupe){groupes.append(_groupe);};

  const QList<Groupe*> obtGroupes(){return groupes;};

  QString obtNom(){return nom;};

  int obtId(){return id;}
  bool estSupprime(){return supprime;};
  void supprimer(){supprime =true;};

  void print();
};

#endif

