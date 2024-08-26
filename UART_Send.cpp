
#undef __ARM_FP

#include "mbed.h"

// Create a DigitalOutput object to toggle an LED
static DigitalOut led(PB_14);

// Create a BufferedSerial object with a default baud rate.
//PA_2: TX, PA_3: RX
static BufferedSerial serial_port(PA_2, PA_3);

int main(void)
{
    // Set desired properties (9600-8-N-1).
    serial_port.set_baud(9600);
    serial_port.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );

    // Application buffer to send the data
    char bufTx[] = {"This is a test!\n"};

    while (1) 
    {
            if (uint32_t num = serial_port.write(bufTx, sizeof(bufTx)))
            {
                // Toggle the LED.
                led = !led;
                
                thread_sleep_for(1000);
            
            }
    }
}
