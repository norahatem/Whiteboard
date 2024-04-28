#include "com.h"


using namespace std::literals::chrono_literals;
void initRpi(){
//    wiringPiSetup();
//    pinMode(2,OUTPUT);
//    pinMode(3,INPUT);
//    pinMode(TX,OUTPUT);
//    pinMode(RX,INPUT);
//    digitalWrite(TX,LOW);

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

void send(int coordinate){
    std::bitset<9> bits = coordinate;
    qDebug() << "Bitset to Send" << QString::fromStdString(bits.to_string());
    for(int i = 0; i<bits.size() ; i++){
        //qDebug() <<"\t\t\t" <<bits[i];
        digitalWrite(TX,bits[i]);
        digitalWrite(clkM, HIGH);
        std::this_thread::sleep_for(PERIOD);
        while(!digitalRead(ACK_SEND))
            std::this_thread::sleep_for(ACK_WAIT);
        digitalWrite(clkM, LOW);
        std::this_thread::sleep_for(PERIOD);
        while(digitalRead(ACK_SEND))
            std::this_thread::sleep_for(ACK_WAIT);
    }

}

int read(){
    std::bitset<9> readData;
    for(int i =0; i<readData.size();i++){
        while(!digitalRead(clkS)){
            std::this_thread::sleep_for(CLK_WAIT);
        }
        readData[i] = digitalRead(RX);
        digitalWrite(ACK_RECEIVE, HIGH);
        while(digitalRead(clkS)){
            std::this_thread::sleep_for(CLK_WAIT);
        }
        digitalWrite(ACK_RECEIVE, LOW);
}
    qDebug() << "\t\t\tBitset Read" << QString::fromStdString(readData.to_string());
    return (int)readData.to_ulong();
}
