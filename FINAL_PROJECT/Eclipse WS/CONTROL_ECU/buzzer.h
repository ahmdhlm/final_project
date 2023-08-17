/******************************************************************************
 *
 * Module: buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the buzzer
 *
 * Author: Ahmed Gamal Helmy
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"
#include "gpio.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define BUZZER_PORT_ID     PORTC_ID


#define BUZZER_PIN1_ID      PIN7_ID




/*
 * Description :
 * - Setup the direction for the buzzer pin as output pin through the
 *  GPIO driver
 *
 *  -Turn off the buzzer through the GPIO
 */
void BUZZER_init(void);



/*
 * Description
 * Function to enable the Buzzer through the GPIO.
 * Inputs: None
 *  Return: None
 */

void BUZZER_on(void);





/*
 * Description
 * Function to disable the Buzzer through the GPIO.
 * Inputs: None
 *  Return: None
 */
void BUZZER_off(void);

#endif /* BUZZER_H_ */
