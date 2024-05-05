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
