#include "groupegraphique.h"
#include "ui_groupegraphique.h"

#include "Meeting.h"
#include <QMessageBox>
GroupeGraphique::GroupeGraphique(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupeGraphique)
{
    ui->setupUi(this);
    //Récupération des composants graphiques
    listeGroupes=findChild<QComboBox *>("listeGroupes");
    supprimerGroupe = findChild<QPushButton *>("supprimerGroupe");
    nouveauGroupe = findChild<QLineEdit *>("nouveauGroupe");
    creerGroupe=findChild<QPushButton *>("valideNouveauGroupe");
    matriceInteret=findChild<QTableView *>("matrice");

    Meeting& meeting = Meeting::getInstance();

    connect(creerGroupe, SIGNAL(clicked()), this, SLOT(ajouterGroupe()));
    connect(nouveauGroupe, SIGNAL(returnPressed()), this, SLOT(ajouterGroupe()));
    connect(supprimerGroupe, SIGNAL(clicked()), this, SLOT(retirerGroupe()));
    connect(&meeting.obtGroupeManager(), SIGNAL(listeGroupeAjout(QString)), this, SLOT(ajoutGroupe(QString)));
    connect(&meeting.obtGroupeManager(), SIGNAL(listeGroupeRetrait(QString)), this, SLOT(retraitGroupe(QString)));
    //On fixe le modèle de la matrice d'interet
    matriceInteret->setModel(meeting.obtGroupeManager().obtMatriceInteret());
}

GroupeGraphique::~GroupeGraphique()
{
    delete ui;
}
void GroupeGraphique::ajoutGroupe(QString _nomGroupe)
{
    listeGroupes->addItem(_nomGroupe);
}

void GroupeGraphique::retirerGroupe()
{
    if(!listeGroupes->currentText().isEmpty())
        Meeting::getInstance().obtGroupeManager().retirerGroupe(Meeting::getInstance().obtGroupeManager().obtGroupeParNom(listeGroupes->currentText()));
}

void GroupeGraphique::retraitGroupe(QString _nomGroupe)
{
        listeGroupes->removeItem(listeGroupes->findText(_nomGroupe));
}

void GroupeGraphique::ajouterGroupe()
{
    if(!nouveauGroupe->text().isEmpty())
    {
        try
        {
            Meeting::getInstance().obtGroupeManager().ajouterGroupe(nouveauGroupe->text());
        }
        catch(int i)
        {
            if(i==1)
            {
                QMessageBox messageBox;
                messageBox.critical(0,"Erreur","Ce groupe existe déjà");
                messageBox.setFixedSize(500,200);
            }
        }
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Erreur","Avec un nom, c'est mieux !");
        messageBox.setFixedSize(500,200);
    }
    nouveauGroupe->clear();
}
