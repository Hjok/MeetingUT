#ifndef CHARGEUR_H
#define CHARGEUR_H
#include "Meeting.h"
#include <QObject>
#include <QtXml>
#include <QFile>
#include <QString>
#include <iostream>

class chargeur
{
private:
    Meeting& meeting;
public:
    explicit chargeur(Meeting& _meeting);
    void chargeMeeting(QString _chemin);
    void chargeSolution(QString _chemin);
    void sauveMeeting(QString _chemin);

signals:

public slots:
};

#endif // CHARGEUR_H
