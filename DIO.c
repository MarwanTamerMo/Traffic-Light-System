/*
 * DIO.c
 *
 *  Created on: Mar 31, 2024
 *      Author: Marwan
 */


#include "STD_Types.h"
#include "BitMath.h"
#include <stdio.h>

#include "DIO.h"
#include "DIO_cnfg.h"
#include "DIO_priv.h"


void DIO_vidInit(void)
{

  DDRA = Conc(DIO_DIR_PIN_7,DIO_DIR_PIN_6,DIO_DIR_PIN_5,DIO_DIR_PIN_4,DIO_DIR_PIN_3,DIO_DIR_PIN_2,DIO_DIR_PIN_1,DIO_DIR_PIN_0);
  DDRB = Conc(DIO_DIR_PIN_15,DIO_DIR_PIN_14,DIO_DIR_PIN_13,DIO_DIR_PIN_12,DIO_DIR_PIN_11,DIO_DIR_PIN_10,DIO_DIR_PIN_9,DIO_DIR_PIN_8);
  DDRC = Conc(DIO_DIR_PIN_23,DIO_DIR_PIN_22,DIO_DIR_PIN_21,DIO_DIR_PIN_20,DIO_DIR_PIN_19,DIO_DIR_PIN_18,DIO_DIR_PIN_17,DIO_DIR_PIN_16);
  DDRD = Conc(DIO_DIR_PIN_31,DIO_DIR_PIN_30,DIO_DIR_PIN_29,DIO_DIR_PIN_28,DIO_DIR_PIN_27,DIO_DIR_PIN_26,DIO_DIR_PIN_25,DIO_DIR_PIN_24);


}
/********************************************************/
/*u8PinNumCpy: 0--7 (A)  8--15 (B) 16 --23 (C)24--31 (D)*/
/********************************************************/
tenuErrorStatus DIO_enumWritePin(uint8 u8PinNumCpy , uint8 u8PinValCpy)
{
	tenuErrorStatus  enuErrorLoc = E_OK ;

	if (u8PinNumCpy>=0 && u8PinNumCpy<=7)
	{
		// ODRA === PORTA  1101 0000
		switch(u8PinValCpy)
		{
			case 0:
			   CLEAR_BIT(ODRA , u8PinNumCpy);
			break ;

			case 1:
			   SET_BIT(ODRA , u8PinNumCpy);
			break ;

			default :
			enuErrorLoc = E_NOK_PARM_OUT_OF_RANGE ;
			break ;
		}
	}
	else if (u8PinNumCpy>=8 && u8PinNumCpy<=15)
	{
		// ODRB === PORTB
		u8PinNumCpy = u8PinNumCpy % 8;

		switch(u8PinValCpy)
		{
			case 0:
			   CLEAR_BIT(ODRB , u8PinNumCpy);
			break ;

			case 1:
			   SET_BIT(ODRB , u8PinNumCpy);
			break ;

			default :
			enuErrorLoc = E_NOK_PARM_OUT_OF_RANGE ;
			break ;
		}

	}
	else if (u8PinNumCpy>=16 && u8PinNumCpy<=23)
	{
		// ODRC === PORTC
		u8PinNumCpy = u8PinNumCpy %8 ;

		switch(u8PinValCpy)
		{
			case 0:
			   CLEAR_BIT(ODRC , u8PinNumCpy);
			break ;

			case 1:
			   SET_BIT(ODRC , u8PinNumCpy);
			break ;

			default :
			enuErrorLoc = E_NOK_PARM_OUT_OF_RANGE ;
			break ;
		}

	}
	else if (u8PinNumCpy>=24 && u8PinNumCpy<=31)
	{
		// ODRD === PORTD
		u8PinNumCpy = u8PinNumCpy % 8 ;

		switch(u8PinValCpy)
		{
			case 0:
			   CLEAR_BIT(ODRD , u8PinNumCpy);
			break ;

			case 1:
			   SET_BIT(ODRD , u8PinNumCpy);
			break ;

			default :
			enuErrorLoc = E_NOK_PARM_OUT_OF_RANGE ;
			break ;
		}

	}
	else
	{
		enuErrorLoc = E_NOK_PARM_OUT_OF_RANGE;
	}

	return enuErrorLoc ;
}

tenuErrorStatus DIO_enumReadPin(uint8 u8PinNumCpy , uint8 * pu8PinValCpy)
{
	tenuErrorStatus enuErrorLoc = E_OK;

	if (u8PinNumCpy>=0 && u8PinNumCpy<=7)
	{
		// IDRA
		*pu8PinValCpy = GET_BIT(IDRA , u8PinNumCpy);
	}
	else if (u8PinNumCpy>=8 && u8PinNumCpy<=15)
	{
		// IDRB
		u8PinNumCpy = u8PinNumCpy % 8 ;
		*pu8PinValCpy = GET_BIT(IDRB , u8PinNumCpy);
	}
	else if (u8PinNumCpy>=16 && u8PinNumCpy<=23)
	{
		// IDRC
		u8PinNumCpy = u8PinNumCpy % 8 ;
		*pu8PinValCpy = GET_BIT(IDRC , u8PinNumCpy);
	}
	else if (u8PinNumCpy>=24 && u8PinNumCpy<=31)
	{
		// IDRD
		u8PinNumCpy = u8PinNumCpy % 8 ;
		*pu8PinValCpy = GET_BIT(IDRD , u8PinNumCpy);
	}
	else
	{
		enuErrorLoc = E_NOK_PARM_OUT_OF_RANGE ;
	}

	return enuErrorLoc ;
}

tenuErrorStatus DIO_enuActivePullUp(uint8 u8pinNumCpy, uint8 u8ResStatusCpy)
{
	return DIO_enumWritePin(u8pinNumCpy, u8ResStatusCpy);
}
