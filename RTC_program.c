/*
 * RTC_program->c
 *
 *  Created on: Aug 7, 2023
 *      Author: User
 */

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "I2C_Private.h"
#include "I2C_Interface.h"
#include "DIO_interface.h"
#include "RTC_interface.h"

time_t time_res;
year_t date_res;

/* this function should initialize TWI with the speed required to operate RTC -> */
void RTC_voidInit(void){

	/* enable the oscillator (CH bit = 0) during initial configuration */
	I2C_voidMasterInit(SCL_100KHZ);
}

/* this function should take time in (hours minutes seconds )and if the time is (AM or PM),
   it should configure RTC initial time with it ->*/
void RTC_voidSetTime(time_t* copy_time){

	// algorithm to send data
	u8 sec_res_send = RTC_TimeSecFormat(copy_time->second);
	u8 min_res_send = RTC_TimeMinFormat(copy_time->minute);
	u8 HR_res_send =  RTC_TimeHrFormat(copy_time->hour,copy_time->time_format,copy_time->time_mode);

	/* start sending data */

	I2C_Master_u8StartCondition();

	I2C_Master_u8WriteDataByte_ACK(0xD0);

	I2C_Master_u8WriteDataByte_ACK(0x00);

	I2C_Master_u8WriteDataByte_ACK(sec_res_send);

	I2C_Master_u8WriteDataByte_ACK(min_res_send);

	I2C_Master_u8WriteDataByte_ACK(HR_res_send);

	I2C_Master_u8StopCondition();
}

/* this function should return the time in (hours minutes seconds) and if the time is (AM or PM)-> */
time_t  RTC_GetTime(void){

	/* start Receiving data */

	I2C_Master_u8StartCondition();

	I2C_Master_u8WriteDataByte_ACK(0xD1);

	u8 ptr_time_receive;

	I2C_Master_u8ReadDataByte_ACK(&ptr_time_receive);

	u8 time_sec = ptr_time_receive;

	I2C_Master_u8ReadDataByte_ACK(&ptr_time_receive);

	u8 time_min = ptr_time_receive;

	I2C_Master_u8ReadDataByte_NOTACK(&ptr_time_receive);

	u8 time_HR = ptr_time_receive;

	I2C_Master_u8StopCondition();

	/* Data handling to return time */

	time_res.second = time_sec;

	time_res.minute = time_min;

	time_res.hour = time_HR;

	if( (GET_BIT(time_HR,6) == 1) ){

		time_res.time_format = time_format_12;

		if( (GET_BIT(time_HR,5) == 1) ){

			time_res.time_mode = PM;

		}
		else if( ( GET_BIT(time_HR,5) == 0 ) ) {
			time_res.time_mode = AM;
		}
		else{

			// do nothing , error type
		}
	}

	else if( (GET_BIT(time_HR,6) == 0) ){

		time_res.time_format = time_format_24;
		time_res.time_mode = No_TYPE;
	}

	return time_res;
}

/* this function should take date in (year month day )and should configure RTC with it -> */
void RTC_SetDate(year_t* copy_year){

	/* Data year handling */

   u8 day_res_send = RTC_dayFormat(copy_year->day);

   u8 date_res_send = RTC_dateFormat(copy_year->date);

   u8 month_res_send = RTC_MonthFormat(copy_year->month);

   u8 year_res_send = RTC_yearFormat(copy_year->year);


   /* start sending data */

	I2C_Master_u8StartCondition();

	I2C_Master_u8WriteDataByte_ACK(0xD0);

	I2C_Master_u8WriteDataByte_ACK(0x03);

	I2C_Master_u8WriteDataByte_ACK(day_res_send);

	I2C_Master_u8WriteDataByte_ACK(date_res_send);

	I2C_Master_u8WriteDataByte_ACK(month_res_send);

	I2C_Master_u8WriteDataByte_ACK(year_res_send);

	I2C_Master_u8StopCondition();


}

