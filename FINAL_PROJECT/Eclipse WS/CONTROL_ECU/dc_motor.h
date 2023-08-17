/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the ATmega32 dc_motor driver
 *
 * Author: Ahmed  Gamal Helmy
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
# include "std_types.h"
#include "pwm.h"
#include <avr/io.h>

/*******************************************************************************
 *                                Values                                    *
 * *****************************************************************************/
#define DC_MOTOR_PORT1_ID PORTD_ID
#define DC_MOTOR_PORT2_ID PORTD_ID

#define DC_MOTOR_PIN1_ID PIN6_ID
#define DC_MOTOR_PIN2_ID PIN7_ID
/*******************************************************************************
 *                                Types Declaration                                    *
 * *****************************************************************************/
typedef enum {
	stop,
	CW,
	A_CW
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * The Function responsible for setup the direction for the two
 * motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void);


/*Description:
 * The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the
   required speed value
   */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
