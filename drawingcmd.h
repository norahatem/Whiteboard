#ifndef DRAWINGCMD_H
#define DRAWINGCMD_H

#include <bitset>

class DrawingCmd
{
public:
    static const uint8_t CLEAR = 0;
    static const uint8_t PEN_UP = 1;
    static const uint8_t PEN_DOWN = 2;
    static const uint8_t ADD_POINT = 3;
    DrawingCmd();
    void setCmd(int command);
    void setXCoordinate(int xCoordinate);
    void setYCoordinate(int yCoordinate);
    int getCmd();
    int getX();
    int getY();
private:
//    cmd 0: clear
//    cmd 2: penUp
//    cmd 3: penDown
//    cmd 4: addPoint
    int cmd;
//    std::bitset<24> penColour;
//    std::bitset<8> penWidth;
    int x_coordinate;
    int y_coordinate;
//    std::bitset<24> backgroundColor;
};

#endif // DRAWINGCMD_H
