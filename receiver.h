#ifndef RECEIVER_H
#define RECEIVER_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QQueue>
#include <QPoint>
#include "whiteboard.h"

class Receiver: public QMainWindow, public QThread
{
    // Q_OBJECT
    void run() override{
        while(true){
            QThread::sleep(1);
            QPoint point = QPoint(rand()%400, rand()%400);
            drawingArea->addPoint(point);
            qDebug() << "receiver: " << point;
        }
    }
public:
    Receiver(QQueue<QPoint> *receiveQ, QWidget *parent = 0);

protected:

private:
    Whiteboard *drawingArea;
    QQueue<QPoint> receivePoints;
};

#endif // RECEIVER_H
