#include "touredition.h"
#include "ui_touredition.h"
#include "Meeting.h"

TourEdition::TourEdition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TourEdition)
{
    ui->setupUi(this);

    nombreDeTours = findChild<QLineEdit *>("nombreDeTours");
    validerNombreDeTours = findChild<QPushButton *>("validerNombreTours");
    nombreDeTours->setText(QString::number(Meeting::obtenirInstance().obtenirProbleme().obtenirNombreTours()));

    connect(&Meeting::obtenirInstance().obtenirProbleme(), SIGNAL(modifierTours(int)), this, SLOT(nombreToursChange(int)));
    connect(validerNombreDeTours, SIGNAL(clicked()), this, SLOT(changerNombreTours()));
    this->setMaximumHeight(50);
}

TourEdition::~TourEdition()
{
    delete ui;
}

void TourEdition::changerNombreTours()
{
    if(!nombreDeTours->text().isEmpty())
        Meeting::obtenirInstance().obtenirProbleme().definirNombreTours(nombreDeTours->text().toInt());
}
void TourEdition::nombreToursChange(int _nombreTours)
{
    nombreDeTours->setText(QString::number(_nombreTours));
}
