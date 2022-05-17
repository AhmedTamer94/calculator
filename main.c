 /******************************************************************************
 *
 * Simple Calculator
 *
 * Description: The output calculations from -3278 to 32767
 *
 * Author: Ahmed Tamer
 *
 * Date: 17/5/2022
 *
 *******************************************************************************/
#include"lcd.h"
#include"keypad.h"
#include"std_types.h"
#include"gpio.h"
#include"util/delay.h"
int main(void){
	/* VAR key: the microcontroller get the input number from the keypad
	 * and store it in this variable.
	 *
	 * VAR symbol we check by using it if the user hit a symbol or not.
	 *
	 * VAR operation: store the operation corresponding ASCII code which we
	 * get it from the keypad in it.
	 *
	 * VAR num1 and num2 and result: we store the numbers the user hit in it.
	 */
	volatile uint8 key,symbol=0,operation;
	volatile sint16 num1,num2;
	volatile sint16 result;
	LCD_init();
	while(1){
		key=KEYPAD_getPressedKey();//scan the keypad till we get an input

		_delay_ms(200);/*delay 200ms so we simulate the user's pushing as the code
		we be executed and return to the first instruction in this while loop
		and the user did't release his finger yet so it will get a wrong scan.*/

		if((key>=0)&&(key<=9)&&(symbol==0)){/* if the input is a number
		and we didn't hit a symbol or an operation yet do these instructions*/

			num1=num1*10+key;//store the input number to the num1 even if the num>10
			LCD_intgerToString(key);//display only the input number that stored in key VAR
		}
		else if((key>=0)&&(key<=9)&&(symbol!=0)){/* if the key VAR is a number and
		the symbol VAR is changed that's means the user hit a symbol or operation*/

			num2=num2*10+key;//store the input number to the num2 even if the num>10
			LCD_intgerToString(key);//display only the input number that stored in key VAR
		}
		else if(key==13){//if the user hit 'AC/ON' clear the screen and reset the VARs
			symbol=0;
			num1=0;
			num2=0;
			LCD_clearScreen();
		}
		else if(key=='='){//if the user hit '=' do the operation that stored in op VAR
			switch(operation){
			case '+':
				if(symbol=='-')/*here we check if the user wants the second number to be
				a negative number and press '-' after he pressed the operation and
				before he insert the second number*/
					result=num1-num2;
				else
					result=num1+num2;
				break;
			case '-':
				if(symbol=='-')
					result=num1+num2;
				else
					result=num1-num2;
				break;
			case '*':
				if(symbol=='-')
					result=num1*num2*(-1);
				else
					result=num1*num2;
				break;
			case '/':
				if(num1==0)/*if the first num is 0 and the operation is '/' store
				the ASCII code of 'e' in key VAR and do nothing else*/
					key='e';
				else
					if(symbol=='-')
						result=(num1/num2)*(-1);
					else
						result=num1/num2;
				break;
			}
			if(key=='e'){//if the num1 is 0 and the op VAR is '/' clear screen and
				//display error word
				LCD_clearScreen();
				LCD_displayString("ERROR");
			}

			else{/* if num1 is not 0 and op VAR is not '/' display the result VAR
			in ne line*/
				LCD_displayCharacter(key);
				LCD_sendCommand(LCD_SET_CURSOR_LOCATION+0x40);
				LCD_intgerToString(result);

			}
		}
		else {/* if the symbol VAR is 0 then the user didn't insert the first number
		so store the key ASCII code in op VAR and make the symbol VAR is 1*/
			if(symbol==0){
				operation=key;
				symbol=1;
			}
			else if (symbol==1)/* if the symbol is 1 and we are in this case again
			this means the user hit the -' and the second number will be negative
			sign so store the ASCII code of '-' in the symbol as we will check on
			it in the previous switch case to do the operation and display the final
			result*/
				symbol=key;

			LCD_displayCharacter(key);
		}
		_delay_ms(200);/*delay 200ms so we simulate the user's pushing as the code
		we be executed and return to the first instruction in this while loop
		and the user did't release his finger yet so it will get a wrong scan.*/
	}
}


