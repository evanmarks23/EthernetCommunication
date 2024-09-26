#ifndef ETHERNET_DRIVER_H
#define ETHERNET_DRIVER_H

#include <memory>
#include "EthernetFrame.h"

class EthernetDriver
{
private:

    std::shared_ptr<EthernetFrame> mFrame = nullptr; // The frame sending the data

    std::shared_ptr<EthernetFrame> mDevice = nullptr;
    

public:

    EthernetDriver();

    ~EthernetDriver();

    bool SendFrame(std::shared_ptr<EthernetFrame>);

    void Respond();

    void StreamMessage(std::shared_ptr<EthernetFrame>);

    std::vector<uint8_t> ConstructBytes(unsigned char size, int seed);

    std::shared_ptr<EthernetFrame> ConstructFrame(int seed);

    void SetSender(std::shared_ptr<EthernetFrame> frame) {mFrame = frame;}

    void SetReciever(std::shared_ptr<EthernetFrame> frame) {mDevice = frame;}
    
    std::shared_ptr<EthernetFrame> GetSender() {return mFrame;}

    std::shared_ptr<EthernetFrame> GetReciever() {return mDevice;}
    
};

#endif // ETHERNET_DRIVER_H


