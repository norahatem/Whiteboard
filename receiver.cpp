#include "receiver.h"

Receiver::Receiver(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(400,400);
    resize(400,400);
    setWindowTitle("Receiver");
    drawingArea = new Whiteboard(this);
    setCentralWidget(drawingArea);
    receiveThread = std::thread(&Receiver::readData, this);
}

void Receiver::readData(){
    while(true){
        cmd.receive();
        addCmd(cmd);
    }
}

void Receiver::addCmd(DrawingCmd cmd){
    DrawingCmd temp;
    drawingArea->qLock.lock();
    receivedCommands.enqueue(cmd);
    drawingArea->qLock.unlock();
    if(!receivedCommands.empty()){
        temp = receivedCommands.dequeue();
        switch (temp.getCmd()) {
        case CLEAR:
            drawingArea->clear();
            break;
        case PEN_UP:
            drawingArea->penUp(QPoint(temp.getX(), temp.getY()));
            break;
        case PEN_DOWN:
            drawingArea->penDown(QPoint(temp.getX(), temp.getY()));
            break;
        case ADD_POINT:
            drawingArea->addPoint(QPoint(temp.getX(), temp.getY()));
            break;
        case CHANGE_PEN_WIDTH:
            drawingArea->setPenSize(temp.getPenWidth());
            break;
        case CHANGE_PEN_COLOR:
            QColor pCol = QColor(temp.getRed(), temp.getGreen(), temp.getBlue());
            drawingArea->setPenColor(pCol);
            break;
        }
    }
}
