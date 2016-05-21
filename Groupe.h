#ifndef GROUPE
#define GROUPE

#include <QString>

/// class Groupe - 
class Groupe {
  // Attributes
private:
  QString nom;
  int id;
  // Operations
public:
  QString obtNom () const {return nom;};
  int obtId() const {return id;};
  Groupe(QString _nom);
  Groupe(QString _nom, int _id);
  bool operator ==(Groupe _groupe);
};


#endif
