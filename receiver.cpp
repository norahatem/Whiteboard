#include "receiver.h"

Receiver::Receiver(QWidget *parent) : QMainWindow(parent)
{
    // set form size
    setMinimumSize(400,400);
    resize(400,400);
    setWindowTitle("Receiver");
    drawingArea = new Whiteboard("Receiver",this);
    setCentralWidget(drawingArea);
//    start();
    receiveThread = std::thread(&Receiver::readData, this);
}

void Receiver::readData(){
//    DrawingCmd dataPacket;
    std::bitset<40> dataRead;
    std::bitset<8> command;
    std::bitset<16> x;
    std::bitset<16> y;
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
        case 0:
            qDebug() << "Clear\n";
            drawingArea->clear();
            break;
        case 1:
            qDebug() << "PenUp\n";
            drawingArea->penUp(QPoint(temp.getX().to_ulong(), temp.getY().to_ulong()));
            break;
        case 2:
            qDebug() << "PenDown\n";
            drawingArea->penDown(QPoint(temp.getX().to_ulong(), temp.getY().to_ulong()));
            break;
        case 3:
            qDebug() << "AddPoint\n";
            drawingArea->addPoint(QPoint(temp.getX().to_ulong(), temp.getY().to_ulong()));
            break;
        case 4:
            QColor pCol = QColor(temp.getRed().to_ulong(), temp.getGreen().to_ulong(), temp.getBlue().to_ulong());
            qDebug() << pCol;
            drawingArea->setPenColor(pCol);
            break;
        }
    }
}
