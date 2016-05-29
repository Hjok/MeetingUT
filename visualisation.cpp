#include "visualisation.h"
#include "Meeting.h"
#include <QTableView>
#include "fenetreprincipale.h"

Visualisation::Visualisation(QWidget *parent) : QWidget(parent)
{
    setLayout(new QHBoxLayout);


    personnesNonPlacees=NULL;
    rencontres= new QWidget();
    layoutTableaux = new QGridLayout();
    rencontres->setLayout(layoutTableaux);
    layout()->addWidget(rencontres);
    connect(&Meeting::getInstance(), SIGNAL(solutionCree()), this, SLOT(solutionAffiche()));
    connect(&Meeting::getInstance(), SIGNAL(solutionSupprimee()), this, SLOT(solutionDesactivee()));
}

void Visualisation::solutionAffiche()
{
    if(Meeting::getInstance().obtSolution())
    {
        QTableView* tableau;
        for(int i=0; i< Meeting::getInstance().obtSolution()->obtTour(numero).obtNombreRencontre(); i++)
        {
            tableau=new QTableView();
            tableaux.append(tableau);
            layoutTableaux->addWidget(tableau, i/3, i%3);
        }
        //Transform to List View ?
        personnesNonPlacees = new QTableView();

        layout()->addWidget(personnesNonPlacees);
        afficheTour();

        emit metaDonneesChangees(Meeting::getInstance().obtSolution()->obtMetaDonneesText());
    }
}
void Visualisation::tourChange(int _numero)
{
    numero=_numero;
    if(Meeting::getInstance().obtSolution())
        afficheTour();
}
void Visualisation::afficheTour()
{

    personnesNonPlacees->setModel(&Meeting::getInstance().obtSolution()->obtTour(numero));
    Tour& tour = Meeting::getInstance().obtSolution()->obtTour(numero);
    for(int i=0; i<Meeting::getInstance().obtSolution()->obtTour(numero).obtNombreRencontre(); i++)
    {
        tableaux[i]->setModel(&Meeting::getInstance().obtSolution()->obtTour(numero).obtRencontre(i));
        Rencontre& rencontre = Meeting::getInstance().obtSolution()->obtTour(numero).obtRencontre(i);
    }
}
void Visualisation::solutionDesactivee()
{
    layout()->removeWidget(personnesNonPlacees);
    delete personnesNonPlacees;
    personnesNonPlacees =NULL;
    for(int i=0; i<tableaux.length(); i++)
    {
        layoutTableaux->removeWidget(tableaux[i]);
    }
    qDeleteAll(tableaux);
    tableaux.clear();
    emit metaDonneesChangees();

}
