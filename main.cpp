#include <QApplication>
#include <QWidget>

#include "receiver.h"
#include "sender.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQueue<QPoint> points;
    Sender s;
    Receiver r( &points);

    r.show();
    s.show();

    return app.exec();
}
