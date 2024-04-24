/*
 * main.c
 *
 *  Created on: Apr 23, 2024
 *      Author: Marwan
 */

#include "STD_Types.h"
#include "BitMath.h"
#include <util/delay.h>

#define u8RedTotalSeconds 10
#define u8GreenTotalSeconds 15
#define u8YellowTotalSeconds 5

//MCAL
#include "DIO.h"

//HAL
#include "LCD.h"
#include "SEV.h"

//LCD Functions
void waiting_period();
void stop();
void go_time_for_cars();

//SevSeg Functions
void red_light(uint8,uint8);
void green_light(uint8, uint8);
void yellow_light(uint8, uint8);
void decrement_seven_segment(uint8*, uint8*);

// Custom characters for the lcd
	uint8 lcdCharGlob[2][8] = {
		{ 0x00, 0x00, 0x0E, 0x1F, 0x0E, 0x0A, 0x00, 0x00 },
		{ 0x00, 0x04, 0x0E, 0x04, 0x04, 0x0A, 0x00, 0x00 }

		};

int main(void)
{


	uint8 i = 0;
	uint8 u8ReadPinLoc;

	DIO_vidInit();
	DIO_enuActivePullUp(29, 1);
    LCD_vidInit();

    // Write custom characters to CGRAM
       for (uint8 j = 0; j < 3; j++)
       {
           // Set CGRAM address
           LCD_vidSendCmd(0, 0x40 + (j * 8)); // Each custom character occupies 8 addresses

           // Write custom character data
           for (uint8 k = 0; k < 8; k++)
           {
               LCD_vidWriteData(0, lcdCharGlob[j][k]);
           }
       }

	while (1)
	{

	    DIO_enumReadPin(29, &u8ReadPinLoc);

		if (u8ReadPinLoc == 1)
		{
			uint8 u8FirstSevVal = u8RedTotalSeconds / 10;
			uint8 u8SecSevVal = u8RedTotalSeconds % 10;

			LCD_vidSendCmd(0, 0x01);
			LCD_vidSendCmd(0, 0x80);

			for (uint8 i = u8RedTotalSeconds; i > 0; --i)
			{
				red_light(u8FirstSevVal, u8SecSevVal);
				decrement_seven_segment(&u8FirstSevVal, &u8SecSevVal);

				_delay_ms(1000);
				stop();
			}

			LCD_vidSendCmd(0, 0x01);
			LCD_vidSendCmd(0, 0x80);

			DIO_enumWritePin(7, 0);

			u8FirstSevVal = u8GreenTotalSeconds / 10;
			u8SecSevVal = u8GreenTotalSeconds % 10;

			for (uint8 i = u8GreenTotalSeconds; i > 0; --i)
			{
				green_light(u8FirstSevVal, u8SecSevVal);
				decrement_seven_segment(&u8FirstSevVal, &u8SecSevVal);

				_delay_ms(1000);

				go_time_for_cars();
			}

			DIO_enumWritePin(15, 0);
			LCD_vidSendCmd(0, 0x80);

			u8FirstSevVal = u8YellowTotalSeconds / 10;
			u8SecSevVal = u8YellowTotalSeconds % 10;

			for (uint8 i = u8YellowTotalSeconds; i > 0; --i)
			{
				yellow_light(u8FirstSevVal, u8SecSevVal);
				decrement_seven_segment(&u8FirstSevVal, &u8SecSevVal);

//        	_delay_ms(1000);

				// Special handling for the yellow light because of the lcd pattern
				// the delay is present in waiting_time()
				waiting_period();
			}

			DIO_enumWritePin(31, 0);

		}

	}

	return 0;
}

void waiting_period()
{
	static uint8 posLoc = (16 - 5) / 2;

	LCD_vidSendCmd(0,0x01);
	LCD_vidSendCmd(0, 0x80 + posLoc);

	LCD_vidWriteData(0, 'w');
	LCD_vidWriteData(0, 'a');
	LCD_vidWriteData(0, 'i');
	LCD_vidWriteData(0, 't');
	LCD_vidWriteData(0, lcdCharGlob[0][0]);

	_delay_ms(500);

	LCD_vidSendCmd(0,0x01);

	LCD_vidSendCmd(0, 0xC0 + posLoc);

	LCD_vidWriteData(0, 'w');
	LCD_vidWriteData(0, 'a');
	LCD_vidWriteData(0, 'i');
	LCD_vidWriteData(0, 't');
	LCD_vidWriteData(0, lcdCharGlob[0][0]);

	_delay_ms(500);
}

void stop()
{

	static uint8 i = 0;
	static uint8 UP;

	LCD_vidSendCmd(0, 0x01);
	LCD_vidSendCmd(0, UP + i);

	LCD_vidWriteData(0, 's');
	LCD_vidWriteData(0, 't');
	LCD_vidWriteData(0, 'o');
	LCD_vidWriteData(0, 'p');
	LCD_vidWriteData(0, lcdCharGlob[1][0]);


	i++;

	if(i % 2 != 0)
	{
		UP = 0xC0;
	}
	else
	{
		UP = 0x80;
	}

	if(i == 11)
	{
		i = 0;
		UP = 0x80;
	}
}

void go_time_for_cars()
{
	static uint8 i = 0;

	LCD_vidSendCmd(0, 0x01);
	LCD_vidSendCmd(0, 0x80 + i);

	LCD_vidWriteData(0, 'G');
	LCD_vidWriteData(0, 'O');
	LCD_vidWriteData(0, lcdCharGlob[0][0]);

	i++;

	if(i == 13)
	{
		i = 0;
	}
}

void decrement_seven_segment(uint8* first, uint8* second)
{

	if(*second > 0)
	{
		(*second)--;
	}
	else
	{
		if(*first > 0)
		{
			(*first)--;
			(*second) = 9;
		}
	}
}
void red_light(uint8 u8FirstSevVal, uint8 u8SecSevVal)
{

	// Display the values on the seven-segment displays
	SEV_vidWriteNum(0, u8FirstSevVal);
	SEV_vidWriteNum(1, u8SecSevVal);

	// Turn on the red LED
	DIO_enumWritePin(7, 1);

}
void green_light(uint8 u8FirstSevVal, uint8 u8SecSevVal)
{
    // Display the values on the seven-segment displays
    SEV_vidWriteNum(0, u8FirstSevVal);
    SEV_vidWriteNum(1, u8SecSevVal);

    // Turn on the green LED
    DIO_enumWritePin(15, 1);
}

void yellow_light(uint8 u8FirstSevVal, uint8 u8SecSevVal)
{
    // Display the values on the seven-segment displays
    SEV_vidWriteNum(0, u8FirstSevVal);
    SEV_vidWriteNum(1, u8SecSevVal);

    // Turn on the yellow LED
    DIO_enumWritePin(31, 1);
}
