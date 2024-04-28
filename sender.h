#ifndef SENDER_H
#define SENDER_H
#include <QMouseEvent>
#include <QList>
#include <QMainWindow>


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
                drawingArea->qLock.lock();
                std::bitset<9> coordinate = sendData.front();
                sendData.pop();
                drawingArea->qLock.unlock();
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
                qDebug() << "Sending x " << point.x();
                send(point.x());
                qDebug() << "Sending y " << point.y();
                send(point.y());


            } else
                std::this_thread::sleep_for(100ms);
        }
    }


};

#endif // SENDER_H
