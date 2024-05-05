#include "drawingcmd.h"

DrawingCmd::DrawingCmd()
{
//    cmd = CLEAR;
}

void DrawingCmd::setCmd(std::bitset<8> command){
    cmd = command;
}
void DrawingCmd::setXCoordinate(std::bitset<16> xCoordinate){
    x_coordinate = xCoordinate;
}
void DrawingCmd::setYCoordinate(std::bitset<16> yCoordinate){
    y_coordinate = yCoordinate;
}
std::bitset<8> DrawingCmd::getCmd(){
    return cmd;
}
std::bitset<16> DrawingCmd::getX(){
    return x_coordinate;
}
std::bitset<16> DrawingCmd::getY(){
    return y_coordinate;
}

std::bitset<8> DrawingCmd::getRed(){
    return red;
}
std::bitset<8> DrawingCmd::getGreen(){
    return green;
}
std::bitset<8> DrawingCmd::getBlue(){
    return blue;
}

void DrawingCmd::setRed(int r){
    red = r;
}
void DrawingCmd::setGreen(int g){
    green = g;
}
void DrawingCmd::setBlue(int b){
    blue = b;
}


template <size_t N, size_t... Sizes>
std::bitset<N> DrawingCmd::concat(const std::bitset<Sizes>&... bitsets) {
    std::string dataStream = (... + bitsets.to_string());
    return std::bitset<N>(dataStream);
}

template<size_t N>
void DrawingCmd::readData(std::bitset<N>& data) {
    for(int i=0; i<data.size();i++) {
        while(!digitalRead(clkS)) {
            std::this_thread::sleep_for(CLK_WAIT);
        }
        data[i] = digitalRead(RX);
        digitalWrite(ACK_RECEIVE, HIGH);
        while(digitalRead(clkS)) {
            std::this_thread::sleep_for(CLK_WAIT);
        }
        digitalWrite(ACK_RECEIVE, LOW);
    }
}

template<size_t N>
void DrawingCmd::sendData(std::bitset<N>& sendData) {
    for (int i = 0; i < sendData.size(); i++) {
        digitalWrite(TX, sendData[i]);
        digitalWrite(clkM, HIGH);
        std::this_thread::sleep_for(PERIOD);
        while (!digitalRead(ACK_SEND))
            std::this_thread::sleep_for(ACK_WAIT);
        digitalWrite(clkM, LOW);
        std::this_thread::sleep_for(PERIOD);
        while (digitalRead(ACK_SEND))
            std::this_thread::sleep_for(ACK_WAIT);
    }
}

void DrawingCmd::receive(){
    readData(cmd);
    switch ((uint8_t) cmd.to_ulong()) {
    case CLEAR:
        break;
    case CHANGE_PEN_COLOR:
        readData(red);
        readData(green);
        readData(blue);
        break;
    case PEN_DOWN:
    case PEN_UP:
    case ADD_POINT:
        readData(x_coordinate);
        readData(y_coordinate);
        break;
    }

}

void DrawingCmd::send(){
    auto sendClear = std::bitset<8>();
        auto sendColor = std::bitset<32>();
        auto dataToSend = std::bitset<40>();

        switch ((uint8_t) cmd.to_ulong()) {
        case CLEAR:
            sendClear = concat<8>(cmd);
            sendData(sendClear);
            break;
        case CHANGE_PEN_COLOR:
            sendColor = concat<32>(blue, green, red, cmd);
            sendData(sendColor);
            break;
        case PEN_DOWN:
        case PEN_UP:
        case ADD_POINT:
            dataToSend = concat<40>(y_coordinate, x_coordinate, cmd);
            sendData(dataToSend);
            break;
        }
}
