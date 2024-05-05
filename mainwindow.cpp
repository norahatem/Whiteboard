#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QQueue<QPoint> points;
    sender = new Sender(this);
    receiver = new Receiver(this);

    createAction();
    createMenu();

    QString stylesheet = "QLabel { background-color : none; color : black; font-size: 11pt;}";
    send = new QLabel("Local", this);
    receive = new QLabel("Remote", this);
    send->setAlignment(Qt::AlignCenter);
    receive->setAlignment(Qt::AlignCenter);
    send->setStyleSheet(stylesheet);
    receive->setStyleSheet(stylesheet);

    QVBoxLayout *receiverLayout = new QVBoxLayout;
    receiverLayout->addWidget(receive);
    receiverLayout->addWidget(receiver);

    QVBoxLayout *senderLayout = new QVBoxLayout;
    senderLayout->addWidget(send);
    senderLayout->addWidget(sender);



    QHBoxLayout *layout = new QHBoxLayout;
    layout->addLayout(senderLayout);
    layout->addLayout(receiverLayout);

//    setFixedSize(850,450);
    setMinimumSize(1050,550);
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete sender;
    delete receiver;
}

void MainWindow::createAction(){
    clearScreen = new QAction(tr("&Clear"), this);
    connect(clearScreen, &QAction::triggered, sender, &Sender::clearBoard);

    changeColor = new QAction(tr("&Pen Color"), this);
    connect(changeColor, &QAction::triggered, this, &MainWindow::changePenColor);
}

void MainWindow::createMenu(){
    options = new QMenu(tr("&Options"), this);
    options->addAction(clearScreen);
    options->addAction(changeColor);
    menuBar()->addMenu(options);
}


void MainWindow::changePenColor(){
    QColor newColor = QColorDialog::getColor(sender->drawingArea->getPenColor());
    if(newColor.isValid()){
        sender->ChangePenColor(newColor.name());
    }
}
