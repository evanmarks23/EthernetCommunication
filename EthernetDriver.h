#pragma once


#include "EthernetFrame.h"

class EthernetDriver
{
private:

    EthernetFrame mFrame; // The frame sending the data


    

public:

    EthernetDriver();

    ~EthernetDriver();

    bool SendFrame(EthernetFrame frame);

    void Respond();

    void StreamMessage(EthernetFrame frame);

    std::vector<uint8_t> ConstructBytes(unsigned char size);

    EthernetFrame ConstructFrame();
    
    EthernetFrame GetSender() {return mFrame;}
    
};

EthernetDriver::EthernetDriver()
{

}

EthernetDriver::~EthernetDriver()
{
}
