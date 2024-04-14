#ifndef RECEIVER_H
#define RECEIVER_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QQueue>
#include <QPoint>

class Receiver: public QMainWindow
{
    Q_OBJECT
public:
    Receiver(QQueue<QPoint> *rPoints, QWidget *parent = 0);

protected:
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // RECEIVER_H
