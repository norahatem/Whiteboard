#ifndef WHITEBOARD_H
#define WHITEBOARD_H

// to handle graphics and drawings
#include <QPixmap>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>

#include <QColor>
#include <QPoint>
#include <QQueue>
#include <thread>
#include <QThread>
#include <QMutex>

class Whiteboard: public QWidget, public QThread
{
    void run() override {
        while (true) {
            if(!points.empty()){
                lastPoint = points.dequeue();
                paint(lastPoint);
            }
            // QThread::msleep(100);
        }
    }
public:
    explicit Whiteboard(QQueue<QPoint> *sendQ, QWidget *parent = nullptr);
    QMutex qLock;

protected:
    // override these functions to handle drawings
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    // paint event
    void paintEvent(QPaintEvent *event)override;
    void resizeEvent(QResizeEvent *event)override;

private:
    bool drawing;
    QPoint lastPoint, currentPoint;
    void paint(QPoint point);
    // off class image to handle drawing
    QPixmap image;
    // QVector<QPoint> points;
    QColor penColor = "Black";
    double penWidth = 3.5;
    QQueue<QPoint> points;
    QQueue<QPoint> *sPoints;
};

#endif // WHITEBOARD_H
