#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QQueue<QPoint> points;
    sender = new Sender(&points, this);
    receiver = new Receiver(&points, this);

    QString stylesheet = "QLabel { background-color : none; color : black; font-size: 11pt;}";
    send = new QLabel("Local", this);
    receive = new QLabel("Remote", this);
    send->setAlignment(Qt::AlignCenter);
    receive->setAlignment(Qt::AlignCenter);
    send->setStyleSheet(stylesheet);
    receive->setStyleSheet(stylesheet);

    QVBoxLayout *senderLayout = new QVBoxLayout;
    senderLayout->addWidget(send);
    senderLayout->addWidget(sender);

    QVBoxLayout *receiverLayout = new QVBoxLayout;
    receiverLayout->addWidget(receive);
    receiverLayout->addWidget(receiver);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addLayout(senderLayout);
    layout->addLayout(receiverLayout);


    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete sender;
    delete receiver;
}
