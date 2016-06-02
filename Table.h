#ifndef TABLE
#define TABLE
#include <QString>

/// class Table - 
class Table {
  // Attributes
private:
  QString label;
  unsigned int nombreDePlaces;
  int id;

  //struct informationsGraphiques;
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
