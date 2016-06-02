#include "individueditiongraphique.h"
#include "ui_individueditiongraphique.h"
#include "Meeting.h"


IndividuEditionGraphique::IndividuEditionGraphique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndividuEditionGraphique)
{
    //résupération du fichier ui
    ui->setupUi(this);
    //récupération du champs de nom
    nom = findChild<QLineEdit *>("nom");
    //récupération du bouton de validation
    valider = findChild<QPushButton *>("valider");

    //Connexion du bouton de validation à l'opération de valider
    connect(valider, SIGNAL(clicked()), this, SLOT(validation()));
}

IndividuEditionGraphique::~IndividuEditionGraphique()
{
    delete ui;
}

/*!
 * \brief IndividuEditionGraphique::init initialise la popup
 * \param _id l'id du bonhomme à éditer, si l'id est égal à -1 (valeur par défaut), un nouvel individu est crée
 */
void IndividuEditionGraphique::init(int _id)
{
    //On commence par supprimer toutes les cases à cocher des groupes
    for(int i=0; i<groupes.length(); i++)
    {
        ui->groupesLayout->removeWidget(groupes[i]);
        if(groupes[i])
            delete(groupes[i]);
    }
    groupes.clear();

    //On crée une case à cocher par groupe
    const QList<Groupe>& listeGroupes = Meeting::obtenirenirInstance().obtenirGroupeManager().obtenirGroupes();
    for(int i=0; i<listeGroupes.length(); i++)
    {
        groupes.append(new QCheckBox(listeGroupes[i].obtenirNom()));
        ui->groupesLayout->addWidget(groupes.last(), i/3, i%3);
    }

    //Si l'id est égal à -1 on passe en mode création
    if(_id==-1)
    {
        nom->setText("Nom...");
        creation=true;
    }
    else
    {
        //Sinon on remplit les champs avec les valeurs de l'individu
        creation=false;
        //On récupère la personne par son id
        personne = Meeting::obtenirenirInstance().obtenirIndividuParId(_id);
        //On remplit le champs de nom
        nom->setText(personne->obtenirNom());
        //On parcourt les cases à cocher
        for(int i=0; i<groupes.length(); i++)
        {
            //On les décoche par défaut
            groupes[i]->setChecked(false);
            for (int j=0; j< personne->obtenirGroupes().length(); j++)
            {
                //Et on les coche si l'individu appartient à leur groupe associé
                if(personne->obtenirGroupes()[j]->obtenirNom() == groupes[i]->text())
                    groupes[i]->setChecked(true);
            }
        }
    }

}
/*!
 * \brief IndividuEditionGraphique::validation termine la création ou la modification d'un individu
 */
void IndividuEditionGraphique::validation()
{
    //On parcourt les cases à cocher et on récupère le nom de leur groupe si elles sont cochées
    QList<QString> listeGroupes;
    for(int i=0; i<groupes.length(); i++)
    {
        if(groupes[i]->isChecked())
            listeGroupes.append(groupes[i]->text());
    }
    //Si on est en mode création, on crée l'individu
    if(creation)
        Meeting::obtenirenirInstance().ajoutIndividu(nom->text(), listeGroupes);
    else
    {
        //Sinon on met à jour le nom
        personne->definirNom(nom->text());
        //On le vide de ses groupes
        personne->retirerGroupes();
        //Et on réajoute les groupes qu'on a recensé
        for(int i=0; i<groupes.length(); i++)
        {
            if(groupes[i]->isChecked())
                personne->ajouterGroupe(Meeting::obtenirenirInstance().obtenirGroupeManager().obtenirGroupeParNom(groupes[i]->text()));
        }
    }
    //Enfin on ferme la popup
    done(0);
}
