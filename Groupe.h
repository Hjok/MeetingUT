#ifndef GROUPE
#define GROUPE

#include <QString>

/*!
 * \brief La classe Groupe stocke les données d'un groupe
 */
class Groupe {
  // Attributes
private:
   /*! Le nom du groupe */
  QString nom;
  /*! Et son id */
  int id;
  // Operations
public:

  QString obtenirNom () const {return nom;};
  int obtenirId() const {return id;};


  Groupe(QString _nom);
  Groupe(QString _nom, int _id);
  bool operator ==(Groupe _groupe);
};


#endif
