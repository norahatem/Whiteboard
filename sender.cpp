#include "sender.h"


Sender::Sender(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(400,400);
    setWindowTitle("Sender");
    drawingArea = new Whiteboard("Sender", this);
    setCentralWidget(drawingArea);
    senderThread = std::thread(&Sender::serialize, this);
}

void Sender::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        drawingArea->penDown(event->pos());
        drawingData.setCmd(2);
        drawingData.setXCoordinate(event->pos().x());
        drawingData.setYCoordinate(event->pos().y());
        drawingArea->qLock.lock();
//        sendPoints.enqueue(event->pos());
        sendCommands.enqueue(drawingData);
        drawingArea->qLock.unlock();
    }
}

void Sender::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        drawingArea->addPoint(event->pos());
        drawingData.setCmd(3);
        drawingData.setXCoordinate(event->pos().x());
        drawingData.setYCoordinate(event->pos().y());
        drawingArea->qLock.lock();
//        sendPoints.enqueue(event->pos());
        sendCommands.enqueue(drawingData);
        drawingArea->qLock.unlock();
    }
}

void Sender::mouseReleaseEvent(QMouseEvent *event){

    if(event->button() == Qt::LeftButton){
        drawingArea->penUp(event->pos());
        drawingData.setCmd(1);
        drawingData.setXCoordinate(event->pos().x());
        drawingData.setYCoordinate(event->pos().y());
        drawingArea->qLock.lock();
//        sendPoints.enqueue(event->pos());
        sendCommands.enqueue(drawingData);
        drawingArea->qLock.unlock();
    }
}

void Sender::serialize(){
    while (true) {
        if(!sendCommands.empty()){
            drawingArea->qLock.lock();
//            QPoint point = sendPoints.dequeue();
            DrawingCmd cmd = sendCommands.dequeue();
            drawingArea->qLock.unlock();
////            qDebug() << "Sending x " << point.x();
//            send(point.x());
////            qDebug() << "Sending y " << point.y();
//            send(point.y());
            send(cmd);
        } else
            std::this_thread::sleep_for(100ms);
    }
}

