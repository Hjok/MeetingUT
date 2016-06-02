#ifndef SOLUTION_H
#define SOLUTION_H
#include "QList"
#include "Tour.h"

class Solution
{
public:
    Solution(){};

    void ajoutTour(Tour& _tour){tours.append(_tour);};
    void definirMetaDonnees(QMap<QString, QString> _metaDonnees){metaDonnees=_metaDonnees;};
    QMap<QString, QString>& obtenirMetaDonnees(){return metaDonnees;};
    Tour &obtenirTour(int _numero);
    int obtenirNumeroNouveauTour(){return tours.length();};
    void print(){qDebug()<<tours.length();}
    QString obtenirMetaDonneesText();
    int obtenirValeur() const;
private:
    QList<Tour> tours;
    QMap<QString, QString> metaDonnees;

};

#endif // SOLUTION_H
