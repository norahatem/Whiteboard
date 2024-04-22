#ifndef SENDER_H
#define SENDER_H
#include <QMouseEvent>
#include <QList>
#include <QMainWindow>

#include "scribblearea.h"
#include "whiteboard.h"

using namespace std;

class Sender: public QMainWindow, public QThread
{
    // Q_OBJECT
    void run() override {
        while (true) {
            if(!sendPoints.empty()){
                drawingArea->qLock.lock();
                // QPoint point = sendPoints.dequeue();
                // sendPoints.enqueue(se)
                // drawingArea->qLock.unlock();
            }
            // QThread::msleep(100);
            qDebug() << "Hi from the sender\n";
            QThread::sleep(5);
        }

    }
public:
    Sender(QQueue<QPoint> *sendQ, QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;

private slots:

private:
    Whiteboard *drawingArea;
    QQueue<QPoint> sendPoints;
    // QMutex sMutex;

};

#endif // SENDER_H
