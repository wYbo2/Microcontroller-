
#undef __ARM_FP

#include "mbed.h"

BusIn  buttons(PC_12, PA_15);   //create a BusIn object: buttons, by passing PC_12 and PA_15 pins as pin0 and pin1  
BusOut leds(PB_14, PB_15);      //create a BusOut object: leds, by passing PB_14 and PB_15 pins as pin0 and pin1

int main()
{
    char data;              // variable to temporarily store the buttons data

    while (true)            // repeat forever the code below
    {
        data = buttons;     // read the inputs from buttons (BusIn) and save in data
        
        leds = data;        //output the data to leds (BusOut)
        
    }
    
    return 0;
}
