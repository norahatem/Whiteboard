#ifndef SENDER_H
#define SENDER_H
#include <QMouseEvent>
#include <QList>
#include <QMainWindow>


#include <queue>
#include <thread>

#include "whiteboard.h"
#include "com.h"
#include "drawingcmd.h"

using namespace std;
using namespace std::literals::chrono_literals;
class Sender: public QMainWindow
{
     Q_OBJECT
public:
//    Sender(QQueue<QPoint> *sendQ, QWidget *parent = 0);
    Sender(QWidget *parent = 0);
    Whiteboard *drawingArea;


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;

public slots:
    void clearBoard();
private:
//    QQueue<QPoint> sendPoints;
    QQueue<DrawingCmd> sendCommands;
    DrawingCmd drawingData;
    std::thread senderThread;
    void serialize();
    DrawingCmd cmd;
};

#endif // SENDER_H
