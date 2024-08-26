
#undef __ARM_FP

#include "mbed.h"

DigitalIn button_PC12 (PC_12);
DigitalOut led_PB14 (PB_14);

int main()
{
    printf("System core clock is: %d Mhz\n", SystemCoreClock);
    uint32_t portC_CRH = GPIOC->CRH;
    uint32_t portB_CRH = GPIOB->CRH;
    
    printf("Port C CRH register value is: %#x \n", portC_CRH);
    printf("Port B CRH register value is: %#x \n", portB_CRH);

    while (1);
    
}
