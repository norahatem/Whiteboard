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

class Whiteboard: public QWidget
{
public:
    explicit Whiteboard(QWidget *parent = nullptr);

protected:
    // override these functions to handle drawings
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    // paint event
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    bool drawing;
    QPoint lastPoint, currentPoint;
    void paint(QPoint lastPoint, QPoint currentPoint);
    // off class image to handle drawing
    QPixmap image;
    // QVector<QPoint> points;
    QColor penColor = "Black";
    double penWidth = 3.5;
    QQueue<QPoint> points;
};

#endif // WHITEBOARD_H
