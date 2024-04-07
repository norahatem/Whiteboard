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
}

void Whiteboard::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        drawing = true;
        lastPoint = event->pos();

    }
}

void Whiteboard::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton && drawing){
        QPainter painter(&image);
        painter.setPen(QPen(Qt::black, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(lastPoint, event->pos());
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
    image = QPixmap(size());
    image.fill(Qt::white);
    QWidget::resizeEvent(event);
}
