#ifndef SENDER_H
#define SENDER_H
#include <QMouseEvent>
#include <QList>
#include <QMainWindow>

#include "scribblearea.h"
#include "whiteboard.h"

using namespace std;

class Sender: public QMainWindow
{
    Q_OBJECT
public:
    Sender(QWidget *parent = 0);

protected:


private slots:

private:
    Whiteboard *drawingArea;
    QQueue<QPoint> sendPoints;
    QMutex sMutex;

};

#endif // SENDER_H
