#include <QCoreApplication>
#include "webserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    webServer ws;
    ws.start();
    ws.SetPage("working 100% ......");

    return a.exec();
}
