
/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the ATmega32 dc_motor driver
 *
 * Author: Ahmed  Gamal Helmy
 *
 *******************************************************************************/
#include "dc_motor.h"
#include "gpio.h"




/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * The Function responsible for setup the direction for the two
 * motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.

 */
void DcMotor_Init(void){
	/***************************** setupPinDirection as output pin***********/
	GPIO_setupPinDirection(DC_MOTOR_PORT1_ID, DC_MOTOR_PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT2_ID, DC_MOTOR_PIN2_ID,PIN_OUTPUT);


	/************* Stop  the DC-Motor at the beginning ********************/
	GPIO_writePin(DC_MOTOR_PORT1_ID, DC_MOTOR_PIN1_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT2_ID, DC_MOTOR_PIN2_ID, LOGIC_LOW);



}



/*Description:
 * send duty cycle to PWM_Timer_Start
 * The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the
   required speed value
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	PWM_Timer0_Start(speed);
	if ((state ==CW) )
	{
		/********** Rotate ClockWise****************/
		GPIO_writePin(DC_MOTOR_PORT1_ID, DC_MOTOR_PIN1_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT2_ID, DC_MOTOR_PIN2_ID, LOGIC_LOW);

	}
	else if ((state ==A_CW) )
	{
		/********** Rotate Anti_ClockWise****************/
		GPIO_writePin(DC_MOTOR_PORT1_ID, DC_MOTOR_PIN1_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT2_ID, DC_MOTOR_PIN2_ID, LOGIC_HIGH);
	}
	else if ((state ==stop) )
	{
		/************** Stop The Motor ************/
		GPIO_writePin(DC_MOTOR_PORT1_ID, DC_MOTOR_PIN1_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT2_ID, DC_MOTOR_PIN2_ID, LOGIC_LOW);
	}
	else
	{

	}

}



