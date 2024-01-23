// Piano.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// There are four keys in the piano
// Daniel Valvano
// December 29, 2014

// Port E bits 3-0 have 4 piano keys

#include "Piano.h"
#include "..//tm4c123gh6pm.h"


// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){
	volatile unsigned long  delay;	
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;     // 1) activate clock for Port E
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTE_CR_R |= 0x0F;           // 2) allow changes to PF4-0
  // only PE3-0 needs to be unlocked, other bits can't be locked
  GPIO_PORTE_AMSEL_R &= ~0x0F;        // 3) disable analog on PE
  GPIO_PORTE_PCTL_R &= ~0x0000FFFF;   // 4) PCTL GPIO on PE3-0
  GPIO_PORTE_DIR_R &= ~0x0F;          // 5) PF3-0 input
  GPIO_PORTE_AFSEL_R &= ~0x0F;        // 6) disable alt funct on PE7-0
  GPIO_PORTE_PDR_R |= 0x0F;          // enable pull-down on PE3-0
  GPIO_PORTE_DEN_R |= 0x0F;          // 7) enable digital I/O on PE3-0
}


// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){
  unsigned long key = GPIO_PORTE_DATA_R&0xF;
	if(key == 0x01)
		return 1;
	else if (key == 0x02)
		return 2;
	else if (key == 0x04)
		return 3;
	else if (key == 0x08)
		return 4;
	else
		return 0;
}
//---------------------Delay10ms---------------------
// wait 10ms for switches to stop bouncing
// Input: none
// Output: none
void Delay10ms(void){unsigned long volatile time;
  time = 14545;  // 10msec
  while(time){
		time--;
  }
}
