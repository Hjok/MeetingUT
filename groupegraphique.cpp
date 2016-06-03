#include "groupegraphique.h"
#include "ui_groupegraphique.h"

#include "Meeting.h"
#include <QMessageBox>
GroupeGraphique::GroupeGraphique(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupeGraphique)
{
    //Initialisation avec le fichier ui
    ui->setupUi(this);

        //Récupération des composants graphiques crées par le fichier ui
        listeGroupes=findChild<QComboBox *>("listeGroupes");
        supprimerGroupe = findChild<QPushButton *>("supprimerGroupe");
        nouveauGroupe = findChild<QLineEdit *>("nouveauGroupe");
        creerGroupe=findChild<QPushButton *>("valideNouveauGroupe");
        matriceInteret=findChild<QTableView *>("matrice");

    //Récupération du meeting courant
    Meeting& meeting = Meeting::obtenirInstance();

    //Connexion des boutons de cération/suppression
    connect(creerGroupe, SIGNAL(clicked()), this, SLOT(ajouterGroupe()));
    connect(nouveauGroupe, SIGNAL(returnPressed()), this, SLOT(ajouterGroupe()));
    connect(supprimerGroupe, SIGNAL(clicked()), this, SLOT(retirerGroupe()));

    //Lorsque des groupes sont attirés ou retirés par le Back-office, on appelle les slots pour mettre l'affichage à jour
    connect(&meeting.obtenirProbleme().obtenirGroupeManager(), SIGNAL(listeGroupeAjout(QString)), this, SLOT(ajoutGroupe(QString)));
    connect(&meeting.obtenirProbleme().obtenirGroupeManager(), SIGNAL(listeGroupeRetrait(QString)), this, SLOT(retraitGroupe(QString)));

    //On fixe le modèle de la matrice d'interet la classe MatriceInteret est un modèle valable pour une QTableView
    matriceInteret->setModel(meeting.obtenirProbleme().obtenirGroupeManager().obtenirMatriceInteret());
}

GroupeGraphique::~GroupeGraphique()
{
    delete ui;
}
/*!
 * Slot appelé lorsque le back-office signale l'ajout d'un groupe
 * On ajoute le nom de ce groupe au menu déroulant
 */
void GroupeGraphique::ajoutGroupe(QString _nomGroupe)
{
    listeGroupes->addItem(_nomGroupe);
}
/*!
 * Slot appelé lorsque l'utilisateur supprime un groupe par l'interface graphique
 */
void GroupeGraphique::retirerGroupe()
{
    //On retire de la liste des groupes de groupeManager le groupe dont le nom est actuellement actif dans le menu déroulant des groupes
    if(!listeGroupes->currentText().isEmpty())
        Meeting::obtenirInstance().obtenirProbleme().obtenirGroupeManager().retirerGroupe(Meeting::obtenirInstance().obtenirProbleme().obtenirGroupeManager().obtenirGroupeParNom(listeGroupes->currentText()));
    //Notons qu'on ne met pas à jour le menu déroulant, qui sera mis à jour par l'émission du signal de suppression par le GroupeManager
}

/*!
 * Slot appelé lorsque le back-office signale un retrait de groupe, il met à jour le menu déroulant des groupes
 */
void GroupeGraphique::retraitGroupe(QString _nomGroupe)
{
        listeGroupes->removeItem(listeGroupes->findText(_nomGroupe));
}
/*!
 * Slot appelé lorsque l'utilisateur crée un nouveau groupe avec l'interface
 */
void GroupeGraphique::ajouterGroupe()
{
    //Si le champs de texte n'est pas vide
    if(!nouveauGroupe->text().isEmpty())
    {
        try
        {
            //On tente l'ajout d'un groupe
            Meeting::obtenirInstance().obtenirProbleme().obtenirGroupeManager().ajouterGroupe(nouveauGroupe->text());
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
    //On efface le champ de texte
    nouveauGroupe->clear();
    //Le menu déroulant des groupes sera mis à jour par le signal de création qu'émettre le back ofice
}
