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

    meeting.print();

    meeting.obtGroupeManager().print();

    meeting.obtGroupeManager().retirerGroupe(meeting.obtGroupeManager().obtGroupeParId(1));

    meeting.print();
    meeting.obtGroupeManager().print();


    return a.exec();
}
