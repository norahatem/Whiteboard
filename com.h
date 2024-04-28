#ifndef COM_H
#define COM_H

#include <wiringPi.h>
#include <QDebug>
#include <bitset>

#define clkM 2
#define clkS 3
#define T 1ms
#define TX 15
#define RX 16
#define t 100000

void initRpi();

void send(bool bitToSend);

void read();

void serialize();

#endif // COM_H
