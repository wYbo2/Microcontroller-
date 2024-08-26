// LCD2Lines.cpp
// Program to test LCD.
// The LCD display with two lines, 20 characters each.
// PORT A1: PA_15 : PA_8
// There are three control lines (PA_14:PA_12) and four data lines (PA_11 : PA_8).
// PA_14 - RS=0 Data represents Command, RS=1 Data represents Character
// PA_13 - RW=0 Writing into the LCD module
// PA_12 - E =1 Data is latched into LCD module during low to hight transition  
#undef __ARM_FP

#include "mbed.h"
#include "lcd.h"	

int main()
{
    printf("This is MAPP LCD2Lines running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

	lcd_init();					// Initialise LCD module

	lcd_write_cmd(0x80);		// Move cursor to line 1 position 1
    lcd_write_data(0x41); 		// write "A" to LCD
    lcd_write_data(0x42);		// write "B" to LCD
    lcd_write_data(0x43); 		// write "C" to LCD
    
    lcd_write_cmd(0xC0);		// Move cursor to line 2 position 1
    lcd_write_data(0x31); 		// write "1" to LCD
    lcd_write_data(0x32);		// write "2" to LCD
    lcd_write_data(0x33); 		// write "3" to LCD
    
    while(true);					//stop here for now

}						
