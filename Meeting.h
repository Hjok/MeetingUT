#ifndef MEETING
#define MEETING

#include <QDebug>
#include "GroupeManager.h"
#include "Table.h"
#include "Tour.h"
#include "Individu.h"
#include <QList>

/// class Meeting - 
class Meeting {
  // Attributes
private:
  static Meeting* instance;

  QList<Table> tables;
  QList<Individu> participants;
  QList<Tour> tours;
  GroupeManager groupes;
  // Operations
public:
  static Meeting& getInstance(bool create=false);

  void ajoutIndividu(QString _nom, QString _prenom, QList<QString> _groupes);
  void retirerIndividuSupprimes();
  void supprimer(int id);

  QList<Individu> &obtIndividus();
  GroupeManager& obtGroupeManager (){return groupes;};

  //Debug function
  void print();

private:
  Meeting(){};
  ~Meeting(){};
};

#endif
