//PlayMusic-2-Tigers
// Program to play music - 2 Tigers

#undef __ARM_FP

#include "mbed.h"

//This is a macro definition of bass, midrange, and treble frequencies
#define NOTE_L1  262
#define NOTE_L2  294
#define NOTE_L3  330
#define NOTE_L4  349
#define NOTE_L5  392
#define NOTE_L6  440
#define NOTE_L7  494
#define NOTE_M1  523
#define NOTE_M2  587
#define NOTE_M3  659
#define NOTE_M4  698
#define NOTE_M5  784
#define NOTE_M6  880
#define NOTE_M7  988
#define NOTE_H1  1046
#define NOTE_H2  1175
#define NOTE_H3  1318
#define NOTE_H4  1397
#define NOTE_H5  1568
#define NOTE_H6  1760
#define NOTE_H7  1976

//musical notation of Two Tigers 
const static int twoTiger[] = { 
NOTE_M1,NOTE_M2,NOTE_M3,NOTE_M1, 
NOTE_M1,NOTE_M2,NOTE_M3,NOTE_M1, 
NOTE_M3,NOTE_M4,NOTE_M5, 
NOTE_M3,NOTE_M4,NOTE_M5, 
NOTE_M5,NOTE_M6,NOTE_M5,NOTE_M4,
NOTE_M3,NOTE_M1, 
NOTE_M5,NOTE_M6,NOTE_M5,NOTE_M4,
NOTE_M3,NOTE_M1, 
NOTE_M2,NOTE_L5,
NOTE_M1,
NOTE_M2,NOTE_L5,
NOTE_M1
};

////note duration of Two Tigers, 2 is half a beat, 1 is a beat.
const static int tempo[] = { 
2,2,2,2, 
2,2,2,2, 
2,2,1, 
2,2,1,  
2,2,2,2,
1,1,
2,2,2,2,
1,1,
1,1,
1,1,
1,1,
1,1
};

PwmOut buzzer(PA_1);
static int BPM = 80;  

static void silence() 
{
    buzzer.write(0.0f); // silence!
}


int main()
{
    printf("This is MAPP PlayMusic-2-Tigers running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    
    //Play music
    buzzer.resume();
    int noteDuration;

    int nsize = sizeof(twoTiger) / sizeof(int);
    for (int thisNote = 0; thisNote < nsize; thisNote++)
    {
         noteDuration = 500 / tempo[thisNote];//a beat for 0.5 second

        buzzer.period_us(1000000/(twoTiger[thisNote]));
        buzzer.write(0.80f); 
        // after half the length of this tone, we silence
        thread_sleep_for(noteDuration / 2);
        silence();

        //after the full length of this tone, call next note 
        thread_sleep_for(noteDuration); 
        
    }
    // we're done! just finish this note and silence
    thread_sleep_for(noteDuration / 2);  
    silence();   
    buzzer.suspend();

    while (1);

}


