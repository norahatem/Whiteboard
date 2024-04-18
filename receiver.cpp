#include "receiver.h"

Receiver::Receiver(QQueue<QPoint> *receiveQ, QWidget *parent) : QMainWindow(parent)
{
    // set form size
    setMinimumSize(400,400);
    resize(400,400);
    setWindowTitle("Receiver");
    // QPalette pal = QPalette();
    // pal.setColor(QPalette::Window, QColor("#FFFFFF"));
    // setPalette(pal);
    drawingArea = new Whiteboard(&receivePoints, this);
    drawingArea->setIntercative(false);
    setCentralWidget(drawingArea);
}

void Receiver::mouseReleaseEvent(QMouseEvent * event)
{
    // get click position
    qDebug() << "Receiver window clicked: Mouse x " << event->x() << " Mouse y " << event->y();
}
