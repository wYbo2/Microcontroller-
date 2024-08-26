//Single7Seg.cpp
#undef __ARM_FP

#include "mbed.h"

#define WAIT_TIME_MS 1000

#define SEVEN_SEGMENT_MASK 0x000000FF //PORT B0: PB_7 - PB_0, for 7 Seg display
#define SEVEN_SEGMENT_RESET 0x00000000 

PortOut sevenSegmentPort(PortB, SEVEN_SEGMENT_MASK);

//Port C: PC_11 - PC_8 connect to DIG3 - DIG0
DigitalOut sevenSegmentDIG0(PC_8);
DigitalOut sevenSegmentDIG1(PC_9);
DigitalOut sevenSegmentDIG2(PC_10);
DigitalOut sevenSegmentDIG3(PC_11);

int main()
{
    printf("This is MAPP Single7Seg running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    //reset
    sevenSegmentPort = SEVEN_SEGMENT_RESET;
    sevenSegmentDIG0= 0;
    sevenSegmentDIG1= 0;
    sevenSegmentDIG2= 0;
    sevenSegmentDIG3= 0;
    thread_sleep_for(WAIT_TIME_MS);

    while (true)
    {
    	// enable DIG0
    	sevenSegmentDIG0= 1;  

        //display 0
        sevenSegmentPort = 0b00111111;

    }
}
