
#undef __ARM_FP

#include "mbed.h"


#define UART2_TX    PA_2
#define UART2_RX    PA_3

void UART2_init (void);
void UART2_write (int ch);

unsigned char message_send[] = "Hello!\n";

int main(void)
{
    int i;
    
    UART2_init();

    while (1) 
    {
        for (i = 0; i < 7; i++)
        {
            UART2_write(message_send[i]); //send 1 char
        }
         thread_sleep_for(100); //delay between messages
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
    USART2->BRR = 0x0EA6;   //SYSCLK = 72MHz, APB1 = 36MHz, oversampling by 16 and Baud rate 9600bps
    USART2->CR1 = 0x0008;   //enable TX
    USART2->CR2 = 0x0000;   //1 stop bit
    USART2->CR3 = 0x0000;   //no hardware flow control
    USART2->CR1 |= 0x2000; //enable USART

}

//write a char to UART2
void UART2_write (int ch)
{
    while (! (USART2->SR & 0x0080)); //wait until TX buffere empty
    USART2->DR = (ch & 0xFF);
    
}
