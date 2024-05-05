#ifndef WHITEBOARD_H
#define WHITEBOARD_H

// to handle graphics and drawings
#include <QPixmap>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>

#include <QColor>
#include <QPoint>
#include <QQueue>
#include <QMutex>
#include <QDebug>

#include <thread>
#include <iostream>
using namespace std::literals::chrono_literals;
class Whiteboard: public QWidget
{

public:
    explicit Whiteboard(QString name, QWidget *parent = nullptr);
    QMutex qLock;
    void setPenColor(QColor newColor);
    void setPenSize(int newSize);

    // getter methods
    bool getIsModified() const;
    QColor getPenColor() const;
    double getPenWidth() const;
    void addPoint(QPoint point);
    void penUp(QPoint point);
    void penDown(QPoint point);

public slots:
    void clear();

protected:
    // paint event
    void paintEvent(QPaintEvent *event)override;
    void resizeEvent(QResizeEvent *event)override;

private:
    // bool drawing;
    bool isModified;
    QPoint lastPoint;
    void paint(QPoint point);
    // off class image to handle drawing
    QPixmap image;
    // QVector<QPoint> points;
    QColor penColor = "Black";
    int penWidth = 3;
    QQueue<QPoint> points;
    QPen pen = QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    std::thread paintThread;
    QString boardName;
    void painting(){
        while (true) {
            if(!points.empty()){
                qLock.lock();
                update();
                qLock.unlock();

            }
            std::this_thread::sleep_for(50ms);
        }
    }
};

#endif // WHITEBOARD_H
