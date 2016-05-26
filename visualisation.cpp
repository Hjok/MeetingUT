#include "visualisation.h"
#include "Meeting.h"

Visualisation::Visualisation(QWidget *parent) : QWidget(parent)
{
    setLayout(new QHBoxLayout);

    personnesNonPlacees = new QTableView();

    connect(&Meeting::getInstance(), SIGNAL(solutionCree()), this, SLOT(solutionAffiche()));
}

void Visualisation::solutionAffiche()
{
    personnesNonPlacees->setModel(&Meeting::getInstance().obtSolution()->obtTour(numero));
}
void Visualisation::tourChange(int _numero)
{
    numero=_numero;
}
