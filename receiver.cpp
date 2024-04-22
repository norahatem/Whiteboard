#include "receiver.h"

Receiver::Receiver(QQueue<QPoint> *receiveQ, QWidget *parent) : QMainWindow(parent)
{
    // set form size
    setMinimumSize(400,400);
    resize(400,400);
    setWindowTitle("Receiver");
    drawingArea = new Whiteboard(this);
    setCentralWidget(drawingArea);
    start();
}

