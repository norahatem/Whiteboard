#include <QApplication>
#include "receiver.h"
#include "sender.h"
#include <thread>

#include "mainwindow.h"
#include "com.h"


int main(int argc, char *argv[])
{
    initRpi();
    QApplication app(argc, argv);

    MainWindow mainW;
    mainW.show();
//    Sender send;
//    Receiver receive;
//    send.show();
//    receive.show();
    return app.exec();
}
