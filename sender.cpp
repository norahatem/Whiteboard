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
    start();

}

void Sender::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        drawingArea->penDown(event->pos());
    }
}

void Sender::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        drawingArea->addPoint(event->pos());
    }
}

void Sender::mouseReleaseEvent(QMouseEvent *event){

    if(event->button() == Qt::LeftButton){
        drawingArea->penUp(event->pos());
    }
}
