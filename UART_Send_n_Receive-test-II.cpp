
#undef __ARM_FP

#include "mbed.h"
#include "lcd.h"

// Maximum number of element the application buffer can contain
#define MAXIMUM_BUFFER_SIZE    32
#define UART2_TX    PA_2
#define UART2_RX    PA_3

// Create a DigitalOutput object to toggle an LED
//PB_14-> send data, PB_15-> receive data
static DigitalOut led_PB14(PB_14);
static DigitalOut led_PB15(PB_15);

// Create a BufferedSerial object with a default baud rate.
//PA_2: TX, PA_3: RX
static BufferedSerial serial_port(UART2_TX, UART2_RX);

int main(void)
{
    lcd_init();					// Initialise LCD module
    lcd_write_cmd(0x80);		// Move cursor to line 1 position 1

    // Set desired properties (9600-8-N-1).
    serial_port.set_baud(9600);
    serial_port.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );

    printf("GPIOA CRL is: %0x \n", GPIOA->CRL);
    printf("GPIOA ODR is: %0x \n", GPIOA->ODR);
    printf("UART2 BRR is:%0x \n", USART2->BRR);

    // Application buffer to send the data
    char bufRx[MAXIMUM_BUFFER_SIZE] = {0};
    char bufTx[] = {"This is a test!\n"};
    unsigned char nCount = 0;   //totoal number of char received and displayed on LCD, 1 line of LCD is 20 chars
    unsigned char nLine = 1;    //start with 1st line

    if (uint32_t num1 = serial_port.write(bufTx, sizeof(bufTx))) 
    {
        // Toggle the LED.
        led_PB14 = !led_PB14;
        
        thread_sleep_for(50);
    
    }
    while (1) 
    {
           
            if (uint32_t num2 = serial_port.read(bufRx, sizeof(bufRx))) 
            {
                // Toggle the LED.
                led_PB15 = !led_PB15;
                
                lcd_write_data(bufRx[0]); 		// write to LCD
                nCount ++;
                if (nCount >= 20)
                {
                    if (nLine == 1)
                    {
                        lcd_write_cmd(0xC0);		// Move cursor to line 2 position 1
                        nLine ++;
                        nCount = 0;
                    }  
                    else
                    {
                        lcd_Clear();
                        lcd_write_cmd(0x80);		// Move cursor to line 1 position 1
                        nLine = 1;
                        nCount = 0;
                    }                  
                }
                
                // Echo the input back to the terminal.
                if (bufRx[num2-1] == 0x0A || bufRx[num2-1] == 0x0D)
                {
                    bufRx[num2] = '\n';
                    serial_port.write(bufRx, num2+1);
                }
                else 
                {
                    serial_port.write(bufRx, num2);
                }
                
               
                thread_sleep_for(50);
            }
    }
}
