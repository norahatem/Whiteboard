#include "receiver.h"

Receiver::Receiver(QWidget *parent) : QMainWindow(parent)
{
    // set form size
    setMinimumSize(400,400);
    resize(400,400);
    setWindowTitle("Receiver");
}

void Receiver::mouseReleaseEvent(QMouseEvent * event)
{
    // get click position
    qDebug() << "Receiver window clicked: Mouse x " << event->x() << " Mouse y " << event->y();
}
