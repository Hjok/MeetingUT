#include "Solution.h"

Tour& Solution::obtTour(int _numero)
{
    int j=0;
    for (QList<Tour>::iterator i = tours.begin(); i != tours.end(); ++i)
    {
        if(j== _numero)
            return *i;
        j++;
    }
    throw 1;
}
