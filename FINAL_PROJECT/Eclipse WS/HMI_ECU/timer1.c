/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer1.c
 *
 * Description: Source file for the timer1 AVR driver
 *
 * Author: Ahmed Gamal Helmy
 *
 *******************************************************************************/


#include "timer1.h"


#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;




/*************************TIMER1 INIT*********************************
 * ● Description
 *   ⮚ Function to initialize the Timer driver
 * ● Inputs: pointer to the configuration structure with type
 *    Timer1_ConfigType.
 * ● Return: None
 *********************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	//SREG|=(1<<7);


	if(Config_Ptr->mode == TIMER1_NORMAL_Mode)
	{
		/* Configure timer control register TCCR1A
		 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
		 * 2. FOC1A=1 FOC1B=1
		 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
		 */
		TCCR1A = 0x0C;


	}
	else
	{
		/* Configure timer control register TCCR1A
		 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
		 * 2. FOC1A=1 FOC1B=1
		 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
		 */
		TCCR1A = 0x0C;
		/* Configure timer control register TCCR1B
		 * 1. CTC Mode WGM12=1  (Comapare mode)
		 ***/
		TCCR1B = 0x08;
		/****************configure compare value ******************/
		OCR1A = Config_Ptr->compare_value;


	}
	/*****************start count from initial value************/
	TCNT1 = Config_Ptr->initial_value;

	/**********************configure  prescalar********************/
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->prescaler & 0x07);

	if (Config_Ptr->mode==TIMER1_NORMAL_Mode){
		/*
		 * Over flow interrupt enable
		 */
		TIMSK=(1<<TOIE1);
	}
	else {
		/*
		 * compare interrupt interrupt enable
		 */
		TIMSK=(1<<OCIE1A);
	}
}


/*************************TIMER1 deINIT*********************************
 * ● Description
 *   ⮚ Function to disable the Timer1
 * ● Inputs: NONE
 * ● Return: None
 *********************************************************************/

void Timer1_deInit(void){
	//	SREG&=~(1<<7);
	TCCR1B = 0;
	TCCR1A = 0;
	OCR1A = 0;
	TCNT1 = 0;
}


/**********************TIMERSET CALL back********************
 * ● Description
 *   ⮚ Function to set the Call Back function address
 * ● Inputs: pointer to Call Back function
 * ● Return: None
 ***********************************************************/
void Timer1_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr = (volatile void (*)(void))a_ptr;

}


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(* g_callBackPtr)();
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(* g_callBackPtr)();
	}
}




