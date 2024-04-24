/*
 * LCD_priv.h
 *
 *  Created on: Apr 8, 2024
 *      Author: Marwan
 */

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

#define LCD_ONE_LINE 0
#define LCD_TWO_LINE 1

#define LCD_FONT_5X7   0
#define LCD_FONT_5X11  1

#define LCD_DISPLAY_OFF  0
#define LCD_DISPLAY_ON   1


#define LCD_CURSOR_OFF  0
#define LCD_CURSOR_ON   1

#define LCD_CURSOR_BLINK_OFF  0
#define LCD_CURSOR_BLINK_ON   1

#define LCD_RTL   0
#define LCD_LTR   1

#define LCD_DISPLAY_SHIFT_OFF  0
#define LCD_DISPLAY_SHIFT_ON   1

#define LCD_4BIT_MODE   0
#define LCD_8BIT_MODE   1

#define _4BIT_START_PIN 4
#define _8BIT_START_PIN 0 // For WriteHelper Function in .c File

typedef struct
{
	uint8 N_Line     : 1 ;
	uint8 Font       : 1 ;
	uint8 Display    : 1 ;
	uint8 Cursor     : 1 ;
	uint8 C_Blink    : 1 ;
	uint8 EntryMode  : 1 ;
	uint8 Shift      : 1 ;

}tstrLcdIntCnfg;

typedef struct
{
	uint8 Concmode;
	uint8 Rs;
	uint8 Rw;
	uint8 En;
	uint8 Databus[8];

}tstrLcdExtCnfg;

typedef struct
{
	tstrLcdExtCnfg strLcdExtCnfg;
	tstrLcdIntCnfg strLcdIntCnfg;

}tstrLcdCnfg;

extern const tstrLcdCnfg LCD_astrConfigSet[LCD_MAX_NUM];

#endif /* LCD_PRIV_H_ */
