#include <QApplication>
#include "receiver.h"
#include "sender.h"

#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQueue<QPoint> points;

    // Sender sender(&points);
    // Receiver receiver(&points);
    // sender.show();
    // receiver.show();
    MainWindow mainW;
    mainW.show();
    return app.exec();
}
