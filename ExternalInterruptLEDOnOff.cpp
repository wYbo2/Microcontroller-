
#undef __ARM_FP

#include "mbed.h"

DigitalOut led_PB14(PB_14);
DigitalOut led_PB15(PB_15);
DigitalIn  button_PC12 (PC_12);

void EXTI15_10_IRQHandler (void)
{
    led_PB14 = !led_PB14;
    led_PB15 = !led_PB15;
    EXTI->PR = 0x1000;      //clear interrupt pending flag

}

int main()
{
    printf("System core clock is: %d \n", SystemCoreClock);
    led_PB14 = 1;
    led_PB15 = 0;
    
    __disable_irq();                // //disable IRQs globally

    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; //enable AFIO clock

    AFIO->EXTICR[3] &= ~0x000F;     //clear port selection for EXTI12
    AFIO->EXTICR[3] |= 0x0002;      //select port C for EXTI12

    EXTI->IMR |= 0x1000;            //unmask EXIT12
    EXTI->FTSR |= 0x1000;           //set falling edge trigger. 

    NVIC_EnableIRQ(EXTI15_10_IRQn); //enable IRQ14, bit 8 of ISER[1]

    __enable_irq();                 //enable IRQs globally

    NVIC_SetVector(EXTI15_10_IRQn, (uint32_t)&EXTI15_10_IRQHandler); //load the ISR

     while(1)
        __WFI();  //wait for interrupt

    return EXIT_SUCCESS;
   
}

