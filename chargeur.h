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
protected:
    Meeting& meeting;
public:
    chargeur(Meeting& _meeting);
    virtual void chargeMeeting(QString _chemin)=0;
    virtual void chargeSolution(QString _chemin)=0;
    virtual void sauveMeeting(QString _chemin)=0;

};

class parseurXml : public chargeur
{
public:
    parseurXml(Meeting& _meeting);
    void chargeMeeting(QString _chemin);
    void chargeSolution(QString _chemin);
    void sauveMeeting(QString _chemin);
};

#endif // CHARGEUR_H
