/*
 * LCD_cnf.h
 *
 * Created: 7/22/2023 6:53:12 PM
 *  Author: Rizk
 */


#ifndef LCD_CNF_H_
#define LCD_CNF_H_



#define RS_PORT  DIO_U8PORTA
#define RS_PIN   DIO_U8PIN3


#define E_PORT  DIO_U8PORTA
#define E_PIN   DIO_U8PIN2


#define D4_PORT  DIO_U8PORTB
#define D4_PIN   DIO_U8PIN0


#define D5_PORT  DIO_U8PORTB
#define D5_PIN   DIO_U8PIN1


#define D6_PORT  DIO_U8PORTB
#define D6_PIN   DIO_U8PIN2


#define D7_PORT  DIO_U8PORTB
#define D7_PIN   DIO_U8PIN4



#endif /* LCD_CNF_H_ */


///******************************************************************************/
///*****************************************************************************/
///****************    Author    : Mahmoud Radwan       ***********************/
///****************    Layer     : HAL                  **********************/
///****************    SWC       : LCD                  *********************/
///****************    version   : 1.0                  ********************/
///************************************************************************/
///***********************************************************************/
//
///*  preprocessor file guard */
//#ifndef  clcd_config_H_
//
//  #define  clcd_config_H_
//
//  #define CLCD_DATA_PORT     DIO_U8PORTA
//  #define CLCD_CONTRL_PORT   DIO_U8PORTC
//
//
//  #define CLCD_RS_PIN        DIO_U8PIN0
//  #define CLCD_RW_PIN        DIO_U8PIN1
//  #define CLCD_E_PIN         DIO_U8PIN2
//
///***************************************************************************************/
///********************************** Macros *********************************************/
//
//#define lcd_Clear           0x01          /* replace all characters with ASCII 'space'     */
//#define lcd_Home            0x02          /* return cursor to first position on first line */
//#define lcd_EntryMode       0x06          // shift cursor from left to right on read/write
//#define lcd_DisplayOff      0x08          // turn display off
//#define lcd_DisplayOn       0x0C          // display on, cursor off, don't blink character
//#define lcd_FunctionReset   0x30          // reset the LCD
//#define lcd_FunctionSet8bit 0x38          // 8-bit data, 2-line display, 5 x 7 font
//#define lcd_SetCursor       0x80          // set cursor position
//
///***************************************************************************************/
//
//#endif
