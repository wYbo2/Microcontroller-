
#undef __ARM_FP

#include "mbed.h"

DigitalOut led_PB14(PB_14);

void SysTick_Handler(void)
{  
    led_PB14 = !led_PB14;  
   
}

int main()
{
    printf("System core clock is: %d \n", SystemCoreClock);
    led_PB14 = 1;

    __disable_irq();        //global disable IRQs

    //configure SysTick
    SysTick->LOAD = 14400000 - 1;   //reload with number of clocks per 200ms,
                            //N = delay x SYSCLK = 0.2 x 72MHz = 14400000
    SysTick->VAL = 0;       //clear current value register
   
    NVIC_SetPriority(SysTick_IRQn,  0);
    HAL_NVIC_EnableIRQ( SysTick_IRQn );

    NVIC_SetVector(SysTick_IRQn, (uint32_t)&SysTick_Handler);

    __enable_irq();          //global enable IRQs
   
    SysTick->CTRL = 0x07;   //Enable the Timer,  interrupt, use system clock

   
    while (true);

}
