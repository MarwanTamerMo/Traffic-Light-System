/*
 * LCD.h
 *
 *  Created on: Apr 8, 2024
 *      Author: Marwan
 */

#ifndef LCD_H_
#define LCD_H_

void LCD_vidInit(void);
void LCD_vidSendCmd(uint8 u8LcdIndxCpy, uint8 u8CmdCpy);
void LCD_vidWriteData(uint8 u8LcdIndxCPy, uint8 u8DataCpy);

#endif /* LCD_H_ */
