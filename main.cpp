
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window1;
    QWidget window2;
    window1.resize(450,450);
    window2.resize(450,450);
    window1.setWindowTitle("Sender");
    window2.setWindowTitle("Receiver");
    window1.show();
    window2.show();

    return app.exec();
}
