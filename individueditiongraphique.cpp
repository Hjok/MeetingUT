#include "individueditiongraphique.h"
#include "ui_individueditiongraphique.h"
#include "Meeting.h"

IndividuEditionGraphique::IndividuEditionGraphique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndividuEditionGraphique)
{
    ui->setupUi(this);
    nom = findChild<QLineEdit *>("nom");
    valider = findChild<QPushButton *>("valider");
    connect(valider, SIGNAL(clicked()), this, SLOT(validation()));
}

IndividuEditionGraphique::~IndividuEditionGraphique()
{
    delete ui;
}

void IndividuEditionGraphique::init(int _id)
{
    for(int i=0; i<groupes.length(); i++)
    {
        ui->groupesLayout->removeWidget(groupes[i]);
        if(groupes[i])
            delete(groupes[i]);
    }
    groupes.clear();
    const QList<Groupe>& listeGroupes = Meeting::getInstance().obtGroupeManager().obtGroupes();
    for(int i=0; i<listeGroupes.length(); i++)
    {
        groupes.append(new QCheckBox(listeGroupes[i].obtNom()));
        ui->groupesLayout->addWidget(groupes.last(), i/3, i%3);
    }
    if(_id==-1)
    {
        nom->setText("Nom...");
        creation=true;
    }
    else
    {
        creation=false;
        personne = Meeting::getInstance().obtIndividuParId(_id);
        nom->setText(personne->obtNom());
        for(int i=0; i<groupes.length(); i++)
        {
            groupes[i]->setChecked(false);
            for (int j=0; j< personne->obtGroupes().length(); j++)
            {
                if(personne->obtGroupes()[j]->obtNom() == groupes[i]->text())
                    groupes[i]->setChecked(true);
            }
        }
    }

}

void IndividuEditionGraphique::validation()
{
    QList<QString> listeGroupes;
    for(int i=0; i<groupes.length(); i++)
    {
        if(groupes[i]->isChecked())
            listeGroupes.append(groupes[i]->text());
    }
    if(creation)
        Meeting::getInstance().ajoutIndividu(nom->text(), listeGroupes);
    else
    {
        personne->defNom(nom->text());
        personne->retirerGroupes();
        for(int i=0; i<groupes.length(); i++)
        {
            if(groupes[i]->isChecked())
                personne->ajouterGroupe(Meeting::getInstance().obtGroupeManager().obtGroupeParNom(groupes[i]->text()));
        }
    }
    done(0);
}
