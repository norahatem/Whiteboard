#include <QApplication>
#include "receiver.h"
#include "sender.h"
#include <thread>

#include "mainwindow.h"
#include "drawingcmd.h"

void initRpi(){
    wiringPiSetup();
    pinMode(clkM,OUTPUT);
    pinMode(clkS,INPUT);
    pinMode(TX,OUTPUT);
    pinMode(RX,INPUT);
    pinMode(ACK_RECEIVE, OUTPUT);
    pinMode(ACK_SEND, INPUT);
    digitalWrite(ACK_RECEIVE, LOW);
    digitalWrite(clkM,LOW);
    digitalWrite(TX,LOW);
}

int main(int argc, char *argv[])
{
    initRpi();
    QApplication app(argc, argv);

    MainWindow mainW;
    mainW.show();
//    Sender send;
//    Receiver receive;
//    send.show();
//    receive.show();
    return app.exec();
}
