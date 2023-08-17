/******************************************************************************
 *
 * Module: buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the buzzer
 *
 * Author: Ahmed Gamal Helmy
 *
 *******************************************************************************/

#include"buzzer.h"




/*
 * Description :
 * - Setup the direction for the buzzer pin as output pin through the
 *  GPIO driver
 *
 *  -Turn off the buzzer through the GPIO
 */
void BUZZER_init(void){
	GPIO_setupPinDirection(BUZZER_PORT_ID , BUZZER_PIN1_ID , PIN_OUTPUT);



	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN1_ID, LOGIC_LOW);


}

/*
 * Description
 * Function to enable the Buzzer through the GPIO.
 * Inputs: None
 *  Return: None
 */
void BUZZER_on(void){
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN1_ID, LOGIC_HIGH);

}

/*
 * Description
 * Function to disable the Buzzer through the GPIO.
 * Inputs: None
 *  Return: None
 */
void BUZZER_off(void){
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN1_ID, LOGIC_LOW);

}

