#ifndef VISUALISATION_H
#define VISUALISATION_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QTableView>
#include <QListView>
#include <QLabel>
#include <QComboBox>
/*!
 * \brief La classe Visualisation permet d'afficher la solution
 */
class Visualisation : public QWidget
{
    Q_OBJECT
public:
    explicit Visualisation(QWidget *parent = 0);

private:
    QListView* personnesNonPlacees;
    int numero;
    /*! Composant contenant l'affichage des répartitions des individus en un tour */
    QWidget* conteneurTour;
    QWidget* rencontres;
    QList<QTableView *> tableaux;
    QGridLayout* layoutTableaux;
    /*! Composant affichant la valeur du tour */
    QLabel* valeurTour;
    /*! Composant affichant la valeur de la solution */
    QLabel* valeurSolution;
    /*! Composant de sélection de tours */
    QComboBox* listeTours;
    /*! Valeur indiquant si le composant est prêt pour l'affichage */
    bool afficher;

signals:
    void metaDonneesChangees(QString metaDonnees="Pas de solution calculée");

public slots:
private slots:
    void solutionAffiche();
    void tourChange(int _numero);
    void afficheTour();
    void solutionDesactivee();
    void valeurSolutionChangee();

};

#endif // VISUALISATION_H
