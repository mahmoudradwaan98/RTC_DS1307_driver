/*
 * I2C_Program.c
 *
 *  Created on: Aug 6, 2023
 *      Author: User
 */


#include "STD_TYPES.h"
#include "BIT_MATHS.h"

#include "I2C_Private.h"
#include "I2C_Interface.h"

#include "DIO_interface.h"

void I2C_voidMasterInit(SCL_FREQ_t SCL_FREQ){

	switch(SCL_FREQ){

	case SCL_100KHZ:

	    // Set prescaler == 1 (CLR TWSR 0,1)
	    CLR_BIT(TWSR_REG,TWSR_TWPS0);
	    CLR_BIT(TWSR_REG,TWSR_TWPS1);
	    // Set TWBR with value => 100 KHz ( TWBR = 72 )
	    TWBR_REG = 72;
		break;

	case SCL_400KHZ:

	    // Set prescaler == 1 (CLR TWSR 0,1)
	    CLR_BIT(TWSR_REG,TWSR_TWPS0);
	    CLR_BIT(TWSR_REG,TWSR_TWPS1);
	    // Set TWBR with value => 400 KHz ( TWBR = 12 )
	    TWBR_REG = 12;
		break;

	}


}

Error_t I2C_Master_u8SendSLA_Write_ACK (u8 Copy_u8SlaveAddress)
{
    Error_t Local_Error = I2C_NO_Error ;

    // Write 7 bits slave address ( TWDR == address<<1 )
    //TWDR_REG = (Copy_u8SlaveAddress<<1) ;

    TWDR_REG = Copy_u8SlaveAddress;

    TWCR_REG = (1<<TWCR_TWINT) | (1<<TWCR_TWEN);

    // Wait for flag ( TWCR 7 == 0 )
    while( ( GET_BIT(TWCR_REG,TWCR_TWINT) ) == 0 );

    u8 status_val;

    getStatus(&status_val);

    // Check status code == SLA + Write + ACK == (0x18)
    if ( status_val != MASTER_SLA_Write_ACK )
    {
        Local_Error = I2C_Error_Master_SendSLA_Write_ACK ;
    }
    return Local_Error ;
}

/* this function should send 1 data byte to the other device */
Error_t I2C_Master_u8WriteDataByte_ACK(u8 copy_u8data){

    Error_t Local_Error = I2C_NO_Error ;

    // Write data in TWDR
    TWDR_REG = copy_u8data ;

    // clear interrupt flag
    TWCR_REG = (1<<TWCR_TWINT) | (1<<TWCR_TWEN);

    u8 status_val;

    // Wait for flag ( TWCR 7 == 0 )
    while (!(TWCR_REG & (1<<TWCR_TWINT)));

    getStatus(&status_val);

    // Check status code == Master Send Data + ACK == (0x28)
    if (  status_val != MASTER_WR_DataByte_ACK )
    {
        Local_Error = I2C_Error_Master_WriteDataByte_ACK ;
    }

    return Local_Error ;

}

/* this function should send start condition */
Error_t I2C_Master_u8StartCondition(void)
{
    // Enable I2C  ( set TWCR 2 ) , Start condition ( Set TWCR 5) , Clear flag ( Set TWCR 7 )
	TWCR_REG = (1<<TWCR_TWINT)|(1<<TWCR_TWSTA)|(1<<TWCR_TWEN);

	 while (!(TWCR_REG & (1<<TWCR_TWINT)));

    Error_t Local_Error = I2C_NO_Error ;

    u8 status_val;

    getStatus(&status_val);

    // Check status code == start condition ( TWSR & 0xf8 ) == 0x08
    if ( status_val != MASTER_START_ACK )
    {
        Local_Error = I2C_Error_Master_StartCond_ACK ;
    }
    return Local_Error;

}

/* this function should send stop condition */
Error_t I2C_Master_u8StopCondition(void)
{
	TWCR_REG = (1<<TWCR_TWINT)|(1<<TWCR_TWEN)|(1<<TWCR_TWSTO);

    return I2C_NO_Error;

}

/* this function should receive 1 byte and respond with ACK */
Error_t I2C_Master_u8ReadDataByte_ACK(u8 * ptr){

    // Enable ACK  ( Set TWCR 6 )
    SET_BIT(TWCR_REG,TWCR_TWEA);

    Error_t Local_Error = I2C_NO_Error ;

    u8 status_val;

    getStatus(&status_val);

    // Wait for flag ( TWCR 7 == 0 )
    while (!(TWCR_REG & (1<<TWCR_TWINT)));

    // Check status code == Master Read Data + ACK == (0x50)
    if ( status_val != MASTER_RD_DataByte_ACK )
    {
        Local_Error = I2C_Error_Master_ReadDataByte_ACK ;
    }
    // Read Data From Register TWDR
    *ptr = TWDR_REG ;

    return Local_Error ;

}

/* this function should receive 1 byte and respond with NO ACK */
Error_t I2C_Master_u8ReadDataByte_NOTACK(u8 * ptr){

		// Disable ACK  ( CLR TWCR 6 )
		CLR_BIT(TWCR_REG,TWCR_TWEA);

		Error_t Local_Error = I2C_NO_Error ;

		u8 status_val;

	    // Wait for flag ( TWCR 7 == 0 )
	    while (!(TWCR_REG & (1<<TWCR_TWINT)));

		getStatus(&status_val);

	    // Check status code == Master Read Data + NOTACK == (0x58)
	    if ( status_val != MASTER_RD_DataByte_NOTACK )
	    {
	        Local_Error = I2C_Error_Master_ReadDataByte_NOTACK ;
	    }

	    // Read Data From Register TWDR
	    *ptr = TWDR_REG ;

	    return Local_Error ;

}

Error_t I2C_Master_u8ReStartCondition(void)
{
    Error_t Local_Error = I2C_NO_Error ;

    // Enable I2C  ( set TWCR 2 ) , Start condition ( Set TWCR 5) , Clear flag ( Set TWCR 7 )
	TWCR_REG = (1<<TWCR_TWINT)|(1<<TWCR_TWSTA)|(1<<TWCR_TWEN);


	u8 status_val;

	getStatus(&status_val);

	 // Wait for flag ( TWCR 7 == 0 )
    while( ( GET_BIT(TWCR_REG,TWCR_TWINT) ) == 0 );

    // Check status code == Repeat condition ( TWSR & 0xf8 ) == 0x10
    if ( status_val != MASTER_REP_START_ACK )
    {
        Local_Error = I2C_Error_Master_ReStartCond_ACK ;
    }
    return Local_Error ;
}


Error_t I2C_Master_u8SendSLA_Read_ACK (u8 Copy_u8SlaveAddress)
{
    Error_t Local_Error = I2C_NO_Error ;

    // Write 7 bits slave address ( TWDR == address<<1 )
    TWDR_REG = (Copy_u8SlaveAddress<<1) ;

    // Read condition ( SET TWDR 0 )
    TWCR_REG = (1<<TWCR_TWINT) | (1<<TWDR_TWD0);

    // Wait for flag ( TWCR 7 == 0 )
    while( ( GET_BIT(TWCR_REG,TWCR_TWINT) ) == 0 );

    // Check status code == SLA + Read + ACK == (0x40)
    if ( (TWSR_REG & STATUS_BIT_MASK) != MASTER_SLA_Read_ACK )
    {
        Local_Error = I2C_Error_Master_SendSLA_Read_ACK ;
    }
    return Local_Error ;
}
/* this function should read status of status register */
void getStatus(u8* status ){

	*status = (TWSR_REG & STATUS_BIT_MASK);
}
