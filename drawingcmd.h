#ifndef DRAWINGCMD_H
#define DRAWINGCMD_H

#include <bitset>

class DrawingCmd
{
public:
    DrawingCmd();

private:
    std::bitset<4> cmd;
    std::string colour;
};

#endif // DRAWINGCMD_H
