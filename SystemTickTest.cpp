
#undef __ARM_FP

#include "mbed.h"



int main()
{
     printf("System core clock is: %d \n", SystemCoreClock);
    //Configure SysTick
    SysTick->LOAD = 72000; //delay 0.001 sec: N = delay x SYSCLK = 0.001 x 72MHz = 72000
    SysTick->VAL = 0; //clear current value register
    SysTick->CTRL = 0x05;        //enable it, no interrupt, use system clock
   
    while ((SysTick->CTRL & 0x10000) == 0);  //wait until the COUNTFLAG is set
    
    SysTick->CTRL = 0; //Stop the timer, Enable = 0
    
    printf("SysTick value register value is: %d \n", SysTick->VAL);
   

    while (1);
    
}
