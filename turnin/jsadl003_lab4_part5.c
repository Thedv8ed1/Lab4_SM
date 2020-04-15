/*	Author: jsadl003
 *      Partner(s) Name: Jason Sadler
 *	Lab Section: 21
 *	Assignment: Lab #4  Exercise #5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char input[4];
unsigned char key[4];
unsigned short index;    

enum LK_States{ LK_SMStart = 99, LK_Locked = 0, LK_Unlocked = 1, LK_LPressed, LK_LPressed_Wait, LK_LCheck, LK_ULPressed, LK_ULPressed_Wait, LK_ULCheck
} LK_State;

void TickFct_LK(){
	switch (LK_State){
		unsigned char i;
	case LK_SMStart:
		input[0] = 0x00; key[0] = 0x04; // hash
		input[1] = 0x00; key[1] = 0x01; // x
		input[2] = 0x00; key[2] = 0x02; // y
		input[3] = 0x00; key[3] = 0x01; // x
		index = 0x00;
		LK_State = LK_Locked;
		break;
	case LK_Locked:
		if ((PINA) != 0x00){
			LK_State = LK_LPressed;
		}
		else{
			LK_State = LK_Locked;
		}
		break;
	case  LK_LPressed:
		LK_State = LK_LCheck;
		break;
	case LK_LPressed_Wait:
		if (PINA != 0x00){
			LK_State = LK_LPressed_Wait;
		}
		else{
			LK_State = LK_Locked;
		}
		break;
	case  LK_LCheck:
		LK_State = LK_Unlocked;
		for (i = 0x00; i < 0x04; i=i+0x01){
			if (input[i] == 0x00){
				LK_State = LK_LPressed_Wait;
				break;
			}
			if (input[i] != key[i]){
				for (i = 0x00; i < 0x04; i=i+0x01){
					input[i] = 0x00;
				}
				index = 0x00;
				LK_State = LK_LPressed_Wait;
				break;
			}
		}
		if (index >= 4){
			for (i = 0x00; i < 0x04; i=i+0x01){
				input[i] = 0x00;
			}
			index = 0x00;
		}
		break;
	case LK_Unlocked:
		if ((PINA) != 0x00){
			LK_State = LK_ULPressed;
		}
		else{
			LK_State = LK_Unlocked;
		}
		break;
	case  LK_ULPressed:
		LK_State = LK_ULCheck;
		break;
	case LK_ULPressed_Wait:
		if (PINA != 0x00){
			LK_State = LK_ULPressed_Wait;
		}
		else{
			LK_State = LK_Unlocked;
		}
		break;
	case  LK_ULCheck:
		LK_State = LK_Locked;
		for (i = 0x00; i < 0x04; i = i + 0x01){
			if (input[i] == 0x00){
				LK_State = LK_ULPressed_Wait;
				break;
			}
			if (input[i] != key[i]){
				for (i = 0x00; i < 0x04; i = i + 0x01){
					input[i] = 0x00;
				}
				index = 0x00;
				LK_State = LK_ULPressed_Wait;
				break;
			}
		}
		if (index >= 4){
			for (i = 0x00; i < 0x04; i = i + 0x01){
				input[i] = 0x00;
			}
			index = 0x00;
		}
		break;

	}

	switch (LK_State){
	case LK_Locked:
		PORTB = 0x00;
		break;
	case LK_LPressed:
		input[index] = PINA;
		index = index + 0x01;
		LK_State = LK_LCheck;
		break;
	case LK_LCheck:

		break;
	case LK_Unlocked:
		PORTB = 0x01;
		break;

	case LK_ULPressed:
		input[index] = PINA;
		index = index + 0x01;
		LK_State = LK_ULCheck;
		break;
	default:
		
		break;
	}
	PORTC = LK_State;
}


int main(void)
{
    LK_State = LK_SMStart;
    index = 0x00;

   while(1) {
       
     TickFct_LK();
   }
   return 0;
}

