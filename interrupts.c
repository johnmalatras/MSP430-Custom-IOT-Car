//===========================================================================
// File Name : interrupts.c
//
// Description: This file contains the interupt service routines
//
// Author: John Malatras
// Date: Feb 2017
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================

#include "macros.h"
#include "msp430.h"
#include "functions.h"
extern int timerCounter0;
extern int debounceCounter;
int SW1pressed;
int SW2pressed;
int SW1debounce;
int SW2debounce;
int SW1debounce_reset;
int SW2debounce_reset;
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;
volatile unsigned int ADC_Thumb;
volatile unsigned int ADC_Counter;
volatile unsigned int ADC_Right_Detector;
volatile unsigned int ADC_Left_Detector;
unsigned int rightDetector;
unsigned int leftDetector;
extern char adc_char[ADC_DISPLAY];
extern char adc_char_left[ADC_DISPLAY];
extern char adc_char_right[ADC_DISPLAY];
extern char USB_Char_Rx[SMALL_RING_SIZE];
int showMessage = FALSE;

char ncsu[] = "NCSU  #1";
char baud1[] = "9,600";
char baud2[] = "115,200";



//------------------------------------------------------------------------------
// Interrupt for Timer A0 CCR0
// This function is hit every 50ms. It checks if the blackline sensor is on and displays them if so. 
// It also checks for patterns in the two sensors to determine direction of movement
// No local variables used
// Global Variables used: timerCounter0
//
//
// John Malatras
// Feb 2017
//------------------------------------------------------------------------------
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
    timerCounter0++; 

    TA0CCR0 += TA0CCR0_INTERVAL; // Add Offset to TACCR1
}
//----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Interrupt for Port 4
// This function is hit when Switch 1 and 2 are pressed, they increment counters to allow for debounce
// No local variables used
// Global Variables used: display_3, display_4, posL3, posL4
//
//
// John Malatras
// Feb 2017
//------------------------------------------------------------------------------
#pragma vector=PORT4_VECTOR
__interrupt void switch_interrupt(void){
  //Switch 1
  if (P4IFG & SW1){
    SW1pressed = HIGH; // verify SW1 pressed
    SW1debounce = HIGH; // identify SW1 is being debounced
    SW1debounce_reset = LOW; // Resets the count required for the debounce
    P4IE &= ~SW1;  // SW1 interrupt disabled
    TA0CTL &= ~TAIFG; // Clears any current timer interrupt
    
    // Do stuff here
    
  }
  
  //Switch 2
  if (P4IFG & SW2){
    SW2pressed = HIGH; // verify SW2 pressed
    SW2debounce = HIGH; // indentify SW2 is being debounced
    SW2debounce_reset = LOW; // reset the count required for the debounce
    P4IE &= ~SW2;  // SW2 interrupt disabled
    TA0CTL &= ~TAIFG; // Clears any current timer interrupt
    
    // Do stuff here
    

  }
   TA0CCTL1 |= CCIE; //CCR0 enable interrupt
}


//------------------------------------------------------------------------------
// Interrupt for Timer A0 CCR1
// This function is hit every 50ms, and debounces any button clicks
// No local variables used
// Global Variables used: debounceCounter, SW1debounce, SW1debounce_reset, W1debounce, SW1debounce_reset,
//
//
// John Malatras
// Feb 2017
//------------------------------------------------------------------------------
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){
  debounceCounter++;
  if (SW1debounce == HIGH){
    SW1debounce_reset++;
    P4IFG &= ~SW1;
    P3OUT &= ~LCD_BACKLITE;
    P4IFG &= ~SW1;
  }
  if (SW2debounce == HIGH) {
    SW2debounce_reset++;
    P4IFG &= ~SW2;
    P3OUT &= ~LCD_BACKLITE;
    P4IFG &= ~SW2;
  }
  if (SW1debounce_reset> DEBOUNCE_LIMIT) {
    P4IE |= SW1;
    SW1debounce_reset = LOW;
    if (SW2debounce_reset == LOW) {
      P3OUT |= LCD_BACKLITE;
    }
    SW1debounce = FALSE;
  }
  if (SW2debounce_reset > DEBOUNCE_LIMIT) {
    P4IE |= SW2;
    SW2debounce_reset = LOW;
    if (SW1debounce == LOW) {
      P3OUT |= LCD_BACKLITE;
    }
    SW2debounce = FALSE;
  }
  if (SW1debounce_reset == LOW && SW2debounce_reset == LOW) {
    TA0CCTL1 &= ~CCIE;
  }
  TA0CCR1 += TA0CCR1_INTERVAL; // Add Offset to TACCR1
}
//----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ADC10 interrupt service routine
// ADC_Right_Detector; // A00 ADC10INCH_0 - P1.0
// ADC_Left_Detector; // A01 ADC10INCH_1 - P1.1
// ADC_Thumb; // A03 ADC10INCH_3 - P1.3
// ADC_Temp; // A10 ADC10INCH_10 – Temperature REF module
// ADC_Bat; // A11 ADC10INCH_11 - Internal
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
  switch(__even_in_range(ADC10IV,12)) {
    case OVERFLOW_CASE_0: break;        // No interrupt
    case OVERFLOW_CASE_2: break;        // conversion result overflow
    case OVERFLOW_CASE_4: break;        // conversion time overflow
    case OVERFLOW_CASE_6: break;        // ADC10HI
    case OVERFLOW_CASE_8: break;        // ADC10LO
    case OVERFLOW_CASE_10: break;       // ADC10IN
    case OVERFLOW_CASE_12:
      ADC10CTL0 &= ~ADC10ENC ; // Turn off the ENC bit of the ADC10CTL0
      switch (ADC_Counter){
        case LEFT_CASE:
          ADC10MCTL0 = ADC10INCH_1; // Next channel A1
          ADC_Left_Detector = ADC10MEM0; // Current Channel result for A0
          ADC_Counter ++;
          break;
        case RIGHT_CASE:
          ADC10MCTL0 = ADC10INCH_3; // Next channel A3
          ADC_Right_Detector = ADC10MEM0; // Current Channel result for A1
          ADC_Counter ++;
          break;
        case THUMB_CASE:
          ADC10MCTL0 = ADC10INCH_0; // Next channel A0
          ADC_Thumb = ADC10MEM0; // Current Channel result for A3
          ADC_Counter = LOW;
          break;
        default:
          break;
      }
      ADC10CTL0 |= ADC10ENC; // Turn on the ENC bit of the ADC10CTL0
      ADC10CTL0 |= ADC10SC; // Start next sample.
      break;
    default:
      break;
  }
}
//------------------------------------------------------------------------------