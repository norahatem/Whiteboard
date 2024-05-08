//This class represents the receiver window
//it has a receiver thread that keeps reeding from the gpio pins
//and sends them to the whiteboard/ calls the respective whiteboard function based on the received data to be displayed

#ifndef RECEIVER_H
#define RECEIVER_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QQueue>
#include <QPoint>
#include <ctime>

#include "whiteboard.h"
#include "drawingcmd.h"

using namespace std::literals::chrono_literals;

class Receiver: public QMainWindow
{
    Q_OBJECT
public:
    Receiver(QWidget *parent = 0);

protected:

private:
    Whiteboard *drawingArea;
    QQueue<DrawingCmd> receivedCommands;
    DrawingCmd cmd;
    std::thread receiveThread;
    void readData();
    void addCmd(DrawingCmd cmd);
};

#endif // RECEIVER_H
