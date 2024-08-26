
#undef __ARM_FP

#include "mbed.h"

#define WAIT_TIME_MS 200

#define DISPLAY_BAR_MASK 0x000000FF //PORT C0: PC_7 - PC_0
#define DISPLAY_BAR_RESET 0x00000000 

PortOut displayBarPort(PortC, DISPLAY_BAR_MASK);

unsigned char j; //8 bit data type, ranging from 0 to 255

DigitalOut led_PB14(PB_14);
DigitalOut led_PB15(PB_15);
Timeout flipper1;
Timeout flipper2;

void flip1()
{ 
    led_PB14 = !led_PB14;   //toggle LED PB14
}

void flip2()
{ 
    led_PB15 = !led_PB15;   //toggle LED PB14
}

int main()
{
    printf("System core clock is: %d \n", SystemCoreClock);
    led_PB14 = 1;
    led_PB15 = 0;
    displayBarPort = DISPLAY_BAR_RESET;

    j = 0; //the beginning

    flipper1.attach(&flip1, 2000ms); // the address of the function to be attached (flip1) and the interval (2 seconds)
    flipper2.attach(&flip2, 1000ms); // the address of the function to be attached (flip2) and the interval (1 seconds)

    // update LED bar in a main loop. flipper will interrupt it to call flip
    while (true) 
    {
        displayBarPort = j;
        thread_sleep_for(WAIT_TIME_MS);

        j++;    //increment j by 1

    }
  
}
