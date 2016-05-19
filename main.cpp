#include <QCoreApplication>
#include <Meeting.h>

#include "testindividu.h"

int main(int argc, char *argv[])
{


    QCoreApplication a(argc, argv);

    Meeting& meeting = Meeting::getInstance();

    meeting.obtGroupeManager().ajouterGroupe("Groupe 1", 1);
    meeting.obtGroupeManager().ajouterGroupe("Groupe 2");

    QList<QString> grou;
    grou.append("Groupe 1");
    grou.append("Groupe 2");

    meeting.ajoutIndividu("Antoine", "Jouglet", grou);

    meeting.obtGroupeManager().defInteret(meeting.obtIndividus().first().obtGroupes().first(), meeting.obtIndividus().first().obtGroupes().last(), 2);

    qDebug() << meeting.obtGroupeManager().obtInteret(meeting.obtIndividus().first().obtGroupes().first(), meeting.obtIndividus().first().obtGroupes().last());

    qDebug() << meeting.obtGroupeManager().obtInteret(meeting.obtIndividus().first().obtGroupes().last(), meeting.obtIndividus().first().obtGroupes().last());

    meeting.obtGroupeManager().retirerGroupe(meeting.obtGroupeManager().obtGroupeParId(1));


    qDebug() << meeting.obtGroupeManager().obtInteret(meeting.obtIndividus().first().obtGroupes().first(), meeting.obtIndividus().first().obtGroupes().last());


    return a.exec();
}
