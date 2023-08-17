 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Ahmed GAmal Helmy
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
/******************************************************************************
 *                            types
 ****************************************************************************/
//#define F_CPU  8000000UL
typedef enum{
	UART_5_bitData,
	UART_6_bitData,
	UART_7_bitData,
	UART_8_bitData,
	UART_9_bitData=7,
}UART_BitData;


typedef enum{
	UART_disapleParity,
	UART_evenParity=2,
	UART_oddParity,

}UART_Parity;

typedef enum{
	UART_1_bitStop,
	UART_2_bitStop,

}UART_StopBit;


typedef struct {
	UART_BitData             bit_data;
	UART_Parity              parity;
	UART_StopBit             stop_bit  ;
	uint16                   baud_rate ;
}UART_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * config_ptr );

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
