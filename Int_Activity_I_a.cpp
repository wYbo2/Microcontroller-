
#undef __ARM_FP

#include "mbed.h"

#define WAIT_TIME_MS 500
#define DISPLAY_BAR_MASK 0x000000FF //PORT C0: PC_7 - PC_0
#define DISPLAY_BAR_RESET 0x00000000 

PortOut displayBarPort(PortC, DISPLAY_BAR_MASK);
DigitalOut motor_PA7(PA_7);             //for motor control
DigitalIn  button_PC12 (PC_12);       //the button PC12

unsigned char j; //8 bit data type, ranging from 0 to 255
unsigned char press;

void LED_PC7_PC0(void)      //the function to shift a set-bit from left to right
{
    
    j = 0x80; //Initialize j with 1000 0000b, i.e., the left-most bit (MSB)

    while (j != 0x01)   //check that the bit has not been shifted to the right-most bit (LSB) i.e., 0000 0001b
    {
        displayBarPort = j;
        thread_sleep_for(WAIT_TIME_MS);

         j = j >> 1;    //make use of logical right-shift bit-wise operator to shift the data to the right     
    }

    displayBarPort = j; //Display update LED bar
                        //Stop at 0000 0001b
    thread_sleep_for(WAIT_TIME_MS);
}

int main()
{
    //reset the LED bar
    displayBarPort = DISPLAY_BAR_RESET;

    press = 0;
     
    while(1)
    {
        LED_PC7_PC0(); //move the LED bar (PC7-PC0) from bit 7 to bit 0
        //polling the button PC12 status
        if (button_PC12 == 0)
        {
            press ++; //to track first or second time pressing button PC12
            printf ("button PC12 is pressed\n");
        }

        if (press == 1)     //first press
        {
            motor_PA7 = 1;  //turn on motor
        }
        else if (press == 2)    //second press
        {
            motor_PA7 = 0;      //turn off motor
            press = 0;          //reset the pressing counter
        }      
    }//while*/
   
}//main

