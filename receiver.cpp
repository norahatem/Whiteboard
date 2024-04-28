#include "receiver.h"

Receiver::Receiver(QWidget *parent) : QMainWindow(parent)
{
    // set form size
    setFixedSize(400,400);
//    resize(400,400);
    setWindowTitle("Receiver");
    drawingArea = new Whiteboard(this);
    setCentralWidget(drawingArea);
//    start();
    receiveThread = std::thread(&Receiver::readData, this);
}

void Receiver::readData(){
    while(true){
        int data = read();
        qDebug() << "\t\t\tReceived " << data;
        addPoint(data);
    }
}

void Receiver::addPoint(int coordinate){
    drawingArea->qLock.lock();
    coordinates.push(coordinate);
    drawingArea->qLock.unlock();
    if (coordinates.size() >= 2){
        drawingArea->qLock.lock();
        int tempx = coordinates.front();
        coordinates.pop();
        int tempy = coordinates.front();
        coordinates.pop();
        drawingArea->qLock.unlock();
        drawingArea->addPoint(QPoint(tempx, tempy));
    }
}
