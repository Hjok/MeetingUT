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
  QString prenom;
  bool supprime;
  QList<Groupe*> groupes;
  int id;
  // Operations
public:
  Individu(QString _nom, QString _prenom):nom(_nom), prenom(_prenom), supprime(false), id(idCount){idCount++;};
  Individu(QString _nom, QString _prenom, QList<Groupe*> _groupes):nom(_nom), prenom(_prenom), supprime(false), groupes(_groupes), id(idCount){idCount++;};

  void retirerGroupe(Groupe* _groupe);
  void ajouterGroupe(Groupe* _groupe){groupes.append(_groupe);};

  QList<Groupe*> obtGroupes(){return groupes;};

  QString obtNomComplet(){ return prenom + " " + nom;};
  QString obtNom(){return nom;};
  QString obtPrenom(){return prenom;};

  int obtId(){return id;}
  bool estSupprime(){return supprime;};
  void supprimer(){supprime =true;};

  void print();
};

#endif

