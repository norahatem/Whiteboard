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

//function tht takes the command and the point ad sets the commands and enqueue it to the queue
//this is made possible since they all send x and y coordinates but only the command is different
void Sender::sendCmd(int cmd, QPoint point) {
    drawingData.setCmd(cmd);
    qDebug() << "Actual point " << point;
    if ((point.x() >= 0) && (point.y() >= 0)) {
        drawingData.setXCoordinate(point.x());
        drawingData.setYCoordinate(point.y());

    }else{
        if(point.x() < 0){
            drawingData.setXCoordinate((-1*point.x()+32768));
        }
        if(point.y() < 0)
            drawingData.setYCoordinate((-1*point.y()+32768));
    }
    qDebug() << "\t Sent point" << drawingData.getX() << " " << drawingData.getY();
    drawingArea->qLock.lock();
    sendCommands.enqueue(drawingData);
    drawingArea->qLock.unlock();
}

//override mouse events here to implement the drawing with mouse

void Sender::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        drawingArea->penDown(event->pos());
        sendCmd(PEN_DOWN, event->pos());
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
    //clears its board and sets the command to be sent
    drawingArea->clear();
    drawingData.setCmd(CLEAR);
    drawingArea->qLock.lock();
    sendCommands.enqueue(drawingData);
    drawingArea->qLock.unlock();
}

void Sender::ChangePenColor(QColor newPenColor){
    //set the pen colour and set the drawing command to be sent
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
    //set the pen size for its drawing board
    drawingArea->setPenSize(newPenWidth);
    //set the drawing command to be sent to the receiver and adds it to the queue
    drawingData.setCmd(CHANGE_PEN_WIDTH);
    drawingData.setPenWidth(newPenWidth);
    drawingArea->qLock.lock();
    sendCommands.enqueue(drawingData);
    drawingArea->qLock.unlock();
}

void Sender::serialize(){
    //thread function to send all drawing commands to GPIO pins
    while (true) {
        if(!sendCommands.empty()){
            drawingArea->qLock.lock();
            DrawingCmd cmd = sendCommands.dequeue();
            drawingArea->qLock.unlock();
            //drawing command method
            cmd.send();
        } else
            std::this_thread::sleep_for(100ms);
    }
}

