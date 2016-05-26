#ifndef VISUALISATION_H
#define VISUALISATION_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QTableView>
class Visualisation : public QWidget
{
    Q_OBJECT
public:
    explicit Visualisation(QWidget *parent = 0);

private:
    QTableView* personnesNonPlacees;
    int numero;

signals:

public slots:
private slots:
    void solutionAffiche();
    void tourChange(int _numero);

};

#endif // VISUALISATION_H
