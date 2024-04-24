/*
 * SEV_cnf.c
 *
 *  Created on: Apr 1, 2024
 *      Author: Marwan
 */

#include "STD_Types.h"

#include "SEV_cnfg.h"
#include "SEV_priv.h"

tstrSevCnfg SEV_astrConfigSet[SEV_MAX_NUM] =
{
		// All config for SEV index 0
		{
			/*Mode*/
			COM_ANODE,

			/*Pins Connected to the SEV (DIO pin connection)*/
			/* a, b,  c,  d,  e,  f,  g*/
			{ 8, 9, 10, 11, 12, 13, 14 }
		},


		// All config for SEV index 1
		{

		/*Mode*/
		COM_ANODE,

		/*Pins Connected to the SEV (DIO pin connection)*/
		{ 0, 1, 2, 3, 4, 5, 6 }

		}
};
