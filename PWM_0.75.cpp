
#undef __ARM_FP

#include "mbed.h"

int main()
{

    printf("System core clock is: %d \n", SystemCoreClock);

    //enable GPIOA clock
    RCC->APB2ENR |= 0x04;
    
    //Configure GPIO pin : PA7, Alternate Function Output, Push-Pull: CNF[1:0] = [1,0], output speed 10MHz: MODE[1:0]= [0,1]
    GPIOA->CRL |= 0x90000000; //bit 31 - bit 28: 1001b
    GPIOA->CRL &= 0x9FFFFFFF; 
    
    //set up TIM3
    RCC->APB1ENR |= 0x02;   //enable TIM3 clock
    TIM3->PSC = 60 - 1;     //divide by 60
    TIM3->ARR = 240 - 1;    //divide by 240
    TIM3->CNT = 0;          
    TIM3->CCMR1 = 0x6000;           //bit 14 : bit 12 = 110, PWM mode 1 for channel 2
    TIM3->CCER |= 0x0010;           //bit 4 (CC2E) = 1, enable output for channle 2
    TIM3->CCR2 = 180;           //pulse width 75%
    TIM3->CR1 |= 1;                 //enable timer

    printf("TIM3 PWM is started.\n");
  
    while (true);

    
}//main
