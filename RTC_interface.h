/*
 * RTC_interface.h
 *
 *  Created on: Aug 7, 2023
 *      Author: User
 */

#ifndef RTC_INTERFACE_H_
#define RTC_INTERFACE_H_

	#define RTC_Slave_Address_W   0b11010000
	#define RTC_Slave_Address_R   0b11010001

	#define RTC_address_0       0
	#define RTC_address_1       1
	#define RTC_address_2       2
	#define RTC_address_3       3
	#define RTC_address_4       4
	#define RTC_address_5       5
	#define RTC_address_6       6
	#define RTC_address_7       7

	typedef enum{
		time_format_24 = 0,
		time_format_12 = 1
	}time_format_t;

	typedef enum{
		AM =0,
		PM =1,
		No_TYPE =2
	}time_mode_t;

	typedef struct{
		u8 hour;
		u8 minute;
		u8 second;
		time_format_t time_format;
		time_mode_t time_mode;

	}time_t;

	typedef struct{
		u8 year;
		u8 month;
		u8 date;
		u8 day;
	}year_t;

	typedef struct{
		u8 sec_res;
		u8 min_res;
		u8 HR_res;
	}time_res_t;

	typedef struct{
		u8 day_res;
		u8 date_res;
		u8 month_res;
		u8 year_res;
	}year_res_t;


	/* this function should initialize TWI with the speed required to operate RTC . */
	void RTC_voidInit(void);

	/* this function should take time in (hours minutes seconds )and if the time is (AM or PM),
	   it should configure RTC initial time with it .*/
	void RTC_voidSetTime(time_t* copy_time);

	/* this function should return the time in (hours minutes seconds) and if the time is (AM or PM). */
	time_t  RTC_GetTime(void);

	/* this function should take date in (year month day )and should configure RTC with it . */
	void RTC_SetDate(year_t* copy_year);

	/* this function should return the data in (year month day). */
	year_t  RTC_GetDate(void);

	u8 RTC_TimeSecFormat(u8 copy_time_sec);

	u8 RTC_TimeMinFormat(u8 copy_time_min);

	u8 RTC_TimeHrFormat(u8 copy_time_HR , u8 copy_time_format, u8 copy_time_mode);

	u8 RTC_dateFormat(u8 copy_year_date);

	u8 RTC_dayFormat(u8 copy_year_day);

	u8 RTC_MonthFormat(u8 copy_year_month);

	u8 RTC_yearFormat(u8 copy_year);

#endif /* RTC_INTERFACE_H_ */
