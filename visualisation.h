#ifndef VISUALISATION_H
#define VISUALISATION_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QTableView>
#include <QListView>
class Visualisation : public QWidget
{
    Q_OBJECT
public:
    explicit Visualisation(QWidget *parent = 0);

private:
    QListView* personnesNonPlacees;
    int numero;
    QWidget* rencontres;
    QList<QTableView *> tableaux;
    QGridLayout* layoutTableaux;

signals:
    void metaDonneesChangees(QString metaDonnees="Pas de solution calculée");

public slots:
private slots:
    void solutionAffiche();
    void tourChange(int _numero);
    void afficheTour();
    void solutionDesactivee();

};

#endif // VISUALISATION_H
