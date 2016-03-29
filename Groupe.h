#ifndef GROUPE
#define GROUPE

#include <QString>

/// class Groupe - 
class Groupe {
  // Attributes
private:
  QString nom;
  // Operations
public:
  QString obtNom (){return nom;};
  Groupe(QString _nom):nom(_nom){};
};


#endif
