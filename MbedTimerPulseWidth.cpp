
#include <chrono>
#undef __ARM_FP

#include "mbed.h"
using namespace std::chrono; 

DigitalOut led_PB14(PB_14);
DigitalIn switch_PB12 (PB_12);
Timer t;
unsigned int pulseWidth = 0;

int main()
{

    printf("System core clock is: %d \n", SystemCoreClock);
    led_PB14 = 0;
    if (switch_PB12 == 1)   //if PB12 is set as 1 at the beginning, should wait for it to set to 0
    {
        led_PB14 = 1;
        while (switch_PB12 == 1); //wait for PB12 switch to 0
        led_PB14 = 0;
    }

    while (switch_PB12 == 0); //wait for PB12 switch to 1

    t.start();  //start timer
    led_PB14 = 1;

    while (switch_PB12 == 1); //wait for PB12 switch to 0

    pulseWidth = duration_cast<milliseconds> (t.elapsed_time()).count();     
    printf ("The pulse width is %u millisecond\n", pulseWidth );

    t.stop();   //stop timer
    led_PB14 = 0;

    while (true); //stop the code here

}//main
