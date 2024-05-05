#include "receiver.h"

Receiver::Receiver(QWidget *parent) : QMainWindow(parent)
{
    // set form size
    setMinimumSize(400,400);
    resize(400,400);
    setWindowTitle("Receiver");
    drawingArea = new Whiteboard("Receiver",this);
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
        switch (temp.getCmd().to_ulong()) {
        case CLEAR:
//            qDebug() << "Clear\n";
            drawingArea->clear();
            break;
        case PEN_UP:
//            qDebug() << "PenUp\n";
            drawingArea->penUp(QPoint(temp.getX().to_ulong(), temp.getY().to_ulong()));
            break;
        case PEN_DOWN:
//            qDebug() << "PenDown\n";
            drawingArea->penDown(QPoint(temp.getX().to_ulong(), temp.getY().to_ulong()));
            break;
        case ADD_POINT:
//            qDebug() << "AddPoint\n";
            drawingArea->addPoint(QPoint(temp.getX().to_ulong(), temp.getY().to_ulong()));
            break;
        case CHANGE_PEN_WIDTH:
            drawingArea->setPenSize(temp.getPenWidth());
            break;
        case CHANGE_PEN_COLOR:
            QColor pCol = QColor(temp.getRed().to_ulong(), temp.getGreen().to_ulong(), temp.getBlue().to_ulong());
//            qDebug() << pCol;
            drawingArea->setPenColor(pCol);
            break;
        }
    }
}
