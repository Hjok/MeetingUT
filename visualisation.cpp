#include "visualisation.h"
#include "Meeting.h"
#include <QTableView>

Visualisation::Visualisation(QWidget *parent) : QWidget(parent)
{
    setLayout(new QHBoxLayout);

    //Transform to List View ?
    personnesNonPlacees = new QTableView();

    layout()->addWidget(personnesNonPlacees);

    rencontres= new QWidget();
    rencontres->setLayout(new QGridLayout());
    layout()->addWidget(rencontres);
    connect(&Meeting::getInstance(), SIGNAL(solutionCree()), this, SLOT(solutionAffiche()));
}

void Visualisation::solutionAffiche()
{
    QTableView* tableau;
    personnesNonPlacees->setModel(&Meeting::getInstance().obtSolution()->obtTour(numero));
    for(int i=0; i< Meeting::getInstance().obtSolution()->obtTour(numero).obtNombreRencontre(); i++)
    {
        tableau=new QTableView();
        tableau->setModel(&Meeting::getInstance().obtSolution()->obtTour(numero).obtRencontre(i));
        rencontres->layout()->addWidget(tableau);
    }
}
void Visualisation::tourChange(int _numero)
{
    numero=_numero;
    if(Meeting::getInstance().obtSolution())
        solutionAffiche();
}
