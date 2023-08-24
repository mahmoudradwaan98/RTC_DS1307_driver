/*
 * LCD_Program.c
 *
 * Created: 7/22/2023 6:51:19 PM
 *  Author: Rizk
 */

#include "STD_TYPES.h"
#include "BIT_MATHS.h"

#include <util/delay.h>

#include "DIO_interface.h"

#include "clcd_config.h"
#include "clcd_interface.h"
#include "clcd_private.h"
#include "CLCD_ExtraCahr.h"



void LCD_voidInit(void)
{
	MCAL_DIO_u8SetPinDirection(RS_PORT,RS_PIN,DIO_U8PIN_OUTPUT);
	MCAL_DIO_u8SetPinDirection(E_PORT,E_PIN,DIO_U8PIN_OUTPUT);

	MCAL_DIO_u8SetPinDirection(D4_PORT,D4_PIN,DIO_U8PIN_OUTPUT);
	MCAL_DIO_u8SetPinDirection(D5_PORT,D5_PIN,DIO_U8PIN_OUTPUT);
	MCAL_DIO_u8SetPinDirection(D6_PORT,D6_PIN,DIO_U8PIN_OUTPUT);
	MCAL_DIO_u8SetPinDirection(D7_PORT,D7_PIN,DIO_U8PIN_OUTPUT);


//	_delay_ms(35);
//	/* 2 line 5*7 font*/
//	Lcd_SendCmd(0x28);
//	_delay_ms(1);
//
//	/*Display on cursor off*/
//	Lcd_SendCmd(0x0C);
//	_delay_ms(1);
//
//	/*Clear Display */
//	Lcd_SendCmd(0x01);
//	_delay_ms(2);
//
//	/*Entry Mode  Auto increment */
//	Lcd_SendCmd(0x06);
	_delay_ms(15);

	Lcd_SendCmd(0x03);
	_delay_ms(5);
	Lcd_SendCmd(0x03);
	_delay_us(100);
	Lcd_SendCmd(0x03);
	Lcd_SendCmd(0x02);
	Lcd_SendCmd(0x28);
	Lcd_SendCmd(0x0C);
	Lcd_Goto_Row_Column(0, 0);
	Lcd_SendCmd(0x01);

}

void Lcd_SendCmd(u8 Command)

{

	/* command mode */
	MCAL_DIO_u8SetPinValue(RS_PORT,RS_PIN,DIO_U8PIN_LOW);


  /*      Send Command         */
		MCAL_DIO_u8SetPinValue(D7_PORT,D7_PIN,GET_BIT(Command,7));
		MCAL_DIO_u8SetPinValue(D6_PORT,D6_PIN,GET_BIT(Command,6));
		MCAL_DIO_u8SetPinValue(D5_PORT,D5_PIN,GET_BIT(Command,5));
		MCAL_DIO_u8SetPinValue(D4_PORT,D4_PIN,GET_BIT(Command,4));



		/*   Latching   */
		Enable_Pulse();

		MCAL_DIO_u8SetPinValue(D7_PORT,D7_PIN,GET_BIT(Command,3));
		MCAL_DIO_u8SetPinValue(D6_PORT,D6_PIN,GET_BIT(Command,2));
		MCAL_DIO_u8SetPinValue(D5_PORT,D5_PIN,GET_BIT(Command,1));
		MCAL_DIO_u8SetPinValue(D4_PORT,D4_PIN,GET_BIT(Command,0));

  /*   Latching   */
  Enable_Pulse();


}

void LCD_voidSenddata(u8 data)
{
	MCAL_DIO_u8SetPinValue(RS_PORT,RS_PIN,DIO_U8PIN_HIGH);


	/*      Send Command         */

	MCAL_DIO_u8SetPinValue(D4_PORT,D4_PIN,GET_BIT(data,4));
	MCAL_DIO_u8SetPinValue(D5_PORT,D5_PIN,GET_BIT(data,5));
	MCAL_DIO_u8SetPinValue(D6_PORT,D6_PIN,GET_BIT(data,6));
	MCAL_DIO_u8SetPinValue(D7_PORT,D7_PIN,GET_BIT(data,7));



	/*   Latching   */
	Enable_Pulse();




		MCAL_DIO_u8SetPinValue(D4_PORT,D4_PIN,GET_BIT(data,0));
		MCAL_DIO_u8SetPinValue(D5_PORT,D5_PIN,GET_BIT(data,1));
		MCAL_DIO_u8SetPinValue(D6_PORT,D6_PIN,GET_BIT(data,2));
		MCAL_DIO_u8SetPinValue(D7_PORT,D7_PIN,GET_BIT(data,3));
	/*   Latching   */
	Enable_Pulse();


}



