#include "Meeting.h"
#include "chargeur.h"

Meeting* Meeting::instance=0;
/*!
 * \brief Meeting::obtenirInstance retourne l'instance du singleton
 * \param create
 * \return
 */
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
/*!
 * \brief Meeting::Meeting Le constructeur, qui permet de connecter le problème et la solution
 */
Meeting::Meeting()
{
    connect(&probleme, SIGNAL(supprimerSolution()), &solution, SLOT(vider()));
}
/*!
 * \brief Meeting::vider fonction servant à remettre à zéro le problème et la solution
 */
void Meeting::vider()
{
    probleme.vider();
    solution.vider();
}
/*!
 * \brief Meeting::obtenirProbleme accesseur sur le problème
 * \return
 */
Instance& Meeting::obtenirProbleme()
{
    return probleme;
}
/*!
 * \brief Meeting::obtenirSolution accesseur de la solution
 * \return
 */
Solution& Meeting::obtenirSolution()
{
    return solution;
}
/*!
 * \brief Meeting::supprimerSolution permet de remettre à zéro la solution
 */
void Meeting::supprimerSolution()
{
    solution.vider();
}
