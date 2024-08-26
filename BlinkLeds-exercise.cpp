//BlinkLeds-exercise.cpp
//program to light up alternate leds on General I/O Board

#undef __ARM_FP

#include "mbed.h"
#define WAIT_TIME_MS 1000

#define DISPLAY_BAR_MASK 0x000000FF //PORT C0: PC_7 - PC_0
#define DISPLAY_BAR_RESET 0x00000000 

PortOut displayBarPort(PortC, DISPLAY_BAR_MASK);
//Declare the GPIO pins for the Switch as DigitalIn type
DigitalIn switch_PB12(PB_12); 
DigitalIn switch_PA4(PA_4);
DigitalIn switch_PD2(PD_2);

int main()
{
    printf("This is MAPP BlinkLeds-exercise running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    displayBarPort = DISPLAY_BAR_RESET;

    while (true)
    {
        while (switch_PA4.read() == 0); //loop here when switch is on
        
        displayBarPort = 0xAA;
        thread_sleep_for(WAIT_TIME_MS);

        displayBarPort = 0x55;
        thread_sleep_for(WAIT_TIME_MS);
        
    }
}
