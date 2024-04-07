#ifndef SENDER_H
#define SENDER_H
#include <QMouseEvent>
#include <QList>
#include <QMainWindow>

#include "scribblearea.h"

using namespace std;

class Sender: public QMainWindow
{
    Q_OBJECT
public:
    Sender(QWidget *parent = 0);

protected:
    void mouseReleaseEvent(QMouseEvent * event);

private:
    ScribbleArea *drawingArea;
};

#endif // SENDER_H
