#include "drawingcmd.h"

DrawingCmd::DrawingCmd()
{
    cmd = CLEAR;

}

void DrawingCmd::setCmd(int command){
    cmd = command;
}
void DrawingCmd::setXCoordinate(int xCoordinate){
    x_coordinate = xCoordinate;
}
void DrawingCmd::setYCoordinate(int yCoordinate){
    y_coordinate = yCoordinate;
}
std::bitset<8> DrawingCmd::getCmd(){
    return cmd;
}
std::bitset<16>DrawingCmd::getX(){
    return x_coordinate;
}
std::bitset<16>DrawingCmd::getY(){
    return y_coordinate;
}
