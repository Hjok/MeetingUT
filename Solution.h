#ifndef SOLUTION_H
#define SOLUTION_H
#include "QList"
#include "Tour.h"

class Solution
{
public:
    Solution(){};

    void ajoutTour(Tour& _tour){tours.append(_tour);};
    void defMetaDonnees(QMap<QString, QString> _metaDonnees){metaDonnees=_metaDonnees;};
    QMap<QString, QString>& obtMetaDonnees(){return metaDonnees;};
    Tour &obtTour(int _numero);
    int obtNumeroNouveauTour(){return tours.length();};
    void print(){qDebug()<<tours.length();}
    QString obtMetaDonneesText();
private:
    QList<Tour> tours;
    QMap<QString, QString> metaDonnees;

};

#endif // SOLUTION_H
