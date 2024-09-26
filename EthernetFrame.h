#ifndef ETHERNET_FRAME_H
#define ETHERNET_FRAME_H

#include <vector>
#include <cstdint>

class EthernetFrame
{
private:

    std::vector<uint8_t> mPreamble; // 7 byte preamble that indicates starting of the frame
    uint8_t mSFD; // Always set to 10101011 and indicates upcoming bits are starting the frame (1 byte)
    std::vector<uint8_t> mDestination; // MAC address of machine data is going to (6 bytes)
    std::vector<uint8_t> mSource; // MAC address of machine data is coming from (6 bytes)
    std::vector<uint8_t> mLength; // Indicates the length of the entire ethernet frame (2 bytes)
    std::vector<uint8_t> mData; // The data being sent
    uint32_t mCRC; // Genereated over checksum of destination, source, length and data (4 bytes)
    
   
public:
    EthernetFrame(std::vector<uint8_t> preamble, uint8_t sfd, std::vector<uint8_t> destination, 
    std::vector<uint8_t> source, std::vector<uint8_t> length,uint32_t crc, std::vector<uint8_t> data);

    // EthernetFrame() {};

    uint32_t GetCRC() {return mCRC;}
    uint8_t GetSFD() {return mSFD;}
    std::vector<uint8_t> GetData() {return mData;}
    std::vector<uint8_t> GetDestination() {return mDestination;}
    std::vector<uint8_t> GetSource() {return mSource;}
    std::vector<uint8_t> GetLength() {return mLength;}
    std::vector<uint8_t> GetPreamble() {return mPreamble;}

    // ~EthernetFrame();
};

#endif // ETHERNET_FRAME_H

