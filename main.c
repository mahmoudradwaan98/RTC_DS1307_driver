/*
 * main.c
 *
 *  Created on: Apr 28, 2023
 *      Author: User
 */

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "I2C_Interface.h"
#include "RTC_interface.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "clcd_interface.h"
#include <util/delay.h>


/*To disable an enabled WatchDog Timer , the following procedure must be followed:

1. In the same operation, write a logic one to WDTOE and WDE. A logic one must
be written to WDE even though it is set to one before the disable operation starts.

2. Within the next four clock cycles, write a logic 0 to WDE. This disables the
WatchDog.
*/



void main(void){

	PORT_voidInit();
	LCD_voidInit();
	RTC_voidInit();

//	MCAL_DIO_u8SetPinDirection(DIO_U8PORTA,DIO_U8PIN7,DIO_U8PIN_OUTPUT);

	I2C_voidMasterInit(SCL_100KHZ);

//	// hr , min , sec , time format 12 / 24 , time mode AM , PM
//	time_t time1 = {1,8,25,time_format_12,AM};
//	// year , month , date , day
//	year_t year1 = {99,3,5,2};
//
//	RTC_voidSetTime(&time1);
//
//	RTC_SetDate(&year1);

	time_t time_now;

	year_t year_now;

	time_now = RTC_GetTime();

	year_now = RTC_GetDate();



	while(1){

	}
}




