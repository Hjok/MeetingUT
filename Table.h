#ifndef TABLE
#define TABLE
#include <QString>

/*!
 * \brief La classe Table représente une table
 */
class Table {
  // Attributes
private:
    /*! Le nom de la table */
  QString label;
  /*! La capacité de la table */
  unsigned int nombreDePlaces;
  /*! l'identifiant unique de la table */
  int id;

  // Operations
public:
  Table(QString _label, int _nombreDePlaces, int _id);
  Table(QString _label, int _nombreDePlaces);

  int obtenirNombreDePlaces () const{return nombreDePlaces;}
  void definirNombreDePlaces(int _nombreDePlaces){nombreDePlaces = _nombreDePlaces;}
  QString obtenirLabel() const{return label;};
  void definirLabel(QString _label){label=_label;};
  int obtenirId() const{return id;};
  void definirId(int _id){id= _id;};

  void print();



};


#endif
