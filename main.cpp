
#include<iostream>
#include "EthernetDriver.h"
#include "Protocol.h"
#include <cassert>

using namespace std;

const int SendMessage = 1;
const int RecieveMessage = 1;
const int DontSend = 2;

int main()
{
    // Create our driver and protocol
    EthernetDriver driver;

    Protocol protocol;
    

    // Creates the host and device ethernet frames
    shared_ptr<EthernetFrame> host = driver.ConstructFrame(SendMessage);
    shared_ptr<EthernetFrame> device = driver.ConstructFrame(RecieveMessage);

    driver.SetSender(host);
    driver.SetReciever(device);

    // Sends command if valid CRCs
    if(protocol.SendCommand(driver))
    {
        // Since valid CRCs respond to the command and stream the message
        protocol.RespondToCommand(driver);
        protocol.Stream(driver);
        
    }

    // Test to make sure that CRC are the same to send the message
    assert(host->GetCRC() == device->GetCRC());


    cout << "What happens when messages dont send" << endl;
    host = driver.ConstructFrame(DontSend);
    device = driver.ConstructFrame(RecieveMessage);

    driver.SetSender(host);
    driver.SetReciever(device);

    // Sends command if valid CRCs
    if(protocol.SendCommand(driver))
    {
        // Since valid CRCs respond to the command and stream the message
        protocol.RespondToCommand(driver);
        protocol.Stream(driver);
  
    }

    // Test to make sure that CRC are not the same to make sure message does not send
    assert(host->GetCRC() != device->GetCRC());


    return 0;
}