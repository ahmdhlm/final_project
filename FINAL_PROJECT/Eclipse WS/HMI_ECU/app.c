


/******************************************************************************
 *
 *
 * File Name: app.c
 *
 * Description: Source file for the application of HMI
 *
 * Author: Ahmed Gamal Helmy
 *
 *******************************************************************************/


#include "app.h"


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* seconds counter */
uint8 g_sec = 0;

/* counter for no.of wrong pass */
uint8 PassWrongCounter = 0;


int main (void){
	uint8 pass1[PASSWORD_SIZE],pass2[PASSWORD_SIZE],keyPressed;

	uint8 pass_flag=0 ;
	SREG|=(1<<7); /***********enable I bit *********/
	LCD_init() ;  /*********initialize LCD Screen *******/
	UART_init(&UART_configuration) ;     /*********initialize UART *******/
	delaySeconds(1);
	UART_sendByte(HMI_READY);

	while (1){
		if (pass_flag==0){    /*************check is password is set or not*******/
			UART_sendByte(IF_PASS_EXIST);


			if (UART_recieveByte()==PASS_EXIST){
				pass_flag=1;
				continue;
			}
			do
			{
				getPassword(pass1);
				getPasswordConfirmation(pass2);

				pass_flag=1;
			}while (checkPasswordIsSame(pass1,pass2)==PASSWORD_NOT_MATCHED);
		}
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "+ :OPEN DOOR");
			LCD_displayStringRowColumn(1 ,0, "- :CHANGE PASSWORD");


			/************loop till enter + or - ************/
			do
			{
				keyPressed = KEYPAD_getPressedKey();
			}while(keyPressed != '+' && keyPressed != '-');

			if (keyPressed =='+')
			{

				while (1){
					getPassword(pass1);
					if (check_password(pass1)==TRUE)
					{
						open_door() ;
						break ;
					}
					else
					{PassWrongCounter++;
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"WRONG PASSWORD" );
					_delay_ms(500);
					}
					if (PassWrongCounter==3)
					{
						ALARM_ONN();
						break;
					}
				}
				PassWrongCounter=0; /**********reset passwrong counter*********/

			}
			else{


				while (1){
					getPassword(pass1);
					if (check_password(pass1)==TRUE)
					{
						LCD_clearScreen();
						LCD_moveCursor(0,0);
						LCD_displayString("change password");
						//delaySeconds(1);
						_delay_ms(1000);
						pass_flag=0 ;/************reset pass_flag*********/
						/* deletes the password in the EEPROM */
						/***********/
						UART_sendByte(RESET_PASS);
						while(UART_recieveByte() != RESET_COMPLETE );

						break;
					}
					else
					{
						PassWrongCounter++;
						LCD_clearScreen();
						LCD_moveCursor(0,0);
						LCD_displayString("Wrong PASSWORD");
						_delay_ms(500);
					}
					if (PassWrongCounter==3)
					{
						ALARM_ONN();
						break;
					}
				}
			PassWrongCounter=0; /**********reset passwrong counter*********/
			}
		}
		/**/



	}




/*************************cdelay function*********************************
 * ● Description
 *   ⮚ Function to delay
 * ● Inputs: seconds
 * ● Return: None
 *********************************************************************/

void C_second(void)
{
	g_sec++;
}


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

void setPassword(void){
	LCD_clearScreen();
	LCD_displayString("seting new password");

	UART_sendByte(CREATE_NEW_PASS);

}






/************************* GETPASSWORD *********************************
 * ● Description
 *   ⮚ Function to get password
 * ● Inputs: password 1
 * ● Return: None
 *********************************************************************/
void getPassword(uint8 *pass){
	uint8 i; /*******counter***********/
	uint8 keyPressed ; /*************store pressed key*********/
	LCD_clearScreen();
	LCD_displayString("PLEASE, ENTER PASS:");
	LCD_moveCursor(1, 0);

	for (i=0;i<PASSWORD_SIZE;i++){
		do
		{
			keyPressed = KEYPAD_getPressedKey();
			_delay_ms(500);
		}while((keyPressed > 9));
		pass[i] = keyPressed;
		LCD_moveCursor(1, i);
		LCD_intgerToString(pass[i]);
		_delay_ms(100);
		LCD_moveCursor(1, i);
		LCD_displayCharacter('*');

	}
	while (KEYPAD_getPressedKey()!=13);



}

