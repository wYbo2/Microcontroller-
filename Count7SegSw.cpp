//Count7SegSw.cpp
#undef __ARM_FP

#include "mbed.h"
#include "seg7.h"

#define WAIT_TIME_MS 2

#define SEVEN_SEGMENT_MASK 0x000000FF //PORT B0: PB_7 - PB_0, for 7 Seg display
#define SEVEN_SEGMENT_RESET 0x00000000 

//Use the BusOut interface to combine a number of DigitalOut pins to write them at once. 
//This API is useful for writing to multiple pins together as single interface instead of individual pins.
//You can have up to 16 pins in a Bus.
//The order of pins in the constructor is the reverse order of the pins in the byte order. 
//So if you have BusOut(a,b,c,d,e,f,g,h), 
//then the order of bits in the byte would be hgfedcba with a being bit 0, b being bit 1, c being bit 2 and so on.
//Port C: PC_11 - PC_8 connect to DIG3 - DIG0
BusOut sevenSegmentDIG(PC_8, PC_9, PC_10, PC_11);

PortOut sevenSegmentPort(PortB, SEVEN_SEGMENT_MASK);

DigitalIn button(PC_13);

unsigned char outchar, press, i;
unsigned char qNum[4];


int main()
{
    unsigned char i;

    printf("This is MAPP Count7segSw running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    //reset
    sevenSegmentPort = SEVEN_SEGMENT_RESET;
    sevenSegmentDIG = 0;		//0b00000000
    thread_sleep_for(WAIT_TIME_MS);

    qNum[3] = 9; //contents of DIG3
    qNum[2] = 8; //contents of DIG2
    qNum[1] = 7; //contents of DIG1
    qNum[0] = 6; //contents of DIG0
    
    press = 0; 

    while (true)
    {
        for (i = 0; i < 4; i++) 
        {
            switch (i)
            {
                case 0: 
                        sevenSegmentDIG = 0b00000001; // enable DIG0
                        
                        break;
                case 1:
                        sevenSegmentDIG = 0b00000010; // enable DIG1
                        
                        break;
                case 2:
                        sevenSegmentDIG = 0b00000100;  // enable DIG2
                        
                        break;
                case 3:
                        sevenSegmentDIG = 0b00001000;  // enable DIG3
                        break;
                default:
                	break;
            }

            outchar = qNum[i]; //get one value for the DIG
            sevenSegmentPort = convert(outchar); //convert to LED code

            thread_sleep_for(WAIT_TIME_MS);

        }

        if (press == 0) //switch press first time
        {
            if (button.read() == 0) // if RB5 is pressed
            {
                //clear the display
                sevenSegmentPort = SEVEN_SEGMENT_RESET;
                sevenSegmentDIG = 0b00000000;

                press = 1; //switch being pressed
                qNum[0] ++; //increase DIG0 value 
                update(qNum, 4); //adjust the rest of values
            }
        }

        while (button.read() == 0);  //wait until button is released

        press = 0; //switch released
        
    }
}
