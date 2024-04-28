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
    QQueue<QPoint> points;

    MainWindow mainW;
    mainW.show();
    return app.exec();
}
