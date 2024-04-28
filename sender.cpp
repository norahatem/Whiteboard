#include "sender.h"


Sender::Sender(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(400,400);
    setWindowTitle("Sender");
    drawingArea = new Whiteboard(this);
    setCentralWidget(drawingArea);
    senderThread = std::thread(&Sender::serialize, this);
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

void Sender::serialize(){
    while (true) {
        if(!sendPoints.empty()){
            drawingArea->qLock.lock();
            QPoint point = sendPoints.dequeue();
            drawingArea->qLock.unlock();
            qDebug() << "Sending x " << point.x();
            send(point.x());
            qDebug() << "Sending y " << point.y();
            send(point.y());
        } else
            std::this_thread::sleep_for(100ms);
    }
}

