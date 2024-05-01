#ifndef RECEIVER_H
#define RECEIVER_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QQueue>
#include <QPoint>
#include <ctime>
#include <queue>

#include "whiteboard.h"
#include "com.h"

using namespace std::literals::chrono_literals;

class Receiver: public QMainWindow
{
    Q_OBJECT
public:
    Receiver(QWidget *parent = 0);

protected:

private:
    Whiteboard *drawingArea;
//    QQueue<QPoint> receivePoints;
    QQueue<DrawingCmd> receivedCommands;
    DrawingCmd cmd;
//    std::queue<int> coordinates;
    std::thread receiveThread;
    void readData();
//    void addPoint(int coordinate);
    void addCmd(DrawingCmd cmd);
};

#endif // RECEIVER_H
