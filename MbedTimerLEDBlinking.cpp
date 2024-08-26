
#include <chrono>
#undef __ARM_FP

#include "mbed.h"
using namespace std::chrono; 

DigitalOut led_PB14(PB_14);
DigitalIn button_PC12 (PC_12);
Timer t;

int main()
{

    printf("System core clock is: %d \n", SystemCoreClock);

    t.start();  //start timer
         
    while (true)
    {
       if ( duration_cast<milliseconds> (t.elapsed_time()).count() >= 500 ) //every 500ms toggle the LED
       {
            led_PB14 = !led_PB14;   //toggle LED PB14
            printf ("The time taken was %llu millisecond\n", duration_cast<milliseconds> (t.elapsed_time()).count() ); 

            t.reset();              //reset the timer
       }

      if (button_PC12 == 0) //if button PC12 is pressed
       {
           while (button_PC12 == 0); //wait for the release of the button
           break;
       }
    } //while 

    t.stop();   //stop timer

    while (true); //stop the code here

}//main
