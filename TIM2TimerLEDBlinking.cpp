
#undef __ARM_FP

#include "mbed.h"

DigitalOut led_PB14(PB_14);

int main()
{

    printf("System core clock is: %d \n", SystemCoreClock);

    //configure TIM2
    RCC->APB1ENR |= 1;      //enable TIM2 clock
    TIM2->PSC = 7200 - 1;   //divided by 7200
    TIM2->ARR = 10000 - 1;  //count from 0 - 9999, total 10000 counts
    TIM2->CNT = 0;          //clear timer counter
    TIM2->CR1 = 1;          //enable TIM2
     
    while (true)
    {
       while (!(TIM2->SR & 1)); //wait until UIF is set
       
       TIM2->SR &= ~1;          //clear UIF

       led_PB14 = !led_PB14;   //toggle LED PB14

    }  
}
