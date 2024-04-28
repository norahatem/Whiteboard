#ifndef COM_H
#define COM_H

#include <wiringPi.h>
#include <QDebug>

#include <iostream>
#include <bitset>
#include <thread>


#define clkM 2
#define clkS 3
#define T 1ms
#define TX 15
#define RX 16
#define PERIOD 100us
#define CLK_WAIT 10us
//acknowledge pulse on receive pi. This is an output
#define ACK_RECEIVE 4
//acknowledge pulse received on the sender side.
#define ACK_SEND 5
//#define ACK_TIME 1us
#define ACK_WAIT 1us

void initRpi();

void send(int coordinate);

int read();

void serialize();

#endif // COM_H