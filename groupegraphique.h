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

class GroupeGraphique : public QWidget
{
    Q_OBJECT

public:
    explicit GroupeGraphique(QWidget *parent = 0);
    ~GroupeGraphique();

private:
    Ui::GroupeGraphique *ui;
    QComboBox * listeGroupes;
    QLineEdit* nouveauGroupe;
    QPushButton* creerGroupe;
    QPushButton* supprimerGroupe;
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
