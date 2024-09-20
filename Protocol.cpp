#include "Protocol.h"


// Sends the command from host to device
bool Protocol::SendCommand(EthernetDriver driver)
{
    return driver.SendFrame(driver.GetSender());

}

// Has the device respond to the command from host
void Protocol::RespondToCommand(EthernetDriver driver)
{

    driver.Respond();
}

// Has the device stream the message from host
void Protocol::Stream(EthernetDriver driver)
{
    driver.StreamMessage(driver.GetSender());
}