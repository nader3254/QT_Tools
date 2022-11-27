#include "mainwindow.h"

#include <QApplication>

#include "udp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    udp *server =new udp("192.168.1.50",1234);
    while(1)
    {
       // char data[]="hello world ,iam qc c++";
       // server->send("192.168.1.50",data);
        dbg "readed :"<<server->read();
    }



    return a.exec();
}
