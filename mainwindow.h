//this main wincdow is to represent the main indow that shows both sender and receiver windows in one window
//this is an attempt to ic the problem that only the fisrt window shown takes all the functionalities of a window
//it also shows the menu bar that allows you to clear/change pen color and chnage pen width
//how to use it, only decalre it in the main and call the show function

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QColorDialog>
#include <QInputDialog>

#include "sender.h"
#include "receiver.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void changePenColor();
    void changePenWidth();

private:
    Sender *sender;
    Receiver *receiver;
    QLabel *send, *receive;
    void createAction();
    void createMenu();

    QMenu *options;
    QAction *clearScreen;
    QAction *changeColor;
    QAction *changeWidth;

};

#endif // MAINWINDOW_H
