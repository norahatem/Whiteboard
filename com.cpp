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

void send(DrawingCmd command){
//    std::bitset<8> bits = data;
    std::bitset<8> cmd = command.getCmd();
    std::bitset<16> x = command.getX();
    std::bitset<16> y = command.getY();
//    std::cout << "data to Send: " << cmd << "\t\t" << x << "\t" << y << "\n";
    int size = cmd.size() + x.size() + y.size();
//    std::bitset<40> data = cmd + x + y;
    for(int i = 0; i<cmd.size() ; i++){
        digitalWrite(TX,cmd[i]);
        digitalWrite(clkM, HIGH);
        std::this_thread::sleep_for(PERIOD);
        while(!digitalRead(ACK_SEND))
            std::this_thread::sleep_for(ACK_WAIT);
        digitalWrite(clkM, LOW);
        std::this_thread::sleep_for(PERIOD);
        while(digitalRead(ACK_SEND))
            std::this_thread::sleep_for(ACK_WAIT);
    }
//    if(command.getCmd() !=0){
    for(int i = 0; i<x.size() ; i++){
        digitalWrite(TX,x[i]);
        digitalWrite(clkM, HIGH);
        std::this_thread::sleep_for(PERIOD);
        while(!digitalRead(ACK_SEND))
            std::this_thread::sleep_for(ACK_WAIT);
        digitalWrite(clkM, LOW);
        std::this_thread::sleep_for(PERIOD);
        while(digitalRead(ACK_SEND))
            std::this_thread::sleep_for(ACK_WAIT);
    }
    for(int i = 0; i<y.size() ; i++){
        digitalWrite(TX,y[i]);
        digitalWrite(clkM, HIGH);
        std::this_thread::sleep_for(PERIOD);
        while(!digitalRead(ACK_SEND))
            std::this_thread::sleep_for(ACK_WAIT);
        digitalWrite(clkM, LOW);
        std::this_thread::sleep_for(PERIOD);
        while(digitalRead(ACK_SEND))
            std::this_thread::sleep_for(ACK_WAIT);
//            }
}
}
std::bitset<40> read(){
    std::bitset<40> readData;
    for(int i=0; i<readData.size();i++){
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
//    if(readData.to_ulong()!=0){
//        for(int i=8; i<readData.size();i++){
//            while(!digitalRead(clkS)){
//                std::this_thread::sleep_for(CLK_WAIT);
//            }
//            readData[i] = digitalRead(RX);
//            digitalWrite(ACK_RECEIVE, HIGH);
//            while(digitalRead(clkS)){
//                std::this_thread::sleep_for(CLK_WAIT);
//            }
//            digitalWrite(ACK_RECEIVE, LOW);
//        }
//    }
//    std::cout << "\t\t\tReceived data " << readData << "\n";
    return readData;
}
