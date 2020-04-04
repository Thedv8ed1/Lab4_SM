/*	Author: jsadl003
 *      Partner(s) Name: Jason Sadler
 *	Lab Section: 21
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

   // DDRA = 0x00; PORTA = 0x00; // Configure port A's 8 pins as inputs
   // DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s

enum LA_States { LA_SMStart, LA_B0_ON, LA_B1_ON, LA_B0_B1, LA_B1_B0 } LA_State;

void TickFct_Latch()
{
  switch(LA_State) {   
     case LA_SMStart:  
        LA_State = LA_B0_ON;
        break;

     case LA_B0_ON:
        if (!(PINA&0x01)) { 
           LA_State = LA_B0_ON;
        }
        else if (PINA&0x01) {
           LA_State = LA_B0_B1;
        }
        break;
    case LA_B0_B1:
        if ((PINA&0x01)) { 
           LA_State = LA_B0_B1;
        }
        else if (!(PINA&0x01)) {
           LA_State = LA_B1_ON;
        }
        break;
     case LA_B1_ON:
        if (!(PINA&0x01)) { 
           LA_State = LA_B1_ON;
        }
        else if ((PINA&0x01)) {
           LA_State = LA_B1_B0;
        }
        break;
    case LA_B1_B0:
        if ((PINA&0x01)) { 
           LA_State = LA_B1_B0;
        }
        else if (!(PINA&0x01)) {
           LA_State = LA_B0_ON;
        }
        break;
     default:
        LA_State = LA_SMStart;
        break;
  } // Transitions

  switch(LA_State) {   // State actions
     case LA_SMStart:  
        
        break;

     case LA_B0_ON:
        PORTB = 0x01;
        break;
    case LA_B0_B1:
        PORTB = 0x02;
        break;
     case LA_B1_ON:
        PORTB = 0x02;
        break;
    case LA_B1_B0:
        PORTB = 0x01;
        break;
     default:
        break;
   } // State actions
}

int main(void){
    DDRA = 0x00; PORTA = 0x00; // Configure port A's 8 pins as inputs
    DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
    LA_State = LA_SMStart; // Indicates initial call

   while(1) {
      TickFct_Latch();
   }
   return 0;
}
