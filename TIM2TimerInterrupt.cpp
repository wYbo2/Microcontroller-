
#undef __ARM_FP

#include "mbed.h"

DigitalOut led_PB14(PB_14);

void TIM2_IRQHandler()
{
    //Clear TIM2 update interrupt flag.
    TIM2->SR &= ~TIM_SR_UIF;
   
    led_PB14 = !led_PB14;   //toggle LED PB14
}

int main()
{
    printf("System core clock is: %d \n", SystemCoreClock);
   
    __disable_irq();    //global disable IRQ
    
    //Enable the TIM2 clock.
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;      //enable TIM2 clock
    
    //Make sure the timer's "counter" is off.
     TIM2->CR1 &= ~TIM_CR1_CEN;

    //Reset the peripheral.
    RCC->APB1RSTR |= (RCC_APB1RSTR_TIM2RST);
    RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST);

    TIM2->PSC = 7200 - 1;   //divided by 7200
    TIM2->ARR = 10000 - 1;  //count from 0 - 9999, total 10000 counts
    TIM2->CNT = 0;          //clear timer counter
           
    //Send an update event to reset the timer and apply settings.
    TIM2->EGR |= TIM_EGR_UG;

    //Enable TIM2 interrupts and set priority.
    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn, 0);

    __enable_irq();     //global enable IRQ

    NVIC_SetVector(TIM2_IRQn, (uint32_t)&TIM2_IRQHandler); //load the ISR

    //Clear TIM2_IRQn update interrupt,
    TIM2->SR &= ~TIM_SR_UIF;

    //Enable the hardware interrupt.
    TIM2->DIER |= TIM_DIER_UIE;

     //Enable the timer.
     TIM2->CR1 |= TIM_CR1_CEN;
    
    while(1)
        __WFI();  //wait for interrupt

    return EXIT_SUCCESS;
  
}
