#include"lcd.h"
#include"keypad.h"
#include"std_types.h"
#include"util/delay.h"
int main(void){
	volatile uint8 key,num1=0,num2=0,symbol=0,op;
	volatile uint16 result;
	LCD_init();
	while(1){
		key=KEYPAD_getPressedKey();
		_delay_ms(200);
		if((key>=0)&&(key<=9)&&(symbol==0)){
			num1=num1*10+key;
			LCD_intgerToString(key);
		}
		else if((key>=0)&&(key<=9)&&(symbol!=0)){
			num2=num2*10+key;
			LCD_intgerToString(key);
		}
		else if(key==13){
			symbol=0;
			num1=0;
			num2=0;
			LCD_clearScreen();
		}
		else if(key=='='){
			switch(op){
			case '+': result=num1+num2;
			break;
			case '-': result=num1-num2;
			break;
			case '*': result=num1*num2;
			break;
			case '/': result=num1/num2;
			break;
			}
			LCD_displayCharacter(key);
			LCD_intgerToString(result);
		}
		else {
			op=key;
			symbol=1;
			LCD_displayCharacter(key);
		}
		_delay_ms(200);
	}
}


