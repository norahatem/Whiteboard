#ifndef RECEIVER_H
#define RECEIVER_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QQueue>
#include <QPoint>
#include <ctime>

#include "whiteboard.h"
#include "com.h"

using namespace std::literals::chrono_literals;

class Receiver: public QMainWindow
{
    Q_OBJECT
public:
//    Receiver(QQueue<QPoint> *receiveQ, QWidget *parent = 0);
    Receiver(QWidget *parent = 0);

protected:

private:
    Whiteboard *drawingArea;
    QQueue<QPoint> receivePoints;
    std::thread receiveThread;
    std::thread runThread;
    void readData(){
        while(true){
//            std::bitset<9> data;
            int data = read();
            qDebug() << "\t\t\tReceived " << data;
        }

    }
};

#endif // RECEIVER_H
