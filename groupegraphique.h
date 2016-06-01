#ifndef GROUPEGRAPHIQUE_H
#define GROUPEGRAPHIQUE_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QTableView>
#include <QLineEdit>


namespace Ui {
class GroupeGraphique;
}
/*!
 * La classe GroupeGraphique gère l'édition de tout ce qui concerne les groupes :
 * Ajout et suppression, mais égallement édition de la matrice d'interet
 */
class GroupeGraphique : public QWidget
{
    Q_OBJECT

public:
    explicit GroupeGraphique(QWidget *parent = 0);
    ~GroupeGraphique();

private:
    /*! Le fichier ui */
    Ui::GroupeGraphique *ui;
    /*! Le menu déroulant de sélection des groupes */
    QComboBox * listeGroupes;
    /*! La ligne de texte permettant d'entrer le nom d'un nouveau groupe */
    QLineEdit* nouveauGroupe;
    /*! Le bouton de création de groupe */
    QPushButton* creerGroupe;
    /*! Le bouton de supression de groupe */
    QPushButton* supprimerGroupe;
    /*! La tableau affichant la matrice d'interet */
    QTableView* matriceInteret;
private slots:

    //Quand un groupe est ajouté/retiré depuis l'interface
    void ajouterGroupe();
    void retirerGroupe();

    //Quand le back-office signale un ajout/retrait de groupe
    void ajoutGroupe(QString _nomGroupe);
    void retraitGroupe(QString _nomGroupe);
};

#endif // GROUPEGRAPHIQUE_H
