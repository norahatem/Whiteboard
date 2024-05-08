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

int Whiteboard::getPenWidth() const{
    return penWidth;
}

void Whiteboard::paintEvent(QPaintEvent *event){
    paint();

    QPainter painter(this);
    QRect redrawRect = event->rect();
    painter.drawPixmap(redrawRect, image, redrawRect);
    painter.end();
}

void Whiteboard::paint(){
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
}

void Whiteboard::resizeEvent(QResizeEvent *event){
    if (event->size().width() > image.width() || event->size().height() > image.height()) {
        // If the new size is larger, create a new pixmap and copy existing content
        QPixmap newImage(event->size());
        newImage.fill(Qt::white);
        QPainter painter(&newImage);
        painter.drawPixmap(0, 0, image);
        painter.end();
        // Update the image with the new pixmap
        image = newImage;
    }

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

void Whiteboard::painting(){
    while (true) {
        if(!points.empty()){
            qLock.lock();
            update();
            qLock.unlock();
        }
        std::this_thread::sleep_for(50ms);
    }
}
