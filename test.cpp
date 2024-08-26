#undef __ARM_FP
#include "mbed.h"

// PWM output pin for servo
PwmOut servo(PB_5); // Use a PWM-capable pin, like PA_6
DigitalIn button_PC12 (PC_12);
DigitalIn button_PA15 (PA_15);
DigitalOut LED(PB_14);

// Function to set the servo position (0 to 180 degrees)
void set_servo_position(int degrees) {
    // Ensure the degrees value is within the valid range
    if (degrees < 0) degrees = 0;
    if (degrees > 180) degrees = 180;

    // Calculate the pulse width (1ms to 2ms corresponding to 0 to 180 degrees)
    float pulse_width = 0.001 + (0.001 * degrees / 180.0);

    // Set the PWM period and pulse width
    servo.period(0.02); // 20ms period (50Hz)
    servo.pulsewidth(pulse_width); // Set the pulse width
}

int main() {
    // Initialize the servo to the middle position (90 degrees)
    set_servo_position(90);

    // You can add more code here to move the servo to different positions
    while (true) {
        if(button_PA15 == 1){
            LED = 1;
            set_servo_position(0); // Move to 0 degrees
            thread_sleep_for(1000); // Wait 1 second
        }
        else{
            LED = 0;
            set_servo_position(180); // Move to 180 degrees
            thread_sleep_for(1000); // Wait 1 second
        }
    }
}