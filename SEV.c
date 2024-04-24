/*
 * SEV.c
 *
 *  Created on: Apr 1, 2024
 *      Author: Marwan
 */


#include "STD_Types.h"
#include "SEV.h"
#include "BitMath.h"
#include "SEV_priv.h"
#include "SEV_cnfg.h"
#include "DIO.h"

uint8 au8DispVal[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void SEV_vidWriteNum(uint8 u8SevIndxCpy, uint8 u8SevValCpy)
{
	uint8 u8CntrLoc;
	// index in range , value in range
	if ((u8SevIndxCpy < SEV_MAX_NUM) && (u8SevValCpy <= 9) )
	{
		if (SEV_astrConfigSet[u8SevIndxCpy].u8Mode == COM_ANODE)
		{
			// DIO write 7 pins
			// ~au8DispVal[u8SevValCpy]
			// ~au8DispVal  0x66 1100110   GET_BIT(~au8DispVal[u8SevValCpy],0)
			for(u8CntrLoc = 0; u8CntrLoc < 7; ++u8CntrLoc)
			{
				DIO_enumWritePin(SEV_astrConfigSet[u8SevIndxCpy].au8PinCon[u8CntrLoc], GET_BIT(~au8DispVal[u8SevValCpy], u8CntrLoc));

			}
		}

		else
		{
			/* COM CATHODE */

			// DIO write 7 pins
			// ~au8DispVal[u8SevValCpy]
			// ~au8DispVal  0x66 1100110   GET_BIT(~au8DispVal[u8SevValCpy],0)

			for (u8CntrLoc = 0; u8CntrLoc < 7; ++u8CntrLoc)
			{
				DIO_enumWritePin(SEV_astrConfigSet[u8SevIndxCpy].au8PinCon[u8CntrLoc],GET_BIT(~au8DispVal[u8SevValCpy], u8CntrLoc));
			}
		}
	}
}
