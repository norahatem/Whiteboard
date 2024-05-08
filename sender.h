#ifndef SENDER_H
#define SENDER_H
#include <QMouseEvent>
#include <QList>
//this class represents the sender
//it also initializes a whiteboard and ovverrides the mouse events to implement the drawing on the board
//it also has a sender thread that collect the data and send them to the GPIO pins

#include <QMainWindow>

#include <QMenu>
#include <QMenuBar>

#include <thread>

#include "whiteboard.h"
#include "drawingcmd.h"

using namespace std;
using namespace std::literals::chrono_literals;
class Sender: public QMainWindow
{
    Q_OBJECT
public:
    Sender(QWidget *parent = 0);
    Whiteboard *drawingArea;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void clearBoard();
    void ChangePenColor(QColor newPenColor);
    void changePenWidth(int newPenWidth);
private:
    QQueue<DrawingCmd> sendCommands;
    DrawingCmd drawingData;
    std::thread senderThread;
    void serialize();
    DrawingCmd cmd;
    void sendCmd(int cmd, QPoint point);
};

#endif // SENDER_H
