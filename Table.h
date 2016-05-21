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
  int obtNombreDePlaces () const{return nombreDePlaces;}
  void defNombreDePlaces(int _nombreDePlaces){nombreDePlaces = _nombreDePlaces;}
  QString obtLabel() const{return label;};
  void defLabel(QString _label){label=_label;};
  int obtId() const{return id;};
  void defId(int _id){id= _id;};

  void print();



};


#endif
