#ifndef DRAWINGCMD_H
#define DRAWINGCMD_H

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
#define PERIOD 10us
#define CLK_WAIT 1us
//acknowledge pulse on receive pi. This is an output
#define ACK_RECEIVE 4
//acknowledge pulse received on the sender side.
#define ACK_SEND 5
//#define ACK_TIME 1us
#define ACK_WAIT 1us

static const uint8_t CLEAR = 0;
static const uint8_t PEN_UP = 1;
static const uint8_t PEN_DOWN = 2;
static const uint8_t ADD_POINT = 3;
static const uint8_t CHANGE_PEN_COLOR = 4;
static const uint8_t CHANGE_PEN_WIDTH = 5;

using namespace std::literals::chrono_literals;
class DrawingCmd
{
public:
    DrawingCmd();
    void setCmd(std::bitset<8> command);
    void setXCoordinate(std::bitset<16> xCoordinate);
    void setYCoordinate(std::bitset<16> yCoordinate);

    int getCmd();
    int getX();
    int getY();

    int getRed();
    int getGreen();
    int getBlue();

    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);

    void setPenWidth(int newPenWidth);
    int getPenWidth();

    void send();
    void receive();

    template <size_t N, size_t... Sizes>
    std::bitset<N> concat(const std::bitset<Sizes>&... bitsets);

    template<size_t N>
    void readData(std::bitset<N>& data);

    template<size_t N>
    void sendData(std::bitset<N>& sendData);

private:
    std::bitset<8> cmd;
    std::bitset<16> x_coordinate;
    std::bitset<16> y_coordinate;

    std::bitset<8> red;
    std::bitset<8> green;
    std::bitset<8> blue;

    std::bitset<8> penWidth;
};

#endif // DRAWINGCMD_H
