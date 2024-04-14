#include "sender.h"


Sender::Sender(QWidget *parent) : QMainWindow(parent)
{
    // set form size
    setMinimumSize(400,400);
    resize(400,400);
    setWindowTitle("Sender");
    drawingArea = new Whiteboard(&sendPoints, this);
    setCentralWidget(drawingArea);
}
