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
int DrawingCmd::getCmd(){
    return (int)cmd.to_ulong();
}
int DrawingCmd::getX(){
    return (int)x_coordinate.to_ulong();
}
int DrawingCmd::getY(){
    return (int)y_coordinate.to_ulong();
}

int DrawingCmd::getRed(){
    return (int)red.to_ulong();
}
int DrawingCmd::getGreen(){
    return (int)green.to_ulong();
}
int DrawingCmd::getBlue(){
    return (int)blue.to_ulong();
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

//variadic function : takes a variable number of arguments
template <size_t N, size_t... Sizes>
std::bitset<N> DrawingCmd::concat(const std::bitset<Sizes>&... bitsets) {
    //converts to string and concatenates it and returns the bitset value
    std::string dataStream = (... + bitsets.to_string());
    return std::bitset<N>(dataStream);
}

template<size_t N>
void DrawingCmd::readData(std::bitset<N>& data) {
    //takes a reference to a value and reads the respective value and stores it in that variable
    //it loops aroud for the size of that variable
    for(int i=0; i<data.size();i++) {
        //if the clock signal is not high sleep for some time CLK_WAIT
        //clock wait must be less that the time the data is held for as to not miss it
        while(!digitalRead(clkS)) {
            std::this_thread::sleep_for(CLK_WAIT);
        }
        //when the pin is checked to be high, read the data pin and store it in the respective position
        data[i] = digitalRead(RX);
        //write high to the ack receive indicating that you have read the data successfully
        digitalWrite(ACK_RECEIVE, HIGH);
        //wait for the clock to go low
        while(digitalRead(clkS)) {
            std::this_thread::sleep_for(CLK_WAIT);
        }
        //write low to the ack pin indicating that you are ready for the next data transmission
        digitalWrite(ACK_RECEIVE, LOW);
    }
}

template<size_t N>
void DrawingCmd::sendData(std::bitset<N>& sendData) {
    //takes a reference to the variable to be read
    for (int i = 0; i < sendData.size(); i++) {
        //write the data value before setting the clock (data must be set before the next rising edge of the clock)
        digitalWrite(TX, sendData[i]);
        //set the clock high to tell the receiver that this is the data to be read
        digitalWrite(clkM, HIGH);
        //sleep for some time PERIOD
        std::this_thread::sleep_for(PERIOD);
        //wait for ack from receiver note: sleep for some time as to free cpu
        while (!digitalRead(ACK_SEND))
            std::this_thread::sleep_for(ACK_WAIT);
        //when you receive the ack signal, set the clcok low
        digitalWrite(clkM, LOW);
        //leave the clock low for some time
        std::this_thread::sleep_for(PERIOD);
        //wait for the ack pin to go low again before writing the next bit
        while (digitalRead(ACK_SEND))
            std::this_thread::sleep_for(ACK_WAIT);
    }
}

void DrawingCmd::setPenWidth(int newPenWidth){
    penWidth = newPenWidth;
}

int DrawingCmd::getPenWidth(){
    return (int) penWidth.to_ulong();
}

void DrawingCmd::receive(){
    //the receive reads the command and based on the cmd it decides how many bytes to read and how to interpret them
    readData(cmd);
    switch ((uint8_t) cmd.to_ulong()) {
    case CLEAR:
        break;
    case CHANGE_PEN_COLOR:
        readData(red);
        readData(green);
        readData(blue);
        break;
    case CHANGE_PEN_WIDTH:
        readData(penWidth);
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
    //this is to avoid the jump to label error so i just initialize fw variables before,
    //there is probably a better way to do it
    auto sendClear = std::bitset<8>();
    auto sendColor = std::bitset<32>();
    auto dataToSend = std::bitset<40>();
    auto sendWidth = std::bitset<16>();

    //the sender decides how many and what bytes to send based on the cmd
    switch ((uint8_t) cmd.to_ulong()) {
    case CLEAR:
        sendClear = concat<8>(cmd);
        sendData(sendClear);
        break;
    case CHANGE_PEN_COLOR:
        sendColor = concat<32>(blue, green, red, cmd);
        sendData(sendColor);
        break;
    case CHANGE_PEN_WIDTH:
        sendWidth = concat<16>(penWidth, cmd);
        sendData(sendWidth);
        break;
    case PEN_DOWN:
    case PEN_UP:
    case ADD_POINT:
        dataToSend = concat<40>(y_coordinate, x_coordinate, cmd);
        sendData(dataToSend);
        break;
    }
}
