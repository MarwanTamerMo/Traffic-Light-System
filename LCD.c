/*
 * LCD.c
 *
 *  Created on: Apr 8, 2024
 *      Author: Marwan
 */


#include "BitMath.h"
#include "STD_Types.h"
#include <util/delay.h>

#include "DIO.h"

#include "LCD.h"
#include "LCD_cnfg.h"
#include "LCD_priv.h"

static void ModeHelper(uint8 u8LcdIndxCpy, uint8 u8DataorCmdCpy);
static void WriteHelper(uint8 u8StartPin, uint8 u8lcdIndxCpy, uint8 u8DataorCmdCpy);

uint8 LCD_u84BitModFlg = 0;

void LCD_vidInit()
{
	uint8 u8CmdLoc;
	uint8 u8CntrLoc = 0;

	for(u8CntrLoc = 0 ;u8CntrLoc< LCD_MAX_NUM ; u8CntrLoc++)
	{
		if (LCD_astrConfigSet[u8CntrLoc].strLcdExtCnfg.Concmode == LCD_8BIT_MODE)
		{
			_delay_ms(30);

			u8CmdLoc = 0b00110000|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.N_Line)<<3|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.Font)<<2;
			LCD_vidSendCmd(u8CntrLoc , u8CmdLoc);

			_delay_ms(1);

			u8CmdLoc = 0b00001000|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.Display)<<2|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.Cursor)<<1 |
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.C_Blink);
			LCD_vidSendCmd(u8CntrLoc , u8CmdLoc);

			_delay_ms(1);

			LCD_vidSendCmd(u8CntrLoc , 0x01);

			_delay_ms(2);

			u8CmdLoc = 0b00000100|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.EntryMode)<<1|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.Shift);
			LCD_vidSendCmd(u8CntrLoc , u8CmdLoc);

			_delay_ms(1);

		}
		else
		{
			LCD_vidSendCmd(u8CntrLoc , 0b00100010);
			LCD_u84BitModFlg = 1;
			// send 0bNF00
			u8CmdLoc = 0b00000000|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.N_Line)<<7|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.Font)<<6;
			LCD_vidSendCmd(u8CntrLoc , u8CmdLoc);
			LCD_u84BitModFlg = 0;
			_delay_ms(1);

			u8CmdLoc = 0b00001000|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.Display)<<2|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.Cursor)<<1 |
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.C_Blink);
			LCD_vidSendCmd(u8CntrLoc , u8CmdLoc);

			_delay_ms(1);

			LCD_vidSendCmd(u8CntrLoc , 0x01);

			_delay_ms(2);

			u8CmdLoc = 0b00000100|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.EntryMode)<<1|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCnfg.Shift);
			LCD_vidSendCmd(u8CntrLoc , u8CmdLoc);

			_delay_ms(1);

		}

	}

}

void LCD_vidSendCmd(uint8 u8LcdIndxCpy, uint8 u8CmdCpy)
{
	DIO_enumWritePin(LCD_astrConfigSet[u8LcdIndxCpy].strLcdExtCnfg.Rs, 0);
	ModeHelper(u8LcdIndxCpy, u8CmdCpy);
}

void LCD_vidWriteData(uint8 u8LcdIndxCpy, uint8 u8DataCpy)
{
	DIO_enumWritePin(LCD_astrConfigSet[u8LcdIndxCpy].strLcdExtCnfg.Rs, 1);
	ModeHelper(u8LcdIndxCpy, u8DataCpy);
}

static void ModeHelper (uint8 u8LcdIndxCpy, uint8 u8DataorCmdCpy)
{

	if(LCD_astrConfigSet[u8LcdIndxCpy].strLcdExtCnfg.Concmode == LCD_8BIT_MODE)
	{
		WriteHelper(_8BIT_START_PIN, u8LcdIndxCpy, u8DataorCmdCpy);
	}
	else
	{
		DIO_enumWritePin(LCD_astrConfigSet[u8LcdIndxCpy].strLcdExtCnfg.Rw,0);

		if(LCD_u84BitModFlg == 1)
		{
			WriteHelper(_4BIT_START_PIN, u8LcdIndxCpy, u8DataorCmdCpy);
		}
		else
		{
			WriteHelper(_4BIT_START_PIN, u8LcdIndxCpy, u8DataorCmdCpy);

			u8DataorCmdCpy = u8DataorCmdCpy << 4;

			WriteHelper(_4BIT_START_PIN, u8LcdIndxCpy, u8DataorCmdCpy);
		}

	}
}

static void WriteHelper(uint8 u8StartPin, uint8 u8lcdIndxCpy, uint8 u8DataorCmdCpy)
{
			uint8 u8PinNumLoc;

			DIO_enumWritePin(LCD_astrConfigSet[u8lcdIndxCpy].strLcdExtCnfg.Rw, 0);
			DIO_enumWritePin(LCD_astrConfigSet[u8lcdIndxCpy].strLcdExtCnfg.En, 1);

			for (u8PinNumLoc = u8StartPin; u8PinNumLoc < 8; ++u8PinNumLoc)
			{
				DIO_enumWritePin(LCD_astrConfigSet[u8lcdIndxCpy].strLcdExtCnfg.Databus[u8PinNumLoc],
						GET_BIT(u8DataorCmdCpy, u8PinNumLoc));
			}

			_delay_ms(1);
			DIO_enumWritePin(LCD_astrConfigSet[u8lcdIndxCpy].strLcdExtCnfg.En, 0);
			_delay_ms(1);
}
