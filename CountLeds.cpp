//CountLeds.cpp
//Program to make 8 leds on General I/O Board do binary up counting

#undef __ARM_FP

#include "mbed.h"
#define WAIT_TIME_MS 500

#define DISPLAY_BAR_MASK 0x000000FF //PORT C0: PC_7 - PC_0
#define DISPLAY_BAR_RESET 0x00000000 

PortOut displayBarPort(PortC, DISPLAY_BAR_MASK);

unsigned char j; //8 bit data type, ranging from 0 to 255

int main()
{
    printf("This is MAPP CountLeds running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    displayBarPort = DISPLAY_BAR_RESET;

    j = 0; //the beginning

    while (true)
    {
        displayBarPort = j;
        thread_sleep_for(WAIT_TIME_MS);

        j++;    //increment j by 1
        
    }
}
