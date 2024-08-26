
#undef __ARM_FP

#include "mbed.h"

#define WAIT_TIME_MS_0 500 
#define WAIT_TIME_MS_1 1500

DigitalOut led0(PB_14);
DigitalOut led1(PB_15);

int main()
{
    while (true)            //repeat
    {
        led0 = 1;                           //turn on LED 0
        led1 = 0;                           //turn off LED 1
        thread_sleep_for(1);   //delay for 500ms
        led0 = 0;                           //turn off LED 0
        led1 = 1;                           //turn on LED 1
        thread_sleep_for(1);   //delay for 500ms
    }
}
