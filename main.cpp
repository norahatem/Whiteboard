#include <QApplication>
#include <QWidget>

#include "receiver.h"
#include "sender.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Sender s;
    Receiver r;

    s.show();
    r.show();

    return app.exec();
}
