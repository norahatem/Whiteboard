#include "whiteboard.h"
#include <QDebug>


Whiteboard::Whiteboard(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setMinimumSize(400, 400);
    image = QPixmap(size());
    image.fill(Qt::white);
    start();
}

void Whiteboard::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QRect redrawRect = event->rect();
    painter.drawPixmap(redrawRect, image, redrawRect);
    painter.end();
}

void Whiteboard::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        drawing = true;
        currentPoint = event->pos();
        // draw a point everytime the mouse is presses
        qLock.lock();
        points.enqueue(event->pos());
        qLock.unlock();
        // paint(lastPoint, lastPoint);
        // paint();
    }
}

void Whiteboard::senderPaint(){
    qDebug() << currentPoint;
    if(points.empty())
        return;
    qLock.lock();
    lastPoint = points.dequeue();
    qLock.unlock();
    QPainter painter(&image);
    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    if(lastPoint == currentPoint)
        painter.drawPoint(lastPoint);
    painter.drawLine(lastPoint, currentPoint);
    currentPoint = lastPoint;
    // painter.drawPoint(lastPoint);
    painter.end();
    update();
}

void Whiteboard::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton && drawing){
        lastPoint = event->pos();
        qLock.lock();
        points.enqueue(lastPoint);
        qLock.unlock();
    }
}

void Whiteboard::mouseReleaseEvent(QMouseEvent *event){

    if(event->button() == Qt::LeftButton && drawing){
        drawing = false;
    }
}

void Whiteboard::resizeEvent(QResizeEvent *event){
    QPixmap newImage(size());
    newImage.fill(Qt::white);

    // Copy the existing content from the old pixmap to the new pixmap
    QPainter painter(&newImage);
    painter.drawPixmap(0, 0, image);
    image = newImage;
    painter.end();

    QWidget::resizeEvent(event);
}
