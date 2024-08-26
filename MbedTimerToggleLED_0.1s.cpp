
#include <chrono>
#undef __ARM_FP

#include "mbed.h"
using namespace std::chrono; 

DigitalOut led_PB14(PB_14);
Timer t;

int main()
{

    printf("System core clock is: %d \n", SystemCoreClock);
    led_PB14 = 0;
    
    t.start();  //start timer
    
    while (true)
    {
        if ( duration_cast<milliseconds> (t.elapsed_time()).count() >= 100 )
        {
            led_PB14 = !led_PB14;
            t.reset();
        }

    }//while

}//main
