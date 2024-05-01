#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>

#include "sender.h"
#include "receiver.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Sender *sender;
    Receiver *receiver;
    QLabel *send, *receive;
    void createAction();
    void createMenu();

    QMenu *options;
    QAction *clearScreen;

};

#endif // MAINWINDOW_H
