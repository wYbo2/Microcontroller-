/* Test_ADC.cpp
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#undef __ARM_FP

#include "mbed.h"

#define WAIT_TIME_MS_0 50 
#define WAIT_TIME_MS_1 500

AnalogIn varResistor(PA_0);

uint16_t voltage_Code = 0;  //read the ADC code
float voltage_Volts = 0.0;  //read the voltage in volts
float voltage_Ref = 0.0;    //read the current voltage ref value
float voltage_data = 0.0;   //read the voltage data: [0, 1]

int main()
{
    printf("This is the modified bare metal example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    
    varResistor.set_reference_voltage(3.3);
    voltage_Ref = varResistor.get_reference_voltage();
    printf ("The Voltage Ref is: %f \n", voltage_Ref);

   // while (true)
    {
        voltage_Volts = varResistor.read_voltage();
        printf ("The Voltage is: %5.3f \n", voltage_Volts);
        voltage_data = varResistor.read();
        printf ("The Voltage data in [0,1] is: %5.3f \n", voltage_data);

        voltage_Code = varResistor.read_u16();
        printf ("The normalized 16-bit value is: %#x \n", voltage_Code);
        voltage_Code = voltage_Code >> 4;
        printf ("The original ADC value is: %#x \n", voltage_Code);
        voltage_Code = voltage_Code >> 4;
        printf ("The upper 8-bit of ADC value is: %#x \n", voltage_Code);

        thread_sleep_for(WAIT_TIME_MS_0);
    }

    return 0;
}
