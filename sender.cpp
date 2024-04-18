#include "sender.h"


Sender::Sender(QQueue<QPoint> *sendQ, QWidget *parent) : QMainWindow(parent)
{
    // set form size
    setMinimumSize(400,400);
    resize(400,400);
    setWindowTitle("Sender");
    sendPoints = *sendQ;
    drawingArea = new Whiteboard(&sendPoints, this);
    drawingArea->setIntercative(true);
    setCentralWidget(drawingArea);

}
