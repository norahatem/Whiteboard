#include "sender.h"
#include <QMenu>
#include <QMenuBar>

Sender::Sender(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(400,400);
    resize(400,400);
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
        sendCommands.enqueue(drawingData);
        drawingArea->qLock.unlock();
    }
}

void Sender::clearBoard(){
    drawingArea->clear();
    drawingData.setCmd(0);
    drawingArea->qLock.lock();
    sendCommands.enqueue(drawingData);
    drawingArea->qLock.unlock();
}

void Sender::ChangePenColor(QColor newPenColor){
    drawingArea->setPenColor(newPenColor);
    drawingData.setCmd(4);
    drawingData.setRed(newPenColor.red());
    drawingData.setGreen(newPenColor.green());
    drawingData.setBlue(newPenColor.blue());
    drawingArea->qLock.lock();
    sendCommands.enqueue(drawingData);
    drawingArea->qLock.unlock();
}

void Sender::serialize(){
    while (true) {
        if(!sendCommands.empty()){
            drawingArea->qLock.lock();
            DrawingCmd cmd = sendCommands.dequeue();
            drawingArea->qLock.unlock();
            cmd.send();
        } else
            std::this_thread::sleep_for(100ms);
    }
}

