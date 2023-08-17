 /******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer1.h
 *
 * Description: header file for the timer1 AVR driver
 *
 * Author: Ahmed Gamal Helmy
 *
 *******************************************************************************/
#ifndef TIMER1_H_
#define TIMER1_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include"std_types.h"


/***************************************************
 *                 global variables
 * ************************************************/
/* global variable contain the ticks count of the timer */
//uint8 char g_tick = 0;



/****************************************************************
 *                     Types Declarations
 ****************************************************************/



/******************************************************
 * DESCRIPTION : used to define timer1 prescalar
 *****************************************************/
typedef enum {

	TIMER1_NoClock,
	TIMER1_CLK_1,
	TIMER1_CLK_8,
	TIMER1_CLK_64,
	TIMER1_CLK_256,
	TIMER1_CLK_1024,
	TIMER1_EXT_CLK_FALLING,
	TIMER1_EXT_CLK_RISING,
}Timer1_Prescaler;

/******************************************************
 * DESCRIPTION : used to define mode in timer 1
 *****************************************************/
typedef enum {
	TIMER1_NORMAL_Mode,
	TIMER1_CTC_Mode
}Timer1_Mode;

/******************************************************
 * DESCRIPTION : STRUCT FOR CONFIGRATIONS
 *****************************************************/
typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;



/*************************TIMER1 INIT*********************************
 * ● Description
   *   ⮚ Function to initialize the Timer driver
 * ● Inputs: pointer to the configuration structure with type
 *    Timer1_ConfigType.
 * ● Return: None
 *********************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr);




/*************************TIMER1 deINIT*********************************
 * ● Description
   *   ⮚ Function to disable the Timer1
 * ● Inputs: NONE
 * ● Return: None
 *********************************************************************/

void Timer1_deInit(void);


/**********************TIMERSET CALL back********************
 * ● Description
   *   ⮚ Function to set the Call Back function address
 * ● Inputs: pointer to Call Back function
 * ● Return: None
 ***********************************************************/
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER1_H_ */
