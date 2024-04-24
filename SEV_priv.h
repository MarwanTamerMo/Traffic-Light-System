/*
 * SEV_priv.h
 *
 *  Created on: Apr 1, 2024
 *      Author: Marwan
 */

#include "SEV_cnfg.h"

#ifndef SEV_PRIV_H_
#define SEV_PRIV_H_

#define COM_ANODE 1
#define COM_CATHODE 0

typedef struct
{
	uint8 u8Mode;
	uint8 au8PinCon[7];

}tstrSevCnfg;

extern tstrSevCnfg SEV_astrConfigSet[SEV_MAX_NUM];

#endif /* SEV_PRIV_H_ */
