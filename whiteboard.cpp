#include "whiteboard.h"
#include <QDebug>


Whiteboard::Whiteboard(QQueue<QPoint> *sendQ, QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setMinimumSize(400, 400);
    image = QPixmap(size());
    image.fill(Qt::white);
    sPoints = sendQ;
    start();
}

void Whiteboard::setPenColor(QColor newPenColor){
    penColor = newPenColor;
}

void Whiteboard::setPenSize(double newPenSize){
    penWidth = newPenSize;
}

void Whiteboard::clear(){
    // clear the whole queue
    points.clear();
}


void Whiteboard::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QRect redrawRect = event->rect();
    painter.drawPixmap(redrawRect, image, redrawRect);
    painter.end();
}



void Whiteboard::paint(QPoint point){
    // qDebug() << currentPoint;
    // if(points.empty())
    //     return;
    // qLock.lock();
    // lastPoint = points.dequeue();
    // qLock.unlock();
    QPainter painter(&image);
    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    if(lastPoint == point){

        painter.drawPoint(point);
    }
    else{
        painter.drawLine(lastPoint, point);
    }

    lastPoint=point;
    // painter.drawPoint(lastPoint);
    painter.end();
    update();
}

// void Whiteboard::mouseMoveEvent(QMouseEvent *event){
//     if(event->buttons() & Qt::LeftButton && drawing){
//         lastPoint = event->pos();
//         qLock.lock();
//         points.enqueue(lastPoint);
//         sPoints->enqueue(lastPoint);
//         qLock.unlock();
//     }
// }

// void Whiteboard::mouseReleaseEvent(QMouseEvent *event){

//     if(event->button() == Qt::LeftButton && drawing){
//         drawing = false;
//     }
// }

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

void Whiteboard::setIntercative(bool isInteractive){
    interactive = isInteractive;
}

void Whiteboard::addPoint(QPoint point){
    qLock.lock();
    points.enqueue(point);
    qLock.unlock();
}

void Whiteboard::penUp(QPoint point){
    // drawing = false;
    this->addPoint(point);
}

void Whiteboard::penDown(QPoint point){
    // drawing = true;
    lastPoint = point;
    this->addPoint(lastPoint);
}
