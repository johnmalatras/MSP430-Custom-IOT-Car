//=========================================================================== 
// File Name : timers.c // 
// Description: This file initializes the timer and contains all timer functions // 
// Author: John Malatras // Date: February 2017 
// Compiler: Built with IAR Embedded Workbench Version 6.50.4 

//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

void Init_Timer_B1(void);

extern volatile char one_time;
extern volatile unsigned int five_msec_count;
extern volatile unsigned int Time_Sequence;
int right_reverse_rate;
int right_forward_rate;
int left_reverse_rate;
int left_forward_rate;
extern int timerCounter0;

//------------------------------------------------------------------------------
// Initialize Timers
// This function initializes the timers
// No local variables used
// No global variables used
//
// Each individual Timer function is called
//
// John Malatras
// Feb 2017
//-------------------------------------------------------------------------------
void Init_Timers(void){
//------------------------------------------------------------------------------
// Timer Configurations
//------------------------------------------------------------------------------
  Init_Timer_A0(); //
  Init_Timer_B1(); //
  Init_Timer_B2();   //  Required for provided compiled code to work
//------------------------------------------------------------------------------
}


//------------------------------------------------------------------------------
// Timer Code
// This function increases the timer count
// No local variables used
// Global variables used: Time_Sequence, one_time, five_msec_count
//
// Each individual Timer function is called
//
// John Malatras
// Feb 2017
//-------------------------------------------------------------------------------
void Timer_code(void){
//------------------------------------------------------------------------------
// Timer A0 interrupt code
//------------------------------------------------------------------------------
  Time_Sequence++;
  one_time = 1;
  if (five_msec_count < 1000){
    five_msec_count++;
  }
//------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
// five_msec_delay
// This function increases the five_msec_count variable
// Local variables used: fivemsec
// Global variables used: five_msec_count
//
// five_msec_count is increased in 5 ms increments
//
// John Malatras
// Feb 2017
//-------------------------------------------------------------------------------
void Five_msec_delay(unsigned int fivemsec){
//------------------------------------------------------------------------------
//Each count passed is at least x times 5 milliseconds
  five_msec_count = LOW;
  while(fivemsec > (five_msec_count+HIGH)){
    if (five_msec_count < TIMER_A0){
      five_msec_count++;
    }
  }
  int enterTime = timerCounter0;
  while (timerCounter0 - enterTime < 2);
//------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
// Initialize Timer A0
// This function initializes timers CCR0 and CCR1 
// No local variables used
// No global variables used
//
//
// John Malatras
// Feb 2017
//------------------------------------------------------------------------------
void Init_Timer_A0(void) {
  TA0CTL = TASSEL__SMCLK;       // SMCLK source
  TA0CTL |= TACLR;              // Resets TA0R, clock divider, count direction
  TA0CTL |= MC__CONTINOUS;      // Continuous up (previously 2)
  TA0CTL |= ID__2;              // Divide clock by 2
  TA0CTL &= ~TAIE;              // Disable Overflow Interrupt
  TA0CTL &= ~TAIFG;             // Clear Overflow Interrupt flag
  
  TA0EX0 = TAIDEX_7;            // Divide clock by an additional 8
  TA0CCR0 = TA0CCR0_INTERVAL;   // CCR0
  TA0CCTL0 |= CCIE;             // CCR0 enable interrupt
  
  //TA0EX1 = TAIDEX_7;            // Divide clock by an additional 8
  TA0CCR1 = TA0CCR1_INTERVAL;   // CCR0
  TA0CCTL1 |= CCIE;             // CCR0 enable interrupt
  // TA0CCR2 = TA0CCR2_INTERVAL; // CCR2
  // TA0CCTL2 |= CCIE; // CCR2 enable interrupt
}
//------------------------------------------------------------------------------

//left 
void Init_Timer_B1(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
// TB1.2 P3.5 R_FORWARD TB1.1 P3.4 R_REVERSE
// TB2.1 P3.6 L_FORWARD TB2.2 P3.7 L_REVERSE
//------------------------------------------------------------------------------
  TB1CTL = TBSSEL__SMCLK; // SMCLK
  TB1CTL |= MC_1; // Up Mode
  TB1CTL |= TBCLR; // Clear TAR
  left_reverse_rate = LOW; // Set Right Reverse Off P3.4
  left_forward_rate = LOW; // Set Right Forward Off P3.5
  TB1CCR0 = WHEEL_PERIOD; // PWM Period
  TB1CCTL1 = OUTMOD_7; // CCR1 reset/set
  TB1CCR1 = left_reverse_rate ; // P3.4 Right Reverse PWM duty cycle
  TB1CCTL2 = OUTMOD_7; // CCR2 reset/set
  TB1CCR2 = left_forward_rate ; // P3.5 Right Forward PWM duty cycle
//------------------------------------------------------------------------------
}

//right
void Init_Timer_B2(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
// TB1.2 P3.5 R_FORWARD TB1.1 P3.4 R_REVERSE
// TB2.1 P3.6 L_FORWARD TB2.2 P3.7 L_REVERSE
//------------------------------------------------------------------------------
  TB2CTL = TBSSEL__SMCLK; // SMCLK
  TB2CTL |= MC_1; // Up Mode
  TB2CTL |= TBCLR; // Clear TAR
  right_reverse_rate = LOW; // Set Right Reverse Off P3.4
  right_forward_rate = LOW; // Set Right Forward Off P3.5
  TB2CCR0 = WHEEL_PERIOD; // PWM Period
  TB2CCTL1 = OUTMOD_7; // CCR1 reset/set
  TB2CCR1 = right_reverse_rate ; // P3.4 Right Reverse PWM duty cycle
  TB2CCTL2 = OUTMOD_7; // CCR2 reset/set
  TB2CCR2 = right_forward_rate ; // P3.5 Right Forward PWM duty cycle
//------------------------------------------------------------------------------
}