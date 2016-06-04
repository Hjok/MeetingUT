#include "touredition.h"
#include "ui_touredition.h"
#include "Meeting.h"

TourEdition::TourEdition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TourEdition)
{
    //Récupération du fichier ui et de ses élèments
    ui->setupUi(this);

    nombreDeTours = findChild<QLineEdit *>("nombreDeTours");
    validerNombreDeTours = findChild<QPushButton *>("validerNombreTours");
    nombreDeTours->setText(QString::number(Meeting::obtenirInstance().obtenirProbleme().obtenirNombreTours()));

    //Connection du signal de changement de nombre de tours du BO avec le champs
    connect(&Meeting::obtenirInstance().obtenirProbleme(), SIGNAL(modifierTours(int)), this, SLOT(nombreToursChange(int)));
    //Connection du bouton de validation
    connect(validerNombreDeTours, SIGNAL(clicked()), this, SLOT(changerNombreTours()));
    //Et pareil avec le retour chariot
    connect(nombreDeTours, SIGNAL(returnPressed()), this, SLOT(changerNombreTours()));
    this->setMaximumHeight(50);
}

TourEdition::~TourEdition()
{
    delete ui;
}
/*!
 * \brief TourEdition::changerNombreTours change le nombre de tours lorsque l'utilisateur valide son entrée
 */
void TourEdition::changerNombreTours()
{
    if(!nombreDeTours->text().isEmpty())
        Meeting::obtenirInstance().obtenirProbleme().definirNombreTours(nombreDeTours->text().toInt());
}
/*!
 * \brief TourEdition::nombreToursChange met à jour le champs lorsque la valeur du BO change
 * \param _nombreTours
 */
void TourEdition::nombreToursChange(int _nombreTours)
{
    nombreDeTours->setText(QString::number(_nombreTours));
}