/* this function should return the data in (year month day)-> */
year_t  RTC_GetDate(void){


	/* start Receiving data */

	I2C_Master_u8StartCondition();

	I2C_Master_u8WriteDataByte_ACK(0xD1);

	u8 ptr_date_receive;

	I2C_Master_u8ReadDataByte_ACK(&ptr_date_receive);

	u8 date_day = ptr_date_receive;

	I2C_Master_u8ReadDataByte_ACK(&ptr_date_receive);

	u8 date = ptr_date_receive;

	I2C_Master_u8ReadDataByte_ACK(&ptr_date_receive);

	u8 date_month = ptr_date_receive;

	I2C_Master_u8ReadDataByte_NOTACK(&ptr_date_receive);

	u8 date_year = ptr_date_receive;

	I2C_Master_u8StopCondition();

	/* Data handling to return date */

	date_res.day = date_day;
	date_res.date = date;
	date_res.month = date_month;
	date_res.year = date_year;

	return date_res;

}

u8 RTC_TimeSecFormat(u8 copy_time_sec){

	u8 local_sec_time = 0;

	CLR_BIT(local_sec_time,7);

	u8 Sec_format[2];

	u8 temp = copy_time_sec;

	for(u8 i=0;i<2;i++){

		Sec_format[i] = temp % 10;

		temp = temp / 10;

	}
//
//		 u8 mask1 = 0b00001111;
//
//		 local_sec_time |= (mask1 & sec_format[0] );
//
//		 u8 mask2 = 0b01110000;
//
//		 local_sec_time |= (mask2 & sec_format[1]);

	local_sec_time |=  Sec_format[0]  | ( Sec_format[1]<<4);

	return local_sec_time;


}

u8 RTC_TimeMinFormat(u8 copy_time_min){

	u8 local_Min_time = 0;

	CLR_BIT(local_Min_time,7);

	u8 Min_format[2];

	u8 temp = copy_time_min;

	for(u8 i=0;i<2;i++){

		Min_format[i] = temp % 10;

		temp = temp / 10;

	}

	//	 u8 mask1 = 0b00001111;
	//
	//	 local_Min_time |= (mask1 & Min_format[0] );
	//
	//	 u8 mask2 = 0b01110000;
	//
	//	 local_Min_time |= (mask2 & Min_format[1]);

	local_Min_time = ( Min_format[0] | ( Min_format[1] <<4) );

	return local_Min_time;

}

u8 RTC_TimeHrFormat(u8 copy_time_HR , u8 copy_time_format, u8 copy_time_mode){

	u8 local_HR_time =0;

	CLR_BIT(local_HR_time,7);

	u8 HR_format[2];

	u8 temp = copy_time_HR;

	for(u8 i=0;i<2;i++){

		HR_format[i] = temp % 10;

		temp = temp / 10;
	}

	switch(copy_time_format){

	case time_format_12:

		SET_BIT(local_HR_time,6);

		switch(copy_time_mode){
		case AM:
			CLR_BIT(local_HR_time,5);

			break;
		case PM:
			SET_BIT(local_HR_time,5);
			break;
		}

		break;

		case time_format_24:

			CLR_BIT(local_HR_time,6);
			break;

	}

	local_HR_time |= ( HR_format[0] | ( HR_format[1] <<4) );

	return local_HR_time;

}

u8 RTC_dateFormat(u8 copy_year_date){

	u8 local_date =0;

	u8 date_format[2];

	u8 temp = copy_year_date;

	for(u8 i=0;i<2;i++){

		date_format[i] = temp % 10;

		temp = temp / 10;

	}

	local_date = date_format[0] | (date_format[1]<<4);

	return local_date;
}

u8 RTC_dayFormat(u8 copy_year_day){

	u8 local_day = copy_year_day;

	return local_day;
}

u8 RTC_MonthFormat(u8 copy_year_month){

	u8 month_format[2];

	u8 temp = copy_year_month;

	for(u8 i=0;i<2;i++){

		month_format[i] = temp % 10;

		temp = temp / 10;

	}

	u8 local_month = month_format[0] | (month_format[1] << 4);

	return local_month;
}

u8 RTC_yearFormat(u8 copy_year){

	u8 year_format[2];

	u8 temp = copy_year;

	for(u8 i=0;i<2;i++){

		year_format[i] = temp % 10;

		temp = temp / 10;

	}

	u8 local_year = year_format[0] | (year_format[1] << 4);

	return local_year;
}


