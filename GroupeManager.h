#ifndef GROUPE_MANAGER
#define GROUPE_MANAGER

#include "Groupe.h"
#include <QList>
#include <QMap>
#include "matriceinteret.h"
#include <QObject>

/*!
 * La classe GroupeManager s'occupe de la gestion des groupes
 * Elle agrége donc d'une part les groupes et d'autre part la matrice d'interet des groupes
 * Elle n'implémente pas le design pattern singleton mais ne peut avoir qu'une instanciation à la fois
 * En effet elle est un agrégat en un exemplaire de Meeting, qui est elle-même un singleton
 */
class GroupeManager:public QObject {
    Q_OBJECT
  // Attributes
private:
    /*! La matrice d'interet */
  MatriceInteret matriceInteret;
  /*! La liste des groupes */
  QList<Groupe> groupes;
  // Operations
public:
  //Gestion des groupes
  void ajouterGroupe (QString _nom);
  void ajouterGroupe(QString _nom, int _id);
  void retirerGroupe (Groupe* _groupe);
  const QList<Groupe>& obtenirGroupes() const {return groupes;};
  int obtenirProcId();
  bool idExiste(int _id);
  Groupe* obtenirGroupeParNom(QString _nom);
  Groupe* obtenirGroupeParId(int _id);

  //Gestion de la matrice d'interet
  void definirInteret (const Groupe* _g1, const Groupe* _g2, unsigned int _interet);
  void definirMatriceInteret(QMap<int, QMap<int, int>>& _matriceIds);
  MatriceInteret* obtenirMatriceInteret(){return &matriceInteret;};
  QMap<int, int> obtenirListeInteretIds (const Groupe *_groupe)const;
  int obtenirInteret (const Groupe *_groupe1, const Groupe *_groupe2);


  void vider();
  void print();

private:
  void initInterets(const Groupe *_groupeAInit);

signals:
  /*! signal indiquant que le groupe de nom _nomGroupe a été crée et ajouté à la liste */
  void listeGroupeAjout(QString _nomGroupe);
  /*! signal indiquant que le groupe de nom _nomGroupe a été supprimé et retiré de la liste */
  void listeGroupeRetrait(QString _nomGroupe);

};

#endif
