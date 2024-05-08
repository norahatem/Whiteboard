//this is the class that represents the whiteboard
//it receives points from any source using the commands penUp penDown addPoint
//and draws the points based on this
//it also has setter and getter methods for the member variables like the color and width
//these are used to implement different and more commands like changing with and color

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
#include <QMutex>
#include <QDebug>

#include <thread>
#include <iostream>

using namespace std::literals::chrono_literals;

class Whiteboard: public QWidget
{

public:
    explicit Whiteboard(QWidget *parent = nullptr);
    QMutex qLock;
    void setPenColor(QColor newColor);
    void setPenSize(int newSize);

    QColor getPenColor() const;
    int getPenWidth() const;

    void addPoint(QPoint point);
    void penUp(QPoint point);
    void penDown(QPoint point);

public slots:
    void clear();

protected:
    void paintEvent(QPaintEvent *event)override;
    void resizeEvent(QResizeEvent *event)override;

private:
    QPoint lastPoint;
    void paint();
    // off class image to handle drawing
    QPixmap image;
    //initialize the values of color and pen width
    QColor penColor = "Black";
    int penWidth = 3;
    //points to be drawn
    QQueue<QPoint> points;
    QPen pen = QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    std::thread paintThread;
//    QString boardName;
    void painting();
};

#endif // WHITEBOARD_H
