
#undef __ARM_FP

#include "mbed.h"

#define DISPLAY_BAR_MASK 0x000000FF //PORT C0: PC_7 - PC_0
#define DISPLAY_BAR_RESET 0x00000000 

PortOut displayBarPort(PortC, DISPLAY_BAR_MASK); //for LED bar update
DigitalOut motor_PA7(PA_7);             //for motor control
Ticker  LEDBar;                         //the Ticker object
DigitalIn  switch_PB12 (PB_12);         //the switch PB12

unsigned char j; //8 bit data type, ranging from 0 to 255

void ISR_Ticker(void)
{
    j++;

    displayBarPort = j;
     
}

int main()
{
    //reset the LED bar
    displayBarPort = DISPLAY_BAR_RESET;

    j = 0;

    LEDBar.attach(&ISR_Ticker, 500ms);

    while(1)
    {
        if (switch_PB12 == 0)   //if switch PB12 is ON
            motor_PA7 = 1;      //turn on motor
        else
             motor_PA7 = 0;     //else, turn off motor
       
    }//while
   
}//main
