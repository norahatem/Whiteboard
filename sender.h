#ifndef SENDER_H
#define SENDER_H
#include <QMouseEvent>
#include <QList>
#include <QMainWindow>


#include <iostream>
#include <bitset>
#include <queue>
#include <thread>

#include "whiteboard.h"
#include "com.h"



using namespace std;
using namespace std::literals::chrono_literals;
class Sender: public QMainWindow
{
     Q_OBJECT
//    void run() override {
//        while (true) {
//            qDebug() << "Hi from the sender";
//            QThread::sleep(5);
//        }
//    }

public:
//    Sender(QQueue<QPoint> *sendQ, QWidget *parent = 0);
    Sender(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;

private slots:

private:
    Whiteboard *drawingArea;
    QQueue<QPoint> sendPoints;
    std::queue<bitset<9>> sendData;
    std::thread senderThread;
    std::thread serializeThread;
    void sendbits(){
        while(true){
            if(!sendData.empty()){
                std::bitset<9> coordinate = sendData.front();
                sendData.pop();
                for(int i = 0; i<coordinate.size() ; i++){
                    send(coordinate[i]);
                }
            }else
                std::this_thread::sleep_for(100ms);
        }
    }
    void serialize(){
        while (true) {
            if(!sendPoints.empty()){
                drawingArea->qLock.lock();
                QPoint point = sendPoints.dequeue();
                drawingArea->qLock.unlock();
                std::bitset<9> x_coordinate = point.x();
                std::bitset<9> y_coordinate = point.y();
                drawingArea->qLock.lock();
                sendData.push(x_coordinate);
                sendData.push(y_coordinate);
                drawingArea->qLock.unlock();
                qDebug() << "x: " << point.x() << "  y: " << point.y();
                qDebug() << "x: " << QString::fromStdString(x_coordinate.to_string())
                        << "  y: " << QString::fromStdString(y_coordinate.to_string()) << "\n";
                bool sent = false;
            } else
                std::this_thread::sleep_for(100ms);
        }
    }

};

#endif // SENDER_H
