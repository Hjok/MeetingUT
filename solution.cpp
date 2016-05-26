#include "Solution.h"

Tour& Solution::obtTour(int _numero)
{
    for (QList<Tour>::iterator i = tours.begin(); i != tours.end(); ++i)
    {
        return *i;
    }
    throw 0;
}
