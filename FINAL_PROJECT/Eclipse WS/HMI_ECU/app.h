/******************************************************************************
 *
 *
 * File Name: app.h
 *
 * Description: header file for the application of HMI
 *
 * Author: Ahmed Gamal Helmy
 *
 *******************************************************************************/

#ifndef APP_H_
#define APP_H_
#include "timer1.h"
#include "uart.h"
#include "lcd.h"
#include "keypad.h"
#include <util/delay.h>
#include <avr/io.h>

//#define F_CPU  8000000UL

/**********************UART Configurations****************************/
UART_ConfigType UART_configuration = {UART_8_bitData,UART_disapleParity,UART_1_bitStop,9600};
/******************************************************************************
 *                           definitions
 *
 *******************************************************************************/
#define PASSWORD_SIZE               5

#define ERROR                       0

#define HMI_READY                   0x01
#define DONE                        0x02
#define CHECK_PASSWORD              0x03
#define WRONG_PASSOWRD              0x03
#define ALARM_ON                    0x04

#define CREATE_NEW_PASS             0x05
#define OPEN_DOOR                   0x06

#define IF_PASS_EXIST               0x07
#define  PASS_EXIST                 0x08

#define SETTING_NEW_PASSWORD        0x09
#define NEW_PASS_SAVED              0x0A
#define PASSWORD_MATCHED            0x0B
#define PASSWORD_NOT_MATCHED        0x0C

#define RESET_PASS                  0x0D
#define RESET_COMPLETE              0x0E
#define PASS_CORRECT                0x0F
#define PASS_CHECK                  0x10



/*********function prototypes *******************/
void setPassword(void);
void getPassword(uint8 *pass);
void getPasswordConfirmation(uint8 * pass);
uint8 checkPasswordIsSame(uint8* pass1 , uint8*pass2);
uint8  compare_password(uint8* pass1 ,uint8*pass2);
void open_door(void);
void ALARM_ONN(void);
void C_second(void);
void delaySeconds(uint8 sec);
uint8 check_password (uint8 *pass);

#endif /* APP_H_ */
