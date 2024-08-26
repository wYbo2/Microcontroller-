
#undef __ARM_FP

#include "mbed.h"

#define WAIT_TIME_MS_0 500 
#define WAIT_TIME_MS_1 1500

BusOut leds(PB_14, PB_15);

int main()
{
    while (true)            //repeat
    {
        leds = 0b00000000;                   //turn off LEDs
        thread_sleep_for(WAIT_TIME_MS_0);   //delay for 500ms
       
        leds = 0b00000011;                  //turn on LEDs
        thread_sleep_for(WAIT_TIME_MS_0);   //delay for 500ms
    }
}
