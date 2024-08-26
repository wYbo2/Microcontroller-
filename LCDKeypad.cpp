// LCDKeypad.cpp
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
#include "keypad.h"	

unsigned char key, outChar;
char Message1 [ ] = "Enter PIN number :  ";	  // Defining a 20 char string

// ---- Main Program ---------------------------------------------------------------
int main( )
{
	printf("This is MAPP LCDKeypad running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

	int i;
	lcd_init();						// Initialise LCD module

	while(1)
	{
		lcd_write_cmd(0x80);			// Move cursor to line 1 position 1
		for (i = 0; i < 20; i++)		//for 20 char LCD module
		{
			outChar = Message1[i];
			lcd_write_data(outChar); 	// write character data to LCD
		}
		

		lcd_write_cmd(0xC0);			// Move cursor to line 2 position 1
		for (i = 0; i < 20; i++)		//for 20 number
		{ 
			key = getkey(); 				// waits and get an ascii key number when pressed
			lcd_write_data(key);		//display on LCD
			
		}
		
		thread_sleep_for(1000);                 // wait 1 second
		lcd_write_cmd(0x01);			// 00000001 Clear Display instruction
	}
}




