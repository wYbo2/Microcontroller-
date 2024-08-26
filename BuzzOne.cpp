//BuzzOne.cpp
// Program to activate buzzer with one tone

#undef __ARM_FP

#include "mbed.h"
#define WAIT_TIME_MS 1000
#define WAIT_TIME_US 3000

#define DISPLAY_BAR_MASK 0x000000FF //PORT C0: PC_7 - PC_0
#define DISPLAY_BAR_RESET 0x00000000 

//set Port C0 as output
PortOut displayBarPort(PortC, DISPLAY_BAR_MASK);

//Set Port A, GPIO Pin 1 (PA_1) as digitial out put pin
//declare a buzzer as a DigitalOut object by passing PA_1 as the initialition parameter 
DigitalOut buzzer(PA_1); 

//Function to generate one tone
void onetone(void) 
{
    unsigned int k;
    
    //Determines duration of tone
    for (k = 0; k < 100; k++) 
    {
        wait_us(3000);  
        buzzer = !buzzer; //Invert logic level at PA_1       
    }
}

int main()
{
    printf("This is MAPP BuzzOne running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    
    displayBarPort = DISPLAY_BAR_RESET;

    buzzer = 0;

    //sound ON then OFF
    onetone( ); 
    
    //pattern on LED display bar: ob10101010
    displayBarPort = 0xAA;
    thread_sleep_for(WAIT_TIME_MS);

     //sound ON then OFF
    onetone( ); 
    
    //pattern on LED display bar: 0b01010101
    displayBarPort = 0x55;
    thread_sleep_for(WAIT_TIME_MS);

    while (true);    //loop forever to stop music!

}


