#include "sender.h"

Sender::Sender(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(400,400);
    resize(400,400);
    setWindowTitle("Sender");
    drawingArea = new Whiteboard(this);
    setCentralWidget(drawingArea);
    senderThread = std::thread(&Sender::serialize, this);
}

void Sender::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        drawingArea->penDown(event->pos());
        sendCmd(PEN_DOWN, event->pos());
    }
}

void Sender::sendCmd(std::bitset<8> cmd, QPoint point) {
    if ((point.x() <= width() && point.x() >= 0) && (point.y() <= height() && point.y() >= 0)) {
        drawingData.setCmd(cmd);
        drawingData.setXCoordinate(point.x());
        drawingData.setYCoordinate(point.y());
        drawingArea->qLock.lock();
        sendCommands.enqueue(drawingData);
        drawingArea->qLock.unlock();
    }
}

void Sender::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        drawingArea->addPoint(event->pos());
        sendCmd(ADD_POINT, event->pos());
    }
}

void Sender::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        drawingArea->penUp(event->pos());
        sendCmd(PEN_UP, event->pos());
    }
}

void Sender::clearBoard(){
    drawingArea->clear();
    drawingData.setCmd(CLEAR);
    drawingArea->qLock.lock();
    sendCommands.enqueue(drawingData);
    drawingArea->qLock.unlock();
}

void Sender::ChangePenColor(QColor newPenColor){
    drawingArea->setPenColor(newPenColor);
    drawingData.setCmd(CHANGE_PEN_COLOR);
    drawingData.setRed(newPenColor.red());
    drawingData.setGreen(newPenColor.green());
    drawingData.setBlue(newPenColor.blue());
    drawingArea->qLock.lock();
    sendCommands.enqueue(drawingData);
    drawingArea->qLock.unlock();
}

void Sender::changePenWidth(int newPenWidth){
    drawingArea->setPenSize(newPenWidth);
    drawingData.setCmd(CHANGE_PEN_WIDTH);
    drawingData.setPenWidth(newPenWidth);
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

