#ifndef SOLUTION_H
#define SOLUTION_H
#include "QList"
#include "Tour.h"

class Solution
{
public:
    Solution(){};

    void ajoutTour(Tour& _tour){tours.append(_tour);};
    void defMetaDonnees(QMap<QString, int> _metaDonnees){metaDonnees=_metaDonnees;};
    QMap<QString, int>& obtMetaDonnees(){return metaDonnees;};
private:
    QList<Tour> tours;
    QMap<QString, int> metaDonnees;

};

#endif // SOLUTION_H
