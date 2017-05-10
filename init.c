//=========================================================================== 
// File Name : init.c // 
// Description: This file initializes conditions, LED's and contains the display_process function // 
// Author: John Malatras // Date: February 2017 
// Compiler: Built with IAR Embedded Workbench Version 6.50.4 

//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

extern char display_line_1[ELEVEN_DISPLAY_LINE];
extern char display_line_2[ELEVEN_DISPLAY_LINE];
extern char display_line_3[ELEVEN_DISPLAY_LINE];
extern char display_line_4[ELEVEN_DISPLAY_LINE];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;

//------------------------------------------------------------------------------
// Function Name: Init_Conditions
//
// Description: This function enables interrupts and ties the address of 
//              the display pointers to their respective strings. 
//
// Passed: No variables passed
// Locals: No Local variables
// Globals: No Global variables used
//
//  Author: John Malatras
//  Date: Feb 2017
//------------------------------------------------------------------------------
void Init_Conditions(void){
//------------------------------------------------------------------------------
// Initializations Configurations
//------------------------------------------------------------------------------
// Interrupts are disabled by default, enable them.
  enable_interrupts();
  display_1 = &display_line_1[ZERO_DISPLAY_LINE];
  display_2 = &display_line_2[ZERO_DISPLAY_LINE];
  display_3 = &display_line_3[ZERO_DISPLAY_LINE];
  display_4 = &display_line_4[ZERO_DISPLAY_LINE];

//------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
// Function Name: Init_LEDs
//
// Description: This initializes the states of all 8 LED's to off.
//
// Passed: No variables passed
// Locals: No Local variables
// Globals: No Global variables used
//
//  Author: John Malatras
//  Date: Feb 2017
//------------------------------------------------------------------------------
void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on all 8 LEDs
  PJOUT &= ~LED1;
  PJOUT &= ~LED2;
  PJOUT &= ~LED3;
  PJOUT &= ~LED4;
  P3OUT &= ~LED5;
  P3OUT &= ~LED6;
  P3OUT &= ~LED7;
  P3OUT &= ~LED8;
//------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
// Function Name: Display_Process
//
// Description: This function passes the information to the LCD_out
//
// Passed: No variables passed
// Locals: No Local variables
// Globals: display_1, display_2, display_3, display_4, posL1, posL2, posL3, posL4
//
//  Author: John Malatras
//  Date: Feb 2017
//------------------------------------------------------------------------------
void Display_Process(void){
  ClrDisplay();
  lcd_out(display_1, LCD_HOME_L1, posL1);
  lcd_out(display_2, LCD_HOME_L2, posL2);
  lcd_out(display_3, LCD_HOME_L3, posL3);
  lcd_out(display_4, LCD_HOME_L4, posL4);
}

//------------------------------------------------------------------------------
// Configure ADC10_B
void Init_ADC(void){
  ADC10CTL0 = ZEROHEX;          // Clear ADC10CTL0
  ADC10CTL0 |= ADC10SHT_2;      // 16 ADC clocks
  ADC10CTL0 &= ~ADC10MSC;       // Single Sequence
  ADC10CTL0 |= ADC10ON;         // ADC ON - Core Enabled
  ADC10CTL1 = ZEROHEX;          // Clear ADC10CTL1
  ADC10CTL1 |= ADC10SHS_0;      // ADC10SC bit
  ADC10CTL1 |= ADC10SHP;        // SAMPCON signal sourced from sampling timer
  ADC10CTL1 &= ~ADC10ISSH;      // The sample-input signal is not inverted.
  ADC10CTL1 |= ADC10DIV_0;      // ADC10_B clock divider – Divide by 1.
  ADC10CTL1 |= ADC10SSEL_0;     // MODCLK
  ADC10CTL1 |= ADC10CONSEQ_0;   // Single-channel, single-conversion
  ADC10CTL2 = ZEROHEX;          // Clear ADC10CTL2
  ADC10CTL2 |= ADC10DIV_0;      // Pre-divide by 1
  ADC10CTL2 |= ADC10RES;        // 10-bit resolution
  ADC10CTL2 &= ~ADC10DF;        // Binary unsigned
  ADC10CTL2 &= ~ADC10SR;        // supports up to approximately 200 ksps
  ADC10MCTL0 = ZEROHEX;         // Clear ADC10MCTL0
  ADC10MCTL0 |= ADC10SREF_0;    // V(R+) = AVCC and V(R-) = AVSS
  ADC10MCTL0 |= ADC10INCH_3;    // Channel A3 Thumb Wheel
  ADC10IE |= ADC10IE0;          // Enable ADC conversion complete interrupt
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void ADC_Process(void){
 while (ADC10CTL1 & BUSY); // Wait if ADC10 core is active
 ADC10CTL0 |= ADC10ENC + ADC10SC; // Sampling and conversion start
}
//------------------------------------------------------------------------------