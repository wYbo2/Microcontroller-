//Single7Seg_Loop.cpp
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

DigitalIn button(PC_13);

unsigned char press = 0;
unsigned char LedData[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7c, 0x39, 0x5E, 0x79, 0x71};

int main()
{
    printf("This is MAPP Single7Seg_Loop running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    //reset
    sevenSegmentPort = SEVEN_SEGMENT_RESET;
    sevenSegmentDIG0= 0;
    sevenSegmentDIG1= 0;
    sevenSegmentDIG2= 0;
    sevenSegmentDIG3= 0;
    thread_sleep_for(WAIT_TIME_MS);

    // enable DIG0
    sevenSegmentDIG0 = 1;

    while (true)
    {
        if (press == 0)
        {
            //display from 0 to F
            for (int i = 0; i < 16; i++) 
            {
                sevenSegmentPort = LedData[i]; 

                thread_sleep_for(WAIT_TIME_MS);

            }
        }
        else
        {
            //display from F to 0
            for (int i = 15; i >= 0; i--) 
            {
                sevenSegmentPort = LedData[i]; 

                thread_sleep_for(WAIT_TIME_MS);

            }
        }
        

        while (button.read() == 1); //wait for the button press

        //clear the display
        sevenSegmentPort = SEVEN_SEGMENT_RESET;
        thread_sleep_for(WAIT_TIME_MS);
        
        press ++; 
        press %= 2; 
        
    }
}
