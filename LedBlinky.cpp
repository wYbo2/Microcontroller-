/* LedBlinky
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#undef __ARM_FP

#include "mbed.h"

#define WAIT_TIME_MS_0 500 
#define WAIT_TIME_MS_1 1500

DigitalOut led1(LED1);
DigitalIn button(PC_13);

int main()
{
    printf("This is the modified bare metal Led blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    int nCount = 0;

    while (true)
    {
        if (button.read() == 0)
        { 
            // Button is pressed
            // wait for button is released
            while (button.read() == 0);

            nCount ++;
            nCount %= 2;

        }

        led1 = !led1;
        if (nCount == 0)
            thread_sleep_for(WAIT_TIME_MS_0);
        else
             thread_sleep_for(WAIT_TIME_MS_1);
    }
}
