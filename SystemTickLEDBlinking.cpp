
#undef __ARM_FP

#include "mbed.h"

DigitalOut led_PB14(PB_14);

int main()
{
    printf("System core clock is: %d \n", SystemCoreClock);

    //configure SysTick
    SysTick->LOAD = 14400000 - 1;   //reload with number of clocks per 200ms,
                            //N = delay x SYSCLK = 0.2 x 72MHz = 14400000
    SysTick->VAL = 0;       //clear current value register
    SysTick->CTRL = 0x05;   //Enable the Timer,  no interrupt, use system clock

   
    while (true)
    {
       if(SysTick->CTRL & 0x10000)
            led_PB14 = ! led_PB14;

    }  
}
