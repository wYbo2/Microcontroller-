//OnOffLeds.cpp
//Program to use 1 switch to control 8 leds on General I/O Board

#undef __ARM_FP

#include "mbed.h"

#define DISPLAY_BAR_MASK 0x000000FF 	//PORT C0: PC_7 - PC_0
#define DISPLAY_BAR_RESET 0x00000000 

//Declare the GPIO pins for the Switch as DigitalIn type
DigitalIn switch_PB12(PB_12); 
DigitalIn switch_PA4(PA_4);
DigitalIn switch_PD2(PD_2);

PortOut displayBarPort(PortC, DISPLAY_BAR_MASK);

int main()
{
    printf("This is MAPP OnOffLeds running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    displayBarPort = DISPLAY_BAR_RESET;

    while (true)
    {
        if (switch_PA4.read() == 0)
        { 
            //Turn on 4 LED Bars: PC_4, PC_5, PC_6, PC_7
            displayBarPort = 0xF0;
            
        }
        else 
        {
            //Turn on another 4 LED Bars: PC_0, PC_1, PC_2, PC_3
            displayBarPort = 0x0F;
            

        }

    }
}
