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
    std::thread senderThread;
    void serialize();


};

#endif // SENDER_H
