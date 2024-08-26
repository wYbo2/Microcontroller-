
#undef __ARM_FP

#include "mbed.h"

DigitalOut led_PB14(PB_14);
DigitalOut led_PB15(PB_15);
InterruptIn  button_PC12 (PC_12);

void toggleLED (void)
{
    led_PB14 = !led_PB14;
    led_PB15 = !led_PB15;
}

int main()
{
    printf("System core clock is: %d \n", SystemCoreClock);
    led_PB14 = 1;
    led_PB15 = 0;
    
    button_PC12.fall(&toggleLED);   //attach the addres of the toggleLED funciton to the falling edge

    while(1)
        __WFI();  //wait for interrupt

    return EXIT_SUCCESS;
   
}

