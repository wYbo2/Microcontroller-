/* ADC.cpp
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#undef __ARM_FP

#include "mbed.h"

#define WAIT_TIME_MS_0 100 
#define WAIT_TIME_MS_1 500

#define HIGH 0x4E

AnalogIn varResistor(PA_0);
DigitalOut motor(PA_7);
DigitalOut relay(PA_6);

uint16_t voltage_Code = 0;  //read the ADC code
uint8_t  waterLevel = 0;    //8-bit variable to hold the high 8-bit of voltage_Code

int main()
{
    printf("This is the modified bare metal example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
       
   for( ; ; )
    {
        voltage_Code = varResistor.read_u16();
        printf ("The normalized 16-bit value is: %#x \n", voltage_Code);

        voltage_Code = voltage_Code >> 4;
        printf ("The original ADC value is: %#x \n", voltage_Code);
        
        voltage_Code = voltage_Code >> 4;
        printf ("The upper 8-bit of ADC value is: %#x \n", voltage_Code);

        waterLevel = (uint8_t) voltage_Code;

        if (waterLevel > HIGH) 
        {
            //Turn on/off Motor
            motor = 1;
            thread_sleep_for(WAIT_TIME_MS_1);
            motor = 0;
            thread_sleep_for(WAIT_TIME_MS_0);              
                    
        }
        else 
        {
            //Turn on/off Relay
            relay = 1;
            thread_sleep_for(WAIT_TIME_MS_1);
            relay = 0;
            thread_sleep_for(WAIT_TIME_MS_0);                      
        }
    }

    return 0;
}
