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
    //thread function to raed th drawing commands
    while(true){
        //drawing command method
        cmd.receive();
        //call add command function
        addCmd(cmd);
    }
}

void Receiver::addCmd(DrawingCmd cmd){
    DrawingCmd temp;
    int16_t x, y;
    drawingArea->qLock.lock();
    receivedCommands.enqueue(cmd);
    drawingArea->qLock.unlock();
    //this function checks teh command value and calls the appropriate function basd on this
    //with the appropriate variables

    if(!receivedCommands.empty()){
        temp = receivedCommands.dequeue();
        // minus that number to remove the msb and get the actual value
        //so if the value is positive it stays +ve if its -ve it will be -ve here
        x = temp.getX() - 32768;
        y = temp.getY() - 32768;
        switch (temp.getCmd()) {
        case CLEAR:
            drawingArea->clear();
            break;
        case PEN_UP:
            qDebug() << "\t\t\t" << x << " " << y;
            drawingArea->penUp(QPoint(x, y));
            break;
        case PEN_DOWN:
            qDebug() << "\t\t\t" << x << " " << y;
            drawingArea->penDown(QPoint(x, y));
            break;
        case ADD_POINT:
            qDebug() << "\t\t\t" << x << " " << y;
            drawingArea->addPoint(QPoint(x, y));
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
