#include "receiver.h"

Receiver::Receiver(QWidget *parent) : QMainWindow(parent)
{
    // set form size
    setFixedSize(400,400);
//    resize(400,400);
    setWindowTitle("Receiver");
    drawingArea = new Whiteboard(this);
    setCentralWidget(drawingArea);
//    start();
    receiveThread = std::thread(&Receiver::readData, this);
//    runThread = std::thread(&Receiver::runner, this);
}
