#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QQueue<QPoint> points;
    sender = new Sender(this);
    receiver = new Receiver(this);

    createAction();
    createMenu();

    //set stylesheet for QLabel
    QString stylesheet = "QLabel { background-color : none; color : black; font-size: 11pt;}";
    //add two labels indicating which one is the send/local and which one is the receive/remote
    send = new QLabel("Local", this);
    receive = new QLabel("Remote", this);
    send->setAlignment(Qt::AlignCenter);
    receive->setAlignment(Qt::AlignCenter);
    send->setStyleSheet(stylesheet);
    receive->setStyleSheet(stylesheet);

    //two vertical boxe to contain the sender window and its label and the receiver window and its label
    QVBoxLayout *receiverLayout = new QVBoxLayout;
    receiverLayout->addWidget(receive);
    receiverLayout->addWidget(receiver);

    QVBoxLayout *senderLayout = new QVBoxLayout;
    senderLayout->addWidget(send);
    senderLayout->addWidget(sender);

//    horizontal box to add both vertical boxes in it

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
    //function to create the actions that are to be added to the menu
    clearScreen = new QAction(tr("&Clear"), this);
    connect(clearScreen, &QAction::triggered, sender, &Sender::clearBoard);

    changeColor = new QAction(tr("&Pen Color"), this);
    connect(changeColor, &QAction::triggered, this, &MainWindow::changePenColor);

    changeWidth = new QAction(tr("&Pen Width"), this);
    connect(changeWidth, &QAction::triggered, this, &MainWindow::changePenWidth);
}

void MainWindow::createMenu(){
    //function to create the menu bar
    options = new QMenu(tr("&Options"), this);
    options->addAction(clearScreen);
    options->addAction(changeColor);
    options->addAction(changeWidth);
    menuBar()->addMenu(options);
}


void MainWindow::changePenColor(){
    //change pen color to be triggered when the change color action is triggered
    QColor newColor = QColorDialog::getColor(sender->drawingArea->getPenColor());
    if(newColor.isValid()){
        sender->ChangePenColor(newColor.name());
    }
}

void MainWindow::changePenWidth(){
    //function to change pen width
    //called when the pen width action is triggereed
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Whiteboard"), tr("Select pen width:"),
        sender->drawingArea->getPenWidth(),
        1,50,1,&ok);
    if(ok)
        sender->changePenWidth(newWidth);
}
