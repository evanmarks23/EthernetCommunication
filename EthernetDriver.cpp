#include "EthernetDriver.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

// Generates random bytes for ethernet frame
vector<uint8_t> EthernetDriver::ConstructBytes(unsigned char size)
{
    random_device rd;
    mt19937 generator;
    generator.seed(time(0));
    uniform_int_distribution<uint8_t> distribute(0, 255);

    vector<uint8_t> bytes;

    for (int i = 0; i < size; i++)
    {
        bytes.push_back(distribute(generator));
    }

    return bytes;
}

// Builds each part of the ethernet frame
EthernetFrame EthernetDriver::ConstructFrame()
{
    vector<uint8_t> preamble = ConstructBytes(7);
    uint8_t sfd = 0xAB;
    vector<uint8_t> destination = ConstructBytes(6);
    vector<uint8_t> source = ConstructBytes(6);
    
    vector<uint8_t> length = ConstructBytes(2);

    vector<uint8_t> data = ConstructBytes(length[0] + length[1]);

    uint32_t crc = 0;

    // Simple sum for CRC using data, length, destination and source address
    for (auto byte : data)
    {
        crc += byte;
    }
    for (int i = 0; i < source.size(); i++)
    {
        if (i < length.size())
        {
            crc += length[i];
        }
        crc += destination[i];
        crc += source[i];
    }

    EthernetFrame frame(preamble, sfd, destination, source, length, crc, data);
    mFrame = frame;

    return mFrame;
    
}

//Sends the frame if CRC values are the same.
bool EthernetDriver::SendFrame(EthernetFrame frame)
{
    

    if (mFrame.GetCRC() == frame.GetCRC())
    {
         
         cout << "Sending command from Host to Device" << endl;
         return true;
    }
    else
    {
        cout << "Error sending command crc values are different" << endl;
        return false;
    }
    
   

}

// Once the frame gets sent make sure to get have the device respond
void EthernetDriver::Respond()
{
    cout << "The command has been recieved from the host" << endl;
}


// Once verified that the response has happened stream the data from the host
void EthernetDriver::StreamMessage(EthernetFrame frame)
{
    cout << "Message from host: ";
   for (auto byte : frame.GetData())
   {
        cout << +byte;
   }
   cout << endl;
}
