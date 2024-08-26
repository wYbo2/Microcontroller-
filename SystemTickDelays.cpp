
#undef __ARM_FP

#include "mbed.h"

DigitalOut led_PB14(PB_14);

void systick_delay_ms (int n);

int main()
{
    printf("System core clock is: %d \n", SystemCoreClock);
   
    while (true)
    {
        systick_delay_ms (1000); //delay 1s

        led_PB14 = ! led_PB14;

    }
    
}

void systick_delay_ms (int n)
{
    int i;
    //configure SysTick
    SysTick->LOAD = 72000;   //reload with number of clocks per ms,
                            //N = delay x SYSCLK = 0.001 x 72MHz = 72000
    SysTick->VAL = 0;       //clear current value register
    SysTick->CTRL = 0x05;   //Enable the Timer,  no interrupt, use system clock

    for (i = 0; i < n; i++)
    {
        while ((SysTick->CTRL & 0x10000) == 0);  //wait until the COUNTFLAG is set
    }

    SysTick->CTRL = 0; //stop the timer (Enable = 0)
}