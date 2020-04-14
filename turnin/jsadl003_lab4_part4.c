/*	Author: jsadl003
 *      Partner(s) Name: Jason Sadler
 *	Lab Section: 21
 *	Assignment: Lab #4  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum LK_States {LK_SMStart, LK_Locked=1, LK_Unlocked=2, LK_Correct_Pressed=10, LK_Correct_1=11,LK_UCorrect_Pressed=20, LK_UCorrect_1=21 } LK_State;

void TickFct_LK()
{
  switch(LK_State) {   
    case LK_SMStart:
       LK_State = LK_Locked;
    break;
    case LK_Locked:
        if((PINA) == 0x04){
            LK_State = LK_Correct_Pressed;   
        }else{
            LK_State = LK_Locked;  
        }
    break;
    case  LK_Correct_Pressed:
        if(PINA == 0x04){
            LK_State = LK_Correct_Pressed; 
        }
        else if(PINA == 0x00){
            LK_State = LK_Correct_1;
        }
        else{
            LK_State = LK_Locked;   
        }
    break;
    case LK_Correct_1:
        if(PINA == 0x00){
            LK_State = LK_Correct_1;
        }
        else if(PINA == 0x02){
            LK_State = LK_Unlocked;   
        }else{
            LK_State = LK_Locked; 
        }
    break;
  case LK_Unlocked:
        if(PINA == 0x04){
            LK_State = LK_UCorrect_Pressed;
        }else{
            LK_State = LK_Unlocked;
        }
    break;
      case  LK_UCorrect_Pressed:
        if(PINA == 0x04){
            LK_State = LK_UCorrect_Pressed; 
        }
        else if(PINA == 0x00){
            LK_State = LK_UCorrect_1;
        }
        else{
            LK_State = LK_Unlocked;   
        }
    break;
    case LK_UCorrect_1:
        if(PINA == 0x00){
            LK_State = LK_UCorrect_1;
        }
        else if(PINA == 0x02){
            LK_State = LK_Locked;   
        }else{
            LK_State = LK_Unlocked; 
        }
    break;
    }
  switch(LK_State) { 
    case LK_Unlocked:
        PORTB = 0x01;
    break;
    case LK_Locked:
      PORTB = 0x00;
      break;
    default:
        
    break;
  }
  PORTC = LK_State;
}

int main(void){
    DDRA = 0x00; PORTA = 0x00; // Configure port A's 8 pins as inputs
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
   LK_State = LK_SMStart;
   while(1) {
      TickFct_LK();
   }
   return 0;
}
