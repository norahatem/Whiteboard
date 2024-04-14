#include "whiteboard.h"
#include <QDebug>


Whiteboard::Whiteboard(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setMinimumSize(400, 400);
    image = QPixmap(size());
    image.fill(Qt::white);
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
        lastPoint = event->pos();
        // draw a point everytime the mouse is presses
        // points.enqueue(lastPoint);
        pPoint(lastPoint);
        update();
    }
}

void Whiteboard::pPoint(QPoint pointToDraw){
    QPainter painter(&image);
    painter.setPen(QPen(penColor, penWidth));
    painter.drawPoint(lastPoint);
    painter.end();
    qDebug() << pointToDraw;
}

void Whiteboard::pLine(QPoint lastPoint, QPoint currentPoint){
    QPainter painter(&image);
    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, currentPoint);
    painter.end();
    qDebug() << lastPoint << " " << currentPoint;
}

void Whiteboard::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton && drawing){
        pLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
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
