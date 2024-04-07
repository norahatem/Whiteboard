#include "sender.h"


Sender::Sender(QWidget *parent) : QMainWindow(parent)
{
    // set form size
    setMinimumSize(400,400);
    resize(400,400);
    setWindowTitle("Sender");
    drawingArea = new ScribbleArea(this);
    setCentralWidget(drawingArea);
}

void Sender::mouseReleaseEvent(QMouseEvent * event)
{
    // get click position
    qDebug() << "Sender window clicked: Mouse x " << event->x() << " Mouse y " << event->y();
}
