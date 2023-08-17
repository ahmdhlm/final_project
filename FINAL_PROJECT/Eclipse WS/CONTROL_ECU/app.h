/******************************************************************************
 *
 *
 * File Name: app.h
 *
 * Description: header file for the application of CONTROL
 *
 * Author: Ahmed Gamal Helmy
 *
 *******************************************************************************/
#ifndef APP_H_
#define APP_H_
#include "buzzer.h"
#include "dc_motor.h"
#include "external_eeprom.h"
#include "pwm.h"
#include "timer1.h"
#include "twi.h"
#include "uart.h"
#include "avr/io.h"
#include "util/delay.h"
/******************************************************************************
 *                           definitions
 *
 *******************************************************************************/


/**********************UART Configurations****************************/
UART_ConfigType UART_configuration = {UART_8_bitData,UART_disapleParity,UART_1_bitStop,9600};




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



/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8 g_sec = 0;
uint8 g_password[PASSWORD_SIZE ];





/***************************************************************************
 *                            Functions prototypes
 **************************************************************************/


/*************************receive pass*********************************
 * ● Description
 *   ⮚ Function to receive passord
 * ● Inputs: arr[5]
 * ● Return: None
 *********************************************************************/
void recieve_password(uint8 arr[PASSWORD_SIZE]);



/*************************store pass*********************************
 * ● Description
 *   ⮚ Function to store passord in eeprom
 * ● Inputs: arr[5]
 * ● Return: None
 *********************************************************************/
void store_password(void);



/*************************check pass*********************************
 * ● Description
 *   ⮚ Function to receive passord
 * ● Inputs: arr1[] , arr2[]
 * ● Return: TRUE OR FALSE
 *********************************************************************/
uint8 compare_password(uint8* a_arr1,uint8 *a_arr2);


/*************************SET NEW PASSWORD function*********************************
 * ● Description
 *   ⮚ Function to ONN ALARM
 * ● Inputs: ptr to char , ptr to char
 * ● Return: None
 *********************************************************************/
void SETUP_NEW_PASS(uint8 *p1_ptr,uint8 *p2_ptr);


void open_door(void);

/*************************receive_command*********************************
 * ● Description
 *   ⮚ Function to receive command
 * ● Inputs: none
 * ● Return: command
 *********************************************************************/
uint8 receive_command(void);




/*************************cdelay function*********************************
 * ● Description
 *   ⮚ Function to delay
 * ● Inputs: seconds
 * ● Return: None
 *********************************************************************/
void C_second(void) ;  /*********contain global vaible which increases to delay*********/
void delaySeconds(uint8 sec);




/*************************ALARM function*********************************
 * ● Description
 *   ⮚ Function to ONN ALARM
 * ● Inputs: seconds
 * ● Return: None
 *********************************************************************/
void ALARM_ONN(void);

/*************************check password exist*********************************
 * ● Description
 *   ⮚ Function to check pass exit
 * ● Inputs: None
 * ● Return: None
 *********************************************************************/
void CHECK_PASS_EXIST(void );

/*************************RESET PASSWORD*********************************
 * ● Description
 *   ⮚ Function to reset password
 * ● Inputs: None
 * ● Return: None
 *********************************************************************/
void RESET_PASSWORD(void);


void checkPassword(uint8 * pass1, uint8 * pass2);

#endif /* APP_H_ */
