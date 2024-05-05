#include "whiteboard.h"
#include <QDebug>


Whiteboard::Whiteboard(QString name, QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setMinimumSize(400, 400);
    image = QPixmap(size());
    image.fill(Qt::white);
    paintThread = std::thread(&Whiteboard::painting, this);
    boardName = name;
}

void Whiteboard::setPenColor(QColor newPenColor){
    penColor = newPenColor;
    pen.setColor(penColor);
}

void Whiteboard::setPenSize(int newPenSize){
    penWidth = newPenSize;
    pen.setWidth(newPenSize);
}

void Whiteboard::clear(){
    image.fill(QColor("white"));
    update();
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

    QPainter imgPainter(&image);
    while(!points.empty()){
            qLock.lock();
            QPoint point = points.dequeue();
            qLock.unlock();
            imgPainter.setPen(pen);
            if(lastPoint == point)
                imgPainter.drawPoint(point);
            else
                imgPainter.drawLine(lastPoint, point);
            lastPoint=point;


        }
        imgPainter.end();



    QPainter painter(this);
    QRect redrawRect = event->rect();
    painter.drawPixmap(redrawRect, image, redrawRect);
    painter.end();
}

void Whiteboard::paint(QPoint point){
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
