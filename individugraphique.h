#ifndef INDIVIDUGRAHIQUE_H
#define INDIVIDUGRAHIQUE_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include "Meeting.h"
#include "individueditiongraphique.h"

namespace Ui {
class IndividuGraphique;
}
/*!
 * \brief La classe IndividuGraphique
 */
class IndividuGraphique : public QWidget
{
    Q_OBJECT

public:
    explicit IndividuGraphique(QWidget *parent = 0);
    ~IndividuGraphique();

private:
    /*! Le fichier d'ui */
    Ui::IndividuGraphique *ui;
    /*! bouton d'ajout d'individu */
    QPushButton* ajouterIndividu;
    /*! bouton de modification d'individu */
    QPushButton* modifierIndividu;
    /*! bouton de suppression d'individu */
    QPushButton* supprimerIndividu;
    /*! menu déroulant d'individus */
    QComboBox* listeIndividus;
    /*! popup d'édition des individus */
    IndividuEditionGraphique* editionIndividu;
private slots:
    void suppressionIndividu();
    void individuAjoute(QString _name, int _id);
    void individuSupprime(int _id);
    void modificationIndividu();
    void ajoutIndividu();
};

#endif // INDIVIDUGRAHIQUE_H
