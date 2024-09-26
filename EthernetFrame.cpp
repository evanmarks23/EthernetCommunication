#include "EthernetFrame.h"

EthernetFrame::EthernetFrame(std::vector<uint8_t> preamble, uint8_t sfd, std::vector<uint8_t> destination, 
    std::vector<uint8_t> source, std::vector<uint8_t> length, uint32_t crc, std::vector<uint8_t> data) 
    : mPreamble(preamble), mSFD(sfd), mDestination(destination), mSource(source), mLength(length), mCRC(crc), mData(data) 
{
    
}


// EthernetFrame::~EthernetFrame()
// {
// }