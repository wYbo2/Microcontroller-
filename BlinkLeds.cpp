//BlinkLeds.cpp
//program to light up alternate leds on General I/O Board

#undef __ARM_FP

#include "mbed.h"
#define WAIT_TIME_MS 1000

#define DISPLAY_BAR_MASK 0x000000FF //PORT C0: PC_7 - PC_0
#define DISPLAY_BAR_RESET 0x00000000 

PortOut displayBarPort(PortC, DISPLAY_BAR_MASK);

int main()
{
    printf("This is MAPP BlinkLeds running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    displayBarPort = DISPLAY_BAR_RESET;

    while (true)
    {
        displayBarPort = 0xAA;
        thread_sleep_for(WAIT_TIME_MS);

        displayBarPort = 0x55;
        thread_sleep_for(WAIT_TIME_MS);
        
    }
}
