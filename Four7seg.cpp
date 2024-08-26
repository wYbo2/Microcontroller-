//Four7seg.cpp

#undef __ARM_FP

#include "mbed.h"
#define WAIT_TIME_MS 1000

#define SEVEN_SEGMENT_MASK 0x000000FF //PORT B0: PB_7 - PB_0, for 7 Seg display
#define SEVEN_SEGMENT_RESET 0x00000000 

PortOut sevenSegmentPort(PortB, SEVEN_SEGMENT_MASK);

//Use the BusOut interface to combine a number of DigitalOut pins to write them at once. 
//This API is useful for writing to multiple pins together as single interface instead of individual pins.
//You can have up to 16 pins in a Bus.
//The order of pins in the constructor is the reverse order of the pins in the byte order. 
//So if you have BusOut(a,b,c,d,e,f,g,h), 
//then the order of bits in the byte would be hgfedcba with a being bit 0, b being bit 1, c being bit 2 and so on.
//Port C: PC_11 - PC_8 connect to DIG3 - DIG0
BusOut sevenSegmentDIG(PC_8, PC_9, PC_10, PC_11);

DigitalIn button(PC_13);

int main()
{
    printf("This is MAPP Four7seg running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    //reset
    sevenSegmentPort = SEVEN_SEGMENT_RESET;
    sevenSegmentDIG = 0;		//0b00000000
    thread_sleep_for(WAIT_TIME_MS);

    while (true)
    {
        sevenSegmentDIG = 0b00000001; // enable DIG0
        sevenSegmentPort = 0x0000003F;  //display 0: 0b00111111
        thread_sleep_for(WAIT_TIME_MS);

        
        sevenSegmentDIG = 0b00000010; // enable DIG1
        sevenSegmentPort = 0x00000006;  //display 1: 0b00000110
        thread_sleep_for(WAIT_TIME_MS);

        sevenSegmentDIG = 0b00000100; // enable DIG2
        sevenSegmentPort = 0x0000005B;  //display 2: 0b01011011
        thread_sleep_for(WAIT_TIME_MS);

        sevenSegmentDIG = 0b00001000;  // enable DIG3
        sevenSegmentPort = 0x0000004F;  //display 3: 0b01001111
        thread_sleep_for(WAIT_TIME_MS);
    }
}
