#include "whiteboard.h"
#include <QDebug>


Whiteboard::Whiteboard(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setMinimumSize(400, 400);
    //initialize a white blank image and show it
    image = QPixmap(size());
    image.fill(Qt::white);
    //initialize the painting thread
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
    //only fill the whol thing with white
    image.fill(QColor("white"));
    update();
}

QColor Whiteboard::getPenColor() const{
    return penColor;
}


int Whiteboard::getPenWidth() const{
    return penWidth;
}

void Whiteboard::paintEvent(QPaintEvent *event){
//    call the paint function to draw on the image
    paint();
    //show the image or paint it on widget
    QPainter painter(this);
    QRect redrawRect = event->rect();
    painter.drawPixmap(redrawRect, image, redrawRect);
    painter.end();
}

void Whiteboard::paint(){
    //QPainter can only be used in the paintEvent function or functions that are called by it
    //if this is not done and threads are used, the behavior of this cannot be expected
    QPainter imgPainter(&image);
    //checks if points queue is empty and if not
    while(!points.empty()){
            qLock.lock();
            QPoint point = points.dequeue();
            qLock.unlock();
            imgPainter.setPen(pen);
            //based on the value of teh last point it decides whether to draw a point or a line
            //to avoid drawing line between points when mouse is released and pressed again
            if(lastPoint == point)
                imgPainter.drawPoint(point);
            else
                imgPainter.drawLine(lastPoint, point);
            //update the value of the last point
            lastPoint=point;
        }
    imgPainter.end();
}

void Whiteboard::resizeEvent(QResizeEvent *event){
    if (event->size().width() > image.width() || event->size().height() > image.height()) {
        //only resize if larger
        // If the new size is larger create a new pixmap and copy existing content
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
    //use mutexes as queues are not thread safe
    qLock.lock();
    points.enqueue(point);
    qLock.unlock();
}

void Whiteboard::penUp(QPoint point){
    this->addPoint(point);
}

void Whiteboard::penDown(QPoint point){
    //if the mouse is pressed update the last point value with the current point and add it to the queue to be drawn
    lastPoint = point;
    this->addPoint(lastPoint);
}

void Whiteboard::painting(){
    //thread functions
    //calls the update (the paintingEvent) if the points queue is not empty and if it is sleep for 50ms
    //this is related tothe referesh rate of teh widget as if you don't let the thread sleep
    //or make it sleep for a very short time it  dies on you
    while (true) {
        if(!points.empty()){
            qLock.lock();
            update();
            qLock.unlock();
        }
        std::this_thread::sleep_for(50ms);
    }
}