void Enable_Pulse(void)
{
		MCAL_DIO_u8SetPinValue(E_PORT,E_PIN,DIO_U8PIN_HIGH);
		_delay_us(1);
		MCAL_DIO_u8SetPinValue(E_PORT,E_PIN,DIO_U8PIN_LOW);
		_delay_ms(2);
}



void Lcd_DisplayStr(u8* str)
{
	while (*str != '\0')
	{
		Lcd_DisplayChr(*str);
		str++;
	}
}

void Lcd_Goto_Row_Column(u8 row, u8 col)
{
	switch (row)
	{
		case 0:
		Lcd_SendCmd(0x80+col);
		break;

		case 1:
		Lcd_SendCmd(0xC0+col);
		break;
	}
}

void Lcd_DisplayChr(u8 chr)
{
	LCD_voidSenddata(chr);
}


void HLCD_voidClearLCD(void)
{
	/*send Display clear instruction*/
	Lcd_SendCmd(_LCD_CLEAR);

	}/*end of HLCD_voidClearLCD()*/


void HLCD_voidReturnHome(void)
{
	 /*send Return home instruction*/
	 Lcd_SendCmd(_LCD_RETURN_HOME);

}

int atoi(u8 str) {

    int result = 0;
   // Check if the character is a digit between 0 and 9
   if (str >= '0' && str <= '9')
   {

       // Update the result by adding the digit and adjusting its position
       result += (str - '0');

   }

    return result;
}


void Lcd_Displaynum(u16 number)
{
	int value = atoi(number);

	int remainder;

	while(number!=0){

		 remainder = number % 10;
		 Lcd_DisplayChr(remainder);
		 number /= 10;
	}


}