/*************************PASSWORD CONFIRM*********************************
 * ● Description
 *   ⮚ Function to confirm password
 * ● Inputs: password 2
 * ● Return: None
 *********************************************************************/
void getPasswordConfirmation(uint8 * pass)
{
	/* variable to store pressed key */
	uint8 keyPressed;
	/* counter variable for FOR Loop */
	uint8 i;
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("please, re-enter the same pass:");
	LCD_moveCursor(1, 0);


	/* loop to get the password Confirmation */
	for(i=0;i<5;i++)
	{
		do
		{
			keyPressed = KEYPAD_getPressedKey();
			_delay_ms(500);
		}while(keyPressed > 9);
		pass[i] = keyPressed;

		LCD_intgerToString(pass[i]);
		_delay_ms(100);
		LCD_moveCursor(1, i);
		LCD_displayCharacter('*');
	}while(KEYPAD_getPressedKey() != 13);


}

/*************************CHeck password is same? *********************************
 * ● Description
 *   ⮚ Function to open the door
 * ● Inputs: pass1 ,pass2
 * ● Return: same or not
 *********************************************************************/
uint8 checkPasswordIsSame(uint8* pass1 , uint8*pass2){
	uint8 i; /***********counter*********/
	UART_sendByte(CREATE_NEW_PASS);
	for (i=0;i<PASSWORD_SIZE;i++){
		UART_sendByte(pass1[i]);
	}
	for (i=0;i<PASSWORD_SIZE;i++){
		UART_sendByte(pass2[i]);
	}
	if (UART_recieveByte()== NEW_PASS_SAVED){
		return PASSWORD_MATCHED ;
	}
	else
		return PASSWORD_NOT_MATCHED ;
}



/*************************check pass*********************************
 * ● Description
 *   ⮚ Function to receive passord
 * ● Inputs: arr1[] , arr2[]
 * ● Return: TRUE OR FALSE
 *********************************************************************/
uint8  compare_password(uint8* pass1 ,uint8*pass2){
	uint8 i,counter=0;
	for (i=0;i<PASSWORD_SIZE;i++){
		if (pass1[i]==pass2[i]){
			counter++;
		}

	}
	if (counter==PASSWORD_SIZE){
		return TRUE;
	}
	else
		return FALSE ;
}

/***************check password ****************/

uint8 check_password (uint8 *pass){
	uint8 i=0;
	UART_sendByte(PASS_CHECK);
	for (i=0;i<PASSWORD_SIZE;i++){
		UART_sendByte(pass[i]);
	}
	if (UART_recieveByte()==PASS_CORRECT)
		return TRUE ;
	else
		return FALSE;


}


/*************************open door*********************************
 * ● Description
 *   ⮚ Function to open the door
 * ● Inputs: arr1[] , arr2[]
 * ● Return: None
 *********************************************************************/
void open_door(void){
	UART_sendByte(OPEN_DOOR);
	LCD_clearScreen();
	LCD_displayString("DOOR IS UNLOCKING");

	// _delay_ms(5000);
	delaySeconds(15);

	LCD_clearScreen();
	LCD_displayString("DOOR IS OPEN");
	delaySeconds(3);
	//_delay_ms(2000);

	LCD_clearScreen();
	LCD_displayString("DOOR IS LOCKING");
	//_delay_ms(5000);
	delaySeconds(15);


}


/*************************ALARM function*********************************
 * ● Description
 *   ⮚ Function to ONN ALARM
 * ● Inputs: seconds
 * ● Return: None
 *********************************************************************/
void ALARM_ONN(void){
	UART_sendByte(ALARM_ON);
	LCD_clearScreen();
	LCD_displayString("  stealing!! ");
	delaySeconds(60);

}






