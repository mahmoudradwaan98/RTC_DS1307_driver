  /*
   * LCD_Interface.h
   *
   * Created: 7/22/2023 6:51:55 PM
   *  Author: Rizk
   */


  #ifndef LCD_INTERFACE_H_
  #define LCD_INTERFACE_H_

  void LCD_voidInit(void);

  void Lcd_SendCmd(u8 Command);

  void LCD_voidSenddata(u8 data);

  void Lcd_DisplayStr(u8* str);

  void Lcd_Goto_Row_Column(u8 row, u8 col);

  void Lcd_DisplayChr(u8 chr);

  void Lcd_Displaynum(u16 number);



  void Enable_Pulse(void);

  #endif /* LCD_INTERFACE_H_ */



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
  //
  //
  //
  //#ifndef  clcd_interface_H_
  //
  //  #define  clcd_interface_H_
  //
  //
  //  void CLCD_voidSendCommand(u8 copy_u8command);
  //
  //  void CLCD_voidSendData(u8 copy_u8data);
  //
  //  void CLCD_VoidINIT(void);
  //
  //  void CLCD_vidWriteChar(u8 u8DataCpy);
  //
  //  void LCD_vidWriteString (u8* pu8StringCpy, u8 u8Index);
  //
  //  void Gotoxy (u8 Y,u8 X);
  //
  //  void LCD_vidWriteExtraChar (u8 Y,u8 X);
  //
  //
  //#endif
