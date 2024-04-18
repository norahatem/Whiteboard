#ifndef DRAWINGCMD_H
#define DRAWINGCMD_H

#include <iostream>

class DrawingCmd
{
public:
    DrawingCmd();
private:
    std::uint8_t cmd;
    std::string colour;

};

#endif // DRAWINGCMD_H
