#ifndef RECEIVER_H
#define RECEIVER_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QQueue>
#include <QPoint>
#include "whiteboard.h"

class Receiver: public QMainWindow
{
    Q_OBJECT
public:
    Receiver(QQueue<QPoint> *receiveQ, QWidget *parent = 0);

protected:
    void mouseReleaseEvent(QMouseEvent * event);

private:
    Whiteboard *drawingArea;
    QQueue<QPoint> receivePoints;
};

#endif // RECEIVER_H
