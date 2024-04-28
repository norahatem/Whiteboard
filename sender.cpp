#include "sender.h"


Sender::Sender(QWidget *parent) : QMainWindow(parent)
{
    // set form size
    setFixedSize(400,400);
//    resize(400,400);
    setWindowTitle("Sender");
//    sendPoints = *sendQ;
    drawingArea = new Whiteboard(this);
    setCentralWidget(drawingArea);
//    start();
    senderThread = std::thread(&Sender::sendbits, this);
    serializeThread = std::thread(&Sender::serialize, this);
}

void Sender::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        drawingArea->penDown(event->pos());
        drawingArea->qLock.lock();
        sendPoints.enqueue(event->pos());
        drawingArea->qLock.unlock();
    }
}

void Sender::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        drawingArea->addPoint(event->pos());
        drawingArea->qLock.lock();
        sendPoints.enqueue(event->pos());
        drawingArea->qLock.unlock();
    }
}

void Sender::mouseReleaseEvent(QMouseEvent *event){

    if(event->button() == Qt::LeftButton){
        drawingArea->penUp(event->pos());
        drawingArea->qLock.lock();
        sendPoints.enqueue(event->pos());
        drawingArea->qLock.unlock();
    }
}


