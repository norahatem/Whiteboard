#ifndef RECEIVER_H
#define RECEIVER_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QQueue>
#include <QPoint>
#include <ctime>

#include "whiteboard.h"
#include "com.h"

class Receiver: public QMainWindow
{
    Q_OBJECT
//    void run() override{
//        srand(time(0));
//        while(true){
//            QThread::sleep(5);
//            QPoint point = QPoint(rand()%400, rand()%400);
//            drawingArea->addPoint(point);
//            qDebug() << "receiver: " << point;
//        }
//    }
public:
//    Receiver(QQueue<QPoint> *receiveQ, QWidget *parent = 0);
    Receiver(QWidget *parent = 0);

protected:

private:
    Whiteboard *drawingArea;
    QQueue<QPoint> receivePoints;
    std::thread receiveThread;
    std::thread runThread;
    void runner(){
        srand(time(0));
        while(true){
            delayMicroseconds(1000000);
            QPoint point = QPoint(rand()%400, rand()%400);
            drawingArea->addPoint(point);
//            qDebug() << "receiver: " << point;
        }
    }
};

#endif // RECEIVER_H
