/******************************************************************************
 *
 *
 * File Name: app.c
 *
 * Description: Source file for the application
 *
 * Author: Ahmed Gamal Helmy
 *
 *******************************************************************************/
#include "app.h"


int main (void){
	uint8 command ;
	uint8 password1[PASSWORD_SIZE],password2[PASSWORD_SIZE];

	SREG |=(1<<7);                        /****************enable I bit ********************/

	UART_init(&UART_configuration);       /***************** initialize UART ***************/
	EEPROM_init();


	BUZZER_init();                        /******************* initialize EEPROM ***********/

	DcMotor_Init();                       /********************* initialize DC MOTOR********/


	while (UART_recieveByte()!=HMI_READY){};

	while (1){
		command=UART_recieveByte();
		switch (command){


		case PASS_CHECK:
			checkPassword(password1, password2);
			break;

		case CREATE_NEW_PASS:
			SETUP_NEW_PASS(password1, password2);
			break;

		case OPEN_DOOR:
			open_door();
			break;

		case ALARM_ON:
			ALARM_ONN();
			break;
		case IF_PASS_EXIST :
			CHECK_PASS_EXIST();
			break;
		case RESET_PASS:
			RESET_PASSWORD();
			break ;


		}
	}




}



/*************************receive pass*********************************
 * ● Description
 *   ⮚ Function to receive passord
 * ● Inputs: arr[5]
 * ● Return: None
 *********************************************************************/
void recieve_password(uint8 arr[PASSWORD_SIZE]){
	uint8 i;
	while (UART_recieveByte() !=HMI_READY){} ;
	UART_sendByte(HMI_READY);
	for (i=0;i<PASSWORD_SIZE;i++){
		arr[i]=UART_recieveByte();
	}

	UART_sendByte(DONE);
}


/*************************store pass*********************************
 * ● Description
 *   ⮚ Function to store passord in eeprom
 * ● Inputs: NONE
 * ● Return: None
 *********************************************************************/
void store_password(void){
	uint8 i=0;
	EEPROM_init() ;                       /**************** initialize EEPROM **************/
	for (i=0;i<PASSWORD_SIZE;i++){
		EEPROM_writeByte(0x0311+i,g_password[i]);
		delaySeconds(1);
	}
}


/*************************check pass*********************************
 * ● Description
 *   ⮚ Function to receive passord
 * ● Inputs: arr1[] , arr2[]
 * ● Return: TRUE OR FALSE
 *********************************************************************/



uint8 compare_password(uint8* a_arr1,uint8 *a_arr2){
	uint8 i,counter=0;
	for (i=0;i<PASSWORD_SIZE;i++){
		if (a_arr1[i]==a_arr2[i]){
			counter++;
		}

	}
	if (counter==PASSWORD_SIZE){
		return TRUE;
	}
	else
		return FALSE ;



}
/*************************check password*********************************
 * ● Description
 *   ⮚ Function to receive passord
 * ● Inputs: arr1[] , arr2[]
 * ● Return: TRUE OR FALSE
 *********************************************************************/
void checkPassword(uint8 * pass1, uint8 * pass2)
{
	uint8 i;
	/* receive the first password */
	for(i=0;i<5;i++)
	{
		pass1[i] = UART_recieveByte();
	}
	/* read the password saved in the EEPROM */
	for(i=0;i<5;i++)
	{
		EEPROM_readByte(0x00F0+i, pass2+i);
		_delay_ms(10);
	}
	/* if they matched tell the HMI_ECU that passwrod is right */
	if(compare_password(pass1, pass2) ==TRUE)
	{
		UART_sendByte(PASS_CORRECT);
	}
	else
	{
		UART_sendByte(ERROR);
	}
}





void SETUP_NEW_PASS(uint8 *p1_ptr,uint8 *p2_ptr){
	uint8 i;
	/***********get pass*********/
	for (i=0;i<PASSWORD_SIZE;i++){
		p1_ptr[i] =UART_recieveByte();
	}
	/********confirm password********/
	for (i=0;i<PASSWORD_SIZE;i++){
		p2_ptr[i] =UART_recieveByte();
	}
	/*********compare pass1 &pass2********/
	if (compare_password(p1_ptr,p2_ptr)==TRUE){
		/*************if true ->>>  store new pass in eeprom**************/
		for (i=0;i<PASSWORD_SIZE;i++){
			EEPROM_writeByte(0x00F0+i, p1_ptr[i]);
			_delay_ms(10);
		}
		EEPROM_writeByte(0x00F0 - 1, PASS_EXIST);
		_delay_ms(10);
		UART_sendByte(NEW_PASS_SAVED);
	}
	else
		UART_sendByte(ERROR);
}



/*************************open door*********************************
 * ● Description
 *   ⮚ Function to receive passord
 * ● Inputs: arr1[] , arr2[]
 * ● Return: None
 *********************************************************************/
void open_door(void){
	/*****************rotate CW to UNLOCK the door *******************/
	DcMotor_Rotate(CW, 100);
	delaySeconds(15);

	/*************hold dc motor for 3 seconds ***************/
	DcMotor_Rotate(stop, 0);
	delaySeconds(3);

	/*****************rotate A_CW to LOCK the door *******************/
	DcMotor_Rotate(A_CW, 100);
	delaySeconds(15);
	/*************  stop the motor **************/
	DcMotor_Rotate(stop, 0);

}

void C_second(void){
	g_sec++;
}


/*************************cdelay function*********************************
 * ● Description
 *   ⮚ Function to delay
 * ● Inputs: seconds
 * ● Return: None
 *********************************************************************/
void delaySeconds(uint8 sec)
{

	Timer1_setCallBack(C_second);         /* setting the callBack function to count seconds */
	/* timer1 configurations to count sec per interrupt */
	Timer1_ConfigType timer1_Config = {0,31250,TIMER1_CLK_256,TIMER1_CTC_Mode};
	Timer1_init(&timer1_Config);
	while(g_sec < sec);
	g_sec = 0;
	Timer1_deInit();

}


/*************************ALARM function*********************************
 * ● Description
 *   ⮚ Function to ONN ALARM
 * ● Inputs: seconds
 * ● Return: None
 *********************************************************************/
void ALARM_ONN(void){
	BUZZER_on()	;
	delaySeconds(60);
	BUZZER_off();
}

/*************************check password exist*********************************
 * ● Description
 *   ⮚ Function to check pass exit
 * ● Inputs: None
 * ● Return: None
 *********************************************************************/
void CHECK_PASS_EXIST(void ){
	uint8 checker ;
	EEPROM_readByte(0x00F0-1, &checker);
	_delay_ms(10);
	if (checker ==PASS_EXIST)
		UART_sendByte(PASS_EXIST);
	else
		UART_sendByte(ERROR);

}

void RESET_PASSWORD(void){
	EEPROM_writeByte(0x00F0-1, 0x00);
	_delay_ms(10);
	UART_sendByte(RESET_COMPLETE);
}






