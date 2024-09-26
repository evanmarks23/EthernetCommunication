#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "EthernetDriver.h"

class Protocol
{
private:

   
public:
    Protocol();
    ~Protocol();

    bool SendCommand(EthernetDriver driver);

    void RespondToCommand(EthernetDriver driver);

    void Stream(EthernetDriver driver);

    void HandleFrame();
};

#endif // PROTOCOL_H

