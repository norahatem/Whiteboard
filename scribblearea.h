// This scribbleArea class follows the tutorial on Qt: wdiget scribble example:
// can be found here: https://doc.qt.io/qt-5/qtwidgets-widgets-scribble-example.html
// please note that not all the functionalities are going to be implemented, might do that in the futsure tho
// but now we only need the very basic drawing functionalities

#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QWidget>
#include <QColor>
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>


class ScribbleArea: public QWidget
{
    Q_OBJECT
public:
    // constructor
    explicit ScribbleArea(QWidget *parent = nullptr);
    // functions to set the colour and width of pen
    void setPenColor(const QColor &newPenColor);
    void setPenWidth(double newPenWidth);

    // getter methods
    bool getIsModified() const;
    QColor getPenColor() const;
    double getPenWidth() const;


public slots:
    void clear();

protected:
    // override all of those methods
    // mouse handling events to handle the drawing of the board
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    // update the board
    void paintEvent(QPaintEvent *event);
    // make sure that the area we are drawing on is the same as our widget!
    void resizeEvent(QResizeEvent *event);


private:
    // draw line, go from previous point that the user was located at and draw line to the curret position/endPoint
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    // modified is true if there are unsaved changes to the image displayed in the scribble area.
    bool isModified = false;
    // drawing is true while the user is pressing the left mouse button within the scribble area.
    bool drawing = false;
    double penWidth = 1.3;
    QColor penColor = Qt::black;
    QPoint lastPoint;
    QImage image;
};

#endif // SCRIBBLEAREA_H
