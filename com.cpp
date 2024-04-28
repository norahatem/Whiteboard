#include "com.h"

void initRpi(){
    wiringPiSetup();
    pinMode(2,OUTPUT);
    pinMode(3,INPUT);
    pinMode(TX,OUTPUT);
    pinMode(RX,INPUT);
}

//void send(){
//    qDebug() << "Sending..";
//    while(true){
//        digitalWrite(clkM, HIGH);
//        qDebug() << "Sending Pulse";
//        digitalWrite(TX,HIGH);
//        delayMicroseconds(t);
//        digitalWrite(TX,LOW);
//        delayMicroseconds(t);
//        digitalWrite(clkM, LOW);
//        qDebug() << "Pulse sent";
//    }
//}

void send(bool bitToSend){
    qDebug() << "Sending..";
    while(true){
        digitalWrite(clkM, HIGH);
        qDebug() << "Sending data";
        digitalWrite(TX,bitToSend);
        delayMicroseconds(t);
        digitalWrite(clkM, LOW);
        delayMicroseconds(t);
    }
}

//void read(){
//    qDebug() << "\t\t\tReading..";
//    while(true){
//        bool ack=digitalRead(clkS);
//        if(ack){
//            qDebug() << "\t\t\tReading Pulse";
//            bool data = digitalRead(RX);
//            qDebug() << "\t\t\t"<<(data?"HIGH":"LOW");
//        }
//        delayMicroseconds(t);
//    }
//}

void read(){
    qDebug() << "\t\t\tReading..";
    while(true){
        bool ack=digitalRead(clkS);
        if(ack){
            qDebug() << "\t\t\tReading Pulse";
            bool data = digitalRead(RX);
//            qDebug() << "\t\t\t"<<(data?"HIGH":"LOW");
            qDebug() << data;
        }
        delayMicroseconds(t);
    }
}
