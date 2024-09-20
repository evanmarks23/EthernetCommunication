
#include<iostream>
#include "EthernetDriver.cpp"
#include "Protocol.cpp"

using namespace std;

int main()
{
    // Create our driver and protocol
    EthernetDriver driver;

    Protocol protocol;
    

    // Creates the host ethernet frame
    EthernetFrame host = driver.ConstructFrame();

    // Sends command if valid CRCs
    if(protocol.SendCommand(driver))
    {
        // Since valid CRCs respond to the command and stream the message
        protocol.RespondToCommand(driver);
        protocol.Stream(driver);
    }

    return 0;
}