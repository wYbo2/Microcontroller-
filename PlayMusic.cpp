//PlayMusic.cpp
// Program to activate buzzer with one tone

#undef __ARM_FP

#include "mbed.h"
#include "music.h"

int main()
{
    printf("This is MAPP PlayMusic running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    
    //Play music
    music();

    while (1);

}


