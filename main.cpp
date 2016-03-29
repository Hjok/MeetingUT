#include <QCoreApplication>
#include <Meeting.h>

#include "testindividu.h"

int main(int argc, char *argv[])
{


    TestIndividu testIndividu;
        QTest::qExec(&testIndividu, argc, argv);
        return 0;
   /* QCoreApplication a(argc, argv);

    return a.exec();*/
}
