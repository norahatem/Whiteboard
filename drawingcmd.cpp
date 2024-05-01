#include "drawingcmd.h"

DrawingCmd::DrawingCmd()
{
//    cmd = CLEAR;
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
int DrawingCmd::getCmd(){
    return cmd;
}
int DrawingCmd::getX(){
    return x_coordinate;
}
int DrawingCmd::getY(){
    return y_coordinate;
}
