
#undef __ARM_FP

#include "mbed.h"
#include "lcd.h"

// Maximum number of element the application buffer can contain
#define MAXIMUM_BUFFER_SIZE    32
#define UART2_TX    PA_2
#define UART2_RX    PA_3

#define DISPLAY_BAR_MASK 0x000000FF //PORT C0: PC_0 - PC_7
#define DISPLAY_BAR_RESET 0x00000000 

PortOut displayBarPort(PortC, DISPLAY_BAR_MASK);

PwmOut buzzer(PA_1);
PwmOut relay(PA_6);
PwmOut motor(PA_7);

// Create a DigitalOutput object to toggle an LED
//PB_14-> send data, PB_15-> receive data
static DigitalOut led_PB14(PB_14);
static DigitalOut led_PB15(PB_15);



// Create a BufferedSerial object with a default baud rate.
//PA_2: TX, PA_3: RX
static BufferedSerial serial_port(UART2_TX, UART2_RX);

//1 for buzzer, 2 for motor, 3 for relay, 4 for led bar
unsigned char nTest = 0;

 // Application buffer to send the data
char bufRx[MAXIMUM_BUFFER_SIZE] = {0};
char bufTx[] = {"Please select your test:\n1. Buzzer\n2. Motor\n3. Relay\n4. LED Bar\nYour selection is: "};
char bufError[] = {"\nNot supported! Please try again!\n\n"};
char bufTest[2] = {0, '\0'};
char bufLCD[] = {"Start testing "};
char bufBuzzer[] = {"Buzzer"};
char bufMotor[] = {"Motor"};
char bufRelay[] = {"Relay"};
char bufLEDBar[] = {"LED Bar"};
char bufTestDone[] = {"\nTest done!\n\n"};

uint32_t sendMsgToPC (char msg[], int size)
{
    uint32_t numRet = 0;
    numRet = serial_port.write(msg, size); 
    if (numRet) 
    {
        // Toggle the LED.
        led_PB14 = !led_PB14;
        
        thread_sleep_for(50);

    }
    return numRet;
}

int main(void)
{
    lcd_init();					// Initialise LCD module
    lcd_write_cmd(0x80);		// Move cursor to line 1 position 1
   
    displayBarPort = DISPLAY_BAR_RESET;

    // Set desired properties (9600-8-N-1).
    serial_port.set_baud(9600);
    serial_port.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );

   

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
                
                //lcd_write_cmd(0x01);
                //lcd_write_data(bufRx[0]); 		// write to LCD
                
                if (bufRx[0] >= '1' && bufRx[0] <= '4') 
                {
                    //1 or 2 or 3 or 4 is selected
                    bufTest[0] = bufRx[0];
                    nTest = std::atoi(bufTest);
                    serial_port.write(bufRx, 1); //echo back to PC
                }
                else 
                {
                    //selection is not supported
                    sendMsgToPC(bufError, sizeof (bufError));  //send the error message
                    sendMsgToPC(bufTx, sizeof (bufTx));     //ask user to select again
                    continue;
                    
                }
              
                thread_sleep_for(50);
            }

            lcd_write_cmd(0x01); 		// clear LCD
            for (int k = 0; k < sizeof(bufLCD); k++)
                lcd_write_data(bufLCD[k]); 		// write to LCD
            
            lcd_write_cmd(0xC0); 		// move to 2nd line

            switch (nTest)
            {
                case 1:
                        //test buzzer
                        for (int k = 0; k < sizeof(bufBuzzer); k++)
                            lcd_write_data(bufBuzzer[k]); 		// write to LCD
                        buzzer.resume();
                        buzzer.period_ms(5);
                        buzzer.write(0.80f);

                        thread_sleep_for(2000);
                        buzzer.suspend();

                        break;
                case 2: 
                        //test motor
                        for (int k = 0; k < sizeof(bufMotor); k++)
                            lcd_write_data(bufMotor[k]); 		// write to LCD
                        motor.resume();
                        motor.period_ms(1000);
                        motor.write(0.50f);

                        thread_sleep_for(4000);
                        motor.suspend();

                        break; 
                case 3:
                        //test relay
                        for (int k = 0; k < sizeof(bufRelay); k++)
                            lcd_write_data(bufRelay[k]); 		// write to LCD
                        relay.resume();
                        relay.period_ms(1000);
                        relay.write(0.50f);

                        thread_sleep_for(4000);
                        relay.suspend();

                        break;
                case 4:
                        //test LED bar
                        for (int k = 0; k < sizeof(bufLEDBar); k++)
                            lcd_write_data(bufLEDBar[k]); 		// write to LCD
                            
                            for (int l = 0; l < 4; l++)
                            {
                                displayBarPort = DISPLAY_BAR_MASK;
                                thread_sleep_for(500);
                                displayBarPort = DISPLAY_BAR_RESET;
                                thread_sleep_for(500);

                            }
                            

                        break;
                default: 
                        break;

            }

            sendMsgToPC(bufTestDone, sizeof(bufTestDone));

            if (uint32_t num1 = serial_port.write(bufTx, sizeof(bufTx))) 
            {
                // Toggle the LED.
                led_PB14 = !led_PB14;
                
                thread_sleep_for(50);
            
            }


            thread_sleep_for(50);
    }
}
