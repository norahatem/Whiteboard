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
        dataRead = read();
        for(int i = 0; i<8; i++){
            command[i] = dataRead[i];
        }
        cmd.setCmd((int) command.to_ulong());
        if(cmd.getCmd() != 0){
            for(int i = 8; i<24; i++){
                x[i-8] = dataRead[i];
            }
            for(int i = 24; i<40;i++){
                y[i-24] = dataRead[i];
            }
            cmd.setXCoordinate((int) x.to_ulong());
            cmd.setYCoordinate((int) y.to_ulong());

        }

//        drawingArea->qLock.lock();
//        receivedCommands.enqueue(cmd);
//        drawingArea->qLock.unlock();
        addCmd(cmd);
    }
}

void Receiver::addCmd(DrawingCmd cmd){
    DrawingCmd temp;
    drawingArea->qLock.lock();
//    coordinates.push(coordinate);
    receivedCommands.enqueue(cmd);
    drawingArea->qLock.unlock();
//    if (coordinates.size() >= 2){
//        drawingArea->qLock.lock();
//        int tempx = coordinates.front();
//        coordinates.pop();
//        int tempy = coordinates.front();
//        coordinates.pop();
//        drawingArea->qLock.unlock();
//        drawingArea->addPoint(QPoint(tempx, tempy));
//    }
    if(!receivedCommands.empty()){
        temp = receivedCommands.dequeue();
        switch (temp.getCmd()) {
        case 0:
            drawingArea->clear();
            break;
        case 1:
            drawingArea->penUp(QPoint(temp.getX(), temp.getY()));
            break;
        case 2:
            drawingArea->penDown(QPoint(temp.getX(), temp.getY()));
            break;
        case 3:
            drawingArea->addPoint(QPoint(temp.getX(), temp.getY()));
        }
    }
}
