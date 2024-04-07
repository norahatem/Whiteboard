#include "scribblearea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
}

void ScribbleArea::setPenColor(const QColor &newPenColor){
    penColor = newPenColor;
}

void ScribbleArea::setPenWidth(double newPenWidth){
    penWidth = newPenWidth;
}

void ScribbleArea::clear(){
    // the clear function simply fills the whole thing with white
    image.fill(Qt::white);
    // when you make any changes set isModified to true meaning that there are unsaved modifications
    isModified = true;
    update();
}

bool ScribbleArea::getIsModified() const{
    return isModified;
}

void ScribbleArea::mousePressEvent(QMouseEvent *event){
    if(event->button()== Qt::LeftButton){
        // get the position of the last press
        lastPoint = event->pos();
        // set the drawing to true
        // because we can't assume that a mouse move and mouse release event is always preceded by a mouse press event on the same widget.
        drawing = true;
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event){

    if(event->buttons() & Qt::LeftButton && drawing){
        // the draw line function is called if the user moves the mouse while the left button is pressed
        drawLineTo(event->pos());
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton && drawing){
        // the drawLine function is called again after the mouse is released
        drawLineTo(event->pos());
        // editing finished, set drawing to false
        drawing = false;
    }
}

void ScribbleArea::paintEvent(QPaintEvent *event){
    // create QPainter for the scribble area to draw the image
    // The QPainter class provides functions for drawing and painting on widgets and other paint devices.
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    // takes dirtyRect as a parameter twice as we need to redraw this rectangle
    // this means that overdraw this area
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void ScribbleArea::resizeEvent(QResizeEvent *event){
    // check if the image needs to be resized
    // only check if the deimensions of the image are the smaller than that of the screen
    if(width() > image.width() || height()> image.height()){
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
    // Initial Image is slightly larger than mainWindow and scriibleArea
    // to avoid always resizing the image when the user resizes the main window (which would be very inefficient).
    // when the main window becomes larger than this initial size, the image needs to be resized.
}

void ScribbleArea::drawLineTo(const QPoint &endPoint){

    QPainter painter(&image);
    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    // draw a line from the last point where the mouse was pressed or moved to the endPoint
    painter.drawLine(lastPoint, endPoint);
    isModified = true;

    int rad = (penWidth/2)+2;
    // pass the area that needs to be repainted
    // optimization so that we don't repaint the whole thing
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    // update last point
    lastPoint = endPoint;
}


void ScribbleArea::resizeImage(QImage *image, const QSize &newSize){
    // don't do anything if theyre already the same size
    if(image->size() == newSize){
        return;
    }
    // create a brand new image which is all white
    // draw the old image onto it using QPainter
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255,255,255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0,0), *image);
    *image = newImage;
}
