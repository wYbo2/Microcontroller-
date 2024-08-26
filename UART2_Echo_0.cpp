
#undef __ARM_FP

#include "mbed.h"


#define UART2_TX    PA_2
#define UART2_RX    PA_3

void UART2_init (void);
void UART2_write (int ch);
char UART2_read (void);

unsigned char message_send[] = "Hello!\n";

int main(void)
{
    char chData;
    int i;
  
    UART2_init();
    for (i = 0; i < 7; i++)
    {
        UART2_write(message_send[i]); //send 1 char
    }
    
    while (1) 
    {
       chData = UART2_read();
       UART2_write(chData);
    }
}

//Initialize UART2
void UART2_init (void)
{
    //enable the clocks
    RCC->APB1ENR |= 0x05;   //enable GPIOA clock and AFIO clock
    RCC->APB1ENR |= 0x20000; //enable UART2 clock

    //configure PA_2 for UART2 TX
    GPIOA->CRL &= 0xFFFFF0FF;
    GPIOA->CRL |= 0x0900;    //AF output push-pull, 10MHz
    //configure PA_3 for UART2 RX
    GPIOA->CRL &= 0xFFFF0FFF;
    GPIOA->CRL |= 0x8000;    //input pull up/down
    GPIOA->ODR = 0x800C;      //input pull up
    
    USART2->BRR = 0x0EA6;   //SYSCLK = 72MHz, APB1 = 36MHz, oversampling by 16 and Baud rate 9600bps
    USART2->CR1 = 0x000C;   //enable TX and RX
    USART2->CR2 = 0x0000;   //1 stop bit
    USART2->CR3 = 0x0000;   //no hardware flow control
    USART2->CR1 |= 0x2000; //enable USART

    printf("CRL is: %0x \n", GPIOA->CRL);
    printf ("ODR is: %0x \n", GPIOA->ODR);
    printf("UART2 BRR is:%0x \n", USART2->BRR);
}

//write a char to UART2
void UART2_write (int ch)
{
    while (!(USART2->SR & 0x0080)); //wait until TX buffere empty
    USART2->DR = (ch & 0xFF);
    
}

//read a char from UART2
char UART2_read (void)
{
    while (!(USART2->SR & 0x0020)); //wait until char arrives
    return USART2->DR;

}