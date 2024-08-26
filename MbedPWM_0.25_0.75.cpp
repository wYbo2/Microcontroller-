
#undef __ARM_FP

#include "mbed.h"

PwmOut motor(PA_7);
DigitalIn button_PC12 (PC_12);

int main()
{

    printf("System core clock is: %d \n", SystemCoreClock);

    //specify period first
    motor.period(0.2f);   //0.2s period 
    motor.write(0.75f);     //75% duty cycle, relative to period
    
    printf("Duty cycle is: 0.75\n");

    while (button_PC12 == 1); //wait for pressing button
    while (button_PC12 == 0); //wait for releasing button

    motor.write(0.5f);     //50% duty cycle, relative to period

    printf("Duty cycle is: 0.5\n");

    while (button_PC12 == 1); //wait for pressing button
    while (button_PC12 == 0); //wait for releasing button

    motor.write(0.25f);     //25% duty cycle, relative to period
  
    printf("Duty cycle is: 0.25\n");

    while (button_PC12 == 1); //wait for pressing button
    while (button_PC12 == 0); //wait for releasing button

    motor.suspend();

    while (true);

    
}//main
