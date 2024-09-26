#include "EthernetDriver.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

EthernetDriver::EthernetDriver()
{

}

EthernetDriver::~EthernetDriver()
{
}

// Generates random bytes for ethernet frame
vector<uint8_t> EthernetDriver::ConstructBytes(unsigned char size, int seed)
{
    random_device rd;
    mt19937 generator;
    generator.seed(seed);
    uniform_int_distribution<uint8_t> distribute(0, 255);

    vector<uint8_t> bytes;

    for (int i = 0; i < size; i++)
    {
        bytes.push_back(distribute(generator));
    }

    return bytes;
}

// Builds each part of the ethernet frame
std::shared_ptr<EthernetFrame> EthernetDriver::ConstructFrame(int seed)
{
    vector<uint8_t> preamble = ConstructBytes(7, seed);
    uint8_t sfd = 0xAB;
    vector<uint8_t> destination = ConstructBytes(6, seed);
    vector<uint8_t> source = ConstructBytes(6, seed);
    
    vector<uint8_t> length = ConstructBytes(2, seed);

    vector<uint8_t> data = ConstructBytes(length[0] + length[1], seed);

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

    std::shared_ptr<EthernetFrame> frame = make_shared<EthernetFrame>(preamble, sfd, destination, source, length, crc, data);

    return frame;
    
}

//Sends the frame if CRC values are the same.
bool EthernetDriver::SendFrame(std::shared_ptr<EthernetFrame> frame)
{
    

    if (mFrame->GetCRC() == mDevice->GetCRC())
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
void EthernetDriver::StreamMessage(std::shared_ptr<EthernetFrame> frame)
{
    cout << "Message from host: ";
   for (auto byte : frame->GetData())
   {
        cout << +byte;
   }
   cout << endl;
   cout << endl;
}
