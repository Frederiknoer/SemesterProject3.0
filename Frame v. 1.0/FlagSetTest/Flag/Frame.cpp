//
// Created by Mikkel on 03-10-2016.
//

#include "Frame.h"
#include <iostream>

using namespace std;

Frame::Frame()
{
}

Frame::Frame(unsigned int data)
{
    uint32_t mask = 0;						// We need 32 bits: 8 bit(startFlag)+8 bit (data)+ 8 bit (parity) + 8 bit (endFlag)

    frame =((mask|data)<<16);					// flytter data 16 pladser venstre		00000000 data 0 00 0 0000 00000000

    if (data == 126) {						// 126 = 0b																				01111110 = start/stop flag
        int mask2 = 0x38000;				//flag check on 0000 0000  0000 0011  1000 0000  0000 0000 (bit stuffing med 0)
        frame = frame ^ mask2;
    }
}

unsigned int Frame::getFrame()
{
    return frame;
}

void Frame::setFlag()
{
    const uint32_t	StartFlag = 0x7E000000;
    const uint32_t	StopFlag = 0x0000007E;

    frame = (StartFlag | frame | StopFlag);

}

void Frame::setParitybit()
{
    const uint32_t	parityFlag = 0x4000;	//00000000 00000000 0100 0000 00000000

    int testF = frame;

    int parity = 0;
    while (testF > 0)						// if it is 0 there are no more 1's to count
    {
        if (testF & 0x01)					//see if LSB is 1
        {
            parity++;						// why yes it is
        }
        testF = testF >> 1;					//shift to next bit
    }



    if (parity & 0x01) {						// only need the low bit to determine odd / even.... true=odd
        frame = frame | parityFlag;				//High when odd
    }


}


Frame::~Frame()
{

}
