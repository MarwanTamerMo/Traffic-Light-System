/*
 * DIO_priv.h
 *
 *  Created on: Mar 31, 2024
 *      Author: marwa
 */
#include "STD_Types.h"

#ifndef DIO_PRIV_H_
#define DIO_PRIV_H_

#define OUTPUT 1
#define INPUT 0

/*ODRA === PORTA , IDRA === PINA*/

#define DDRA *((volatile uint8_t*)0x3A)
#define ODRA *((volatile uint8_t*)0x3B)
#define IDRA *((volatile uint8_t*)0x39)

#define DDRB *((volatile uint8_t*)0x37)
#define ODRB *((volatile uint8_t*)0x38)
#define IDRB *((volatile uint8_t*)0x36)

#define DDRC *((volatile uint8_t*)0x34)
#define ODRC *((volatile uint8_t*)0x35)
#define IDRC *((volatile uint8_t*)0x33)

#define DDRD *((volatile uint8_t*)0x31)
#define ODRD *((volatile uint8_t*)0x32)
#define IDRD *((volatile uint8_t*)0x30)

#define Conc(b7,b6,b5,b4,b3,b2,b1,b0) Conc_help(b7,b6,b5,b4,b3,b2,b1,b0)
/*
 * Conc_help is made because concatenation is compiler dependent can give priority
 for replacing firstly before concatenating or vice versa so we make sure by adding
 Conc_help() that we concatenate first then replace the parameters with the actual values
 */
#define Conc_help(b7,b6,b5,b4,b3,b2,b1,b0) 0b##b7##b6##b5##b4##b3##b2##b1##b0


#endif /* DIO_PRIV_H_ */
