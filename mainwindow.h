#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sender.h"
#include "receiver.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
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
};

#endif // MAINWINDOW_H
