#ifndef CHARGEUR_H
#define CHARGEUR_H
#include "Meeting.h"
#include <QObject>
#include <QtXml>
#include <QFile>
#include <QString>
#include <iostream>

/*!
 * \brief La classe chargeur est l'interface d'entrée sortie
 *
 * Elle fournit les méthodes abstraites permettant de lire ou d'écrire les données d'un Meeting
 */
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
/*!
 * \brief La classe parseurXml implémente l'interface chargeur pour des fichiers xml
 */

class parseurXml : public chargeur
{
public:
    parseurXml(Meeting& _meeting);
    void chargeMeeting(QString _chemin);
    void chargeSolution(QString _chemin);
    void sauveMeeting(QString _chemin);
};

#endif // CHARGEUR_H
