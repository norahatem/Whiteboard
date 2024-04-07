#ifndef RECEIVER_H
#define RECEIVER_H

#include <QMainWindow>
#include <QMouseEvent>

class Receiver: public QMainWindow
{
    Q_OBJECT
public:
    Receiver(QWidget *parent = 0);

protected:
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // RECEIVER_H