///******************************************************************************/
///*****************************************************************************/
///****************    Author    : Mahmoud Radwan       ***********************/
///****************    Layer     : HAL                  **********************/
///****************    SWC       : LCD                  *********************/
///****************    version   : 1.0                  ********************/
///************************************************************************/
///***********************************************************************/
//#include "STD_TYPES.h"
//#include <util/delay.h>
//
//#include "DIO_interface.h"
//
//#include "clcd_config.h"
//#include "clcd_interface.h"
//#include "clcd_private.h"
//#include "CLCD_ExtraCahr.h"
///***************************************************************************************/
///* Description : Interface to send the configuration commands to the LCD Driver         */
///* Input       : Command number                                                         */
///* Output      : Nothing                                                                */
///***************************************************************************************/
//
// void CLCD_voidSendCommand(u8 copy_u8command){
//
//
//	  /* set RS pin to low to send command */
//	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_RS_PIN, DIO_U8PIN_LOW );
//
//	  /* set R/W pin to low to write command */
//	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_RW_PIN,  DIO_U8PIN_LOW);
//
//	  /* send command through data port */
//	  DIO_u8SetPortValue(CLCD_DATA_PORT,copy_u8command);
//
//
//	  /* set Enable PIN for period of time */
//	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_E_PIN,DIO_U8PIN_HIGH);
//	  _delay_ms(2);
//	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_E_PIN,DIO_U8PIN_LOW);
//
//  }
//
//  void CLCD_voidSendData(u8 copy_u8data){
//
//	  /* set RS pin to high to send data */
//	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_RS_PIN, DIO_U8PIN_HIGH );
//
//	  /* set R/W pin to low to write data */
//	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_RW_PIN,  DIO_U8PIN_LOW);
//
//	  /* send data to data port */
//	  DIO_u8SetPortValue(CLCD_DATA_PORT,copy_u8data);
//
//
//	  /* set Enable PIN for period of time  */
//	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_E_PIN,DIO_U8PIN_HIGH);
//	  _delay_ms(2);
//	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_E_PIN,DIO_U8PIN_LOW);
//
//  }
//
//
//  /***************************************************************************************/
//  /* Description : Apply initialization sequence for LCD module                           */
//  /* Input       : Nothing                                                                */
//  /* Output      : Nothing                                                                */
//  /***************************************************************************************/
//
//  void CLCD_VoidINIT(void)
//  {
//  	/* Delay 30ms to ensure the initialization of the LCD driver */
//  	_delay_ms(30);
//
//  	/* Return Home  */
//  	CLCD_voidSendCommand(lcd_Home);
//  	_delay_ms(15);
//
//  	/* Function Set  */
//  	/* function send command : n 2 lines (1) , font size 5*8 (0) from data sheet */
//  	CLCD_voidSendCommand(lcd_FunctionSet8bit);
//  	_delay_ms(1);
//
//  	/* Display ON OFF Control */
//  	  /* function send command : display on/off control 00001DCB
//  	   * D : display screen enable 1
//  	   * C : cursor enable 1
//  	   * B : cursor blink enable 1
//  	   *  */
//  	CLCD_voidSendCommand(lcd_DisplayOn);
//  	_delay_ms(1);
//
//  	/* Clear Display */
//  	CLCD_voidSendCommand(lcd_Clear);
//  	_delay_ms(15);
//
//  	/* Entry Mode Set  */
//  	CLCD_voidSendCommand(lcd_EntryMode);
//  	_delay_ms(2);
//
//  }
//
//  /***************************************************************************************/
//  /* Description! Interface to write character on LCD screen                             */
//  /* Input      ! Data to send                                                           */
//  /* Output     ! Nothing                                                                */
//  /***************************************************************************************/
//  void CLCD_vidWriteChar(u8 u8DataCpy)
//  {
//  	/* Set RS to HIG */
//	  DIO_u8SetPinValue(CLCD_CONTRL_PORT, CLCD_RS_PIN, DIO_U8PIN_HIGH);
//
//  	/* Set R/W to LOW */
//	  DIO_u8SetPinValue(CLCD_CONTRL_PORT, CLCD_RW_PIN, DIO_U8PIN_LOW);
//
//  	/* Set E to HIGH */
//	  DIO_u8SetPinValue(CLCD_CONTRL_PORT, CLCD_E_PIN, DIO_U8PIN_HIGH);
//
//  	/* Load Command on Data bus */
//	  DIO_u8SetPortValue(CLCD_DATA_PORT, u8DataCpy);
//
//  	/* Set E to LOW */
//	  DIO_u8SetPinValue(CLCD_CONTRL_PORT, CLCD_E_PIN, DIO_U8PIN_LOW);
//
//  	/* Wait for E to settle */
//  	_delay_ms(5);
//
//  	/* Set E to HIGH */
//  	DIO_u8SetPinValue(CLCD_CONTRL_PORT, CLCD_E_PIN, DIO_U8PIN_HIGH);
//
//  	/* Delay to let the LCD Display the character */
//  	_delay_ms(10);
//
//  }
//
//  /***************************************************************************************/
//  /* Description : Interface to write string on LCD screen                                */
//  /* Input       : Pointer to the string                                                  */
//  /* Output      : Nothing                                                                */
//  /***************************************************************************************/
//  void LCD_vidWriteString (u8* pu8StringCpy, u8 u8Index)
//  {
//
//      /* Local loop index */
//	  //    u8 u8Index = 0;
//  	u8 iteration=0;
//  	//	while (pu8StringCpy[u8Index] != '\0')
//  	for (iteration=0; iteration<u8Index ; iteration++)
//  	{
//
//  		/* Write Character on LCD */
//  		CLCD_vidWriteChar(pu8StringCpy[iteration]);
//
//  		/* Increment local loop index */
//  		//  		u8Index++;
//
//  		/* Delay to let the LCD show the character */
//  		_delay_ms(2);
//  	}
//
//  }
//
//  /***************************************************************************************/
//  /* Description : Interface to start the writing process at certain digit in the LCD     */
//  /* Input       : Y = Row position , X = Column position                                 */
//  /* Output      : Nothing                                                                */
//  /***************************************************************************************/
//  void Gotoxy (u8 Y,u8 X)
//  {
//  	if (X>0 && X<=16)
//  	{
//  	    switch(Y)
//  	    {
//  		    case 1:
//  		    	CLCD_voidSendCommand(X+127);
//  		    break;
//  		    case 2:
//  		    	CLCD_voidSendCommand(X+191);
//  		    break;
//  		    default:
//  		    break;
//  	    }
//  	}
//  }
//
//  /***************************************************************************************/
//  /* Description : Interface to write extra characters saved in the CGRAM                 */
//  /* Input       : Y = Row position , X = Column position                                 */
//  /* Output      : Nothing                                                                */
//  /***************************************************************************************/
//  void LCD_vidWriteExtraChar (u8 Y,u8 X)
//  {
//      u8 iteration1,iteration2;
//
//      /*DDRAM-->CGRAM*/
//
//      CLCD_voidSendCommand(64);
//
//  	for(iteration1=0 ; iteration1<64 ; iteration1++)
//  	{
//  		CLCD_vidWriteChar(ExtraChar[iteration1]);
//  	}
//
//  	/* CGRAM --> DDRAM */
//
//  	CLCD_voidSendCommand(128);
//
//  	Gotoxy(Y,X);
//
//  	/* First eight character which saved at CGRAM */
//
//  	for (iteration2=0; iteration2<=7 ; iteration2++)
//  	{
//  		/* Write bytes of DDRAM */
//  		CLCD_vidWriteChar(iteration2);
//
//  		_delay_ms(5);
//  	}
//  }


