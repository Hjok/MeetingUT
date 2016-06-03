#include "Meeting.h"
#include "chargeur.h"

Meeting* Meeting::instance=0;
Meeting& Meeting::obtenirInstance(bool create)
{
    if(Meeting::instance)
    {
        if(!create)
            return *Meeting::instance;
        delete Meeting::instance;
    }
    Meeting::instance = new Meeting();
    return *Meeting::instance;

}
Meeting::Meeting()
{
    connect(&probleme, SIGNAL(supprimerSolution()), &solution, SLOT(vider()));
}

void Meeting::vider()
{
    probleme.vider();
    solution.vider();
}

Solution& Meeting::obtenirSolution()
{
    return solution;
}


void Meeting::supprimerSolution()
{
    solution.vider();
}
