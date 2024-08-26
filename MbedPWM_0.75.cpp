
#undef __ARM_FP

#include "mbed.h"

PwmOut motor(PA_7);

int main()
{

    printf("System core clock is: %d \n", SystemCoreClock);

    //specify period first
    motor.period_us(200);   //0.2ms period 
    motor.write(0.75f);     //75% duty cycle, relative to period
    
    printf("PWM is started.\n");
  
    while (true);

    
}//main
