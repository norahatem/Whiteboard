#include "whiteboard.h"
#include <QDebug>


Whiteboard::Whiteboard(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setMinimumSize(400, 400);
    image = QPixmap(size());
    image.fill(Qt::white);
    paintThread = std::thread(&Whiteboard::painting, this);
//    start();
}

void Whiteboard::setPenColor(QColor newPenColor){
    penColor = newPenColor;
}

void Whiteboard::setPenSize(double newPenSize){
    penWidth = newPenSize;
}

void Whiteboard::clear(){
    image.fill(QColor("white"));
}

QColor Whiteboard::getPenColor() const{
    return penColor;
}

bool Whiteboard::getIsModified() const{
    return isModified;
}

double Whiteboard::getPenWidth() const{
    return penWidth;
}

void Whiteboard::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QRect redrawRect = event->rect();
    painter.drawPixmap(redrawRect, image, redrawRect);
    painter.end();
}

void Whiteboard::paint(QPoint point){
    QPainter painter(&image);
    painter.setPen(pen);
    if(lastPoint == point)
        painter.drawPoint(point);
    else
        painter.drawLine(lastPoint, point);
    lastPoint=point;
    painter.end();
    update();
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

void Whiteboard::addPoint(QPoint point){
    qLock.lock();
    points.enqueue(point);
    qLock.unlock();
}

void Whiteboard::penUp(QPoint point){
    this->addPoint(point);
}

void Whiteboard::penDown(QPoint point){
    lastPoint = point;
    this->addPoint(lastPoint);
}
