#ifndef INDIVIDU
#define INDIVIDU

#include <QString>
#include <QList>
#include <QDebug>
#include "Groupe.h"

/*!
 * \brief La classe individu représente une personne
 */
class Individu {
  // Attributes
private:
  /*! Le nom de la personne */
  QString nom;
  /*! la liste des groupes auxquels appartient la personne */
  QList<Groupe*> groupes;
  /*! l'id de la personne */
  int id;
  // Operations
public:
  Individu(QString _nom, int _id);
  Individu(QString _nom, QList<Groupe*> _groupes);

  //Gestion des groupes
  void retirerGroupe(Groupe* _groupe);
  void retirerGroupes(){groupes.clear();};
  void ajouterGroupe(Groupe* _groupe){if(!groupes.contains(_groupe))groupes.append(_groupe);};
  int obtenirInteretRencontre(const Individu *_personneRencontree) const;
  const QList<Groupe*> obtenirGroupes()const{return groupes;};

  QString obtenirNom()const{return nom;};
  int obtenirId() const{return id;}

  void definirNom(QString _nom){nom=_nom;};

};

#endif

