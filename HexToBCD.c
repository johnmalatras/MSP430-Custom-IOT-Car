#include "macros.h"
#include "msp430.h"
#include "functions.h"

char adc_char[ADC_DISPLAY];
char adc_char_left[ADC_DISPLAY];
char adc_char_right[ADC_DISPLAY];
char iroff[ADC_DISPLAY];
char whitevalue[ADC_DISPLAY];
char blackvalue[ADC_DISPLAY];
int state;
extern char *display_3;
extern char *display_4;


//-----------------------------------------------------------------------------
// Hex to BCD Conversion for Thumbwheel
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//------------------------------------------------------------------------------
void HEXtoBCD(int hex_value){
  int value;
  adc_char[FIRST_ADC_DIGIT] = '0';
  adc_char[SECOND_ADC_DIGIT] = '0';
  adc_char[THIRD_ADC_DIGIT] = '0';
  adc_char[FOURTH_ADC_DIGIT] = '0';
  
  if (hex_value > HEX_MAX){
    hex_value = hex_value - HEX_MAX;
    adc_char[FIRST_ADC_DIGIT] = '1';
  }
  value = LOW;
  while (hex_value > HEX_MAX_TWO){
    hex_value = hex_value - HEX_MAX_TWO_SHIFT;
    value = value + ONE;
    adc_char[SECOND_ADC_DIGIT] = PLACE_VALUE + value;
  }
  value = LOW;
  while (hex_value > HEX_MAX_THREE){
    hex_value = hex_value - HEX_MAX_THREE_SHIFT;
    value = value + ONE;
    adc_char[THIRD_ADC_DIGIT] = PLACE_VALUE + value;
  }
  adc_char[FOURTH_ADC_DIGIT] = PLACE_VALUE + hex_value;
  
}

//------------------------------------------------------------------------------
// HEX to Decimal for Left Detector 
//--------------------------------------------------------------------------
void HEXtoBCD_LEFT(int hex_value){
  
  int value;
  adc_char_left[FIRST_ADC_DIGIT] = '0';
  adc_char_left[SECOND_ADC_DIGIT] = '0';
  adc_char_left[THIRD_ADC_DIGIT] = '0';
  adc_char_left[FOURTH_ADC_DIGIT] = '0';
  
  if (hex_value > HEX_MAX){
    hex_value = hex_value - HEX_MAX;
    adc_char_left[FIRST_ADC_DIGIT] = '1';
  }
  value = LOW;
  while (hex_value > HEX_MAX_TWO){
    hex_value = hex_value - HEX_MAX_TWO_SHIFT;
    value = value + ONE;
    adc_char_left[SECOND_ADC_DIGIT] = PLACE_VALUE + value;
  }
  value = LOW;
  while (hex_value > HEX_MAX_THREE){
    hex_value = hex_value - HEX_MAX_THREE_SHIFT;
    value = value + ONE;
    adc_char_left[THIRD_ADC_DIGIT] = PLACE_VALUE + value;
  }
  adc_char_left[FOURTH_ADC_DIGIT] = PLACE_VALUE + hex_value;
}

//------------------------------------------------------------------------------
// HEX to Decimal for Right Detector
//------------------------------------------------------------------------------
void HEXtoBCD_RIGHT(int hex_value){
  
  int value;
  adc_char_right[FIRST_ADC_DIGIT] = '0';
  adc_char_right[SECOND_ADC_DIGIT] = '0';
  adc_char_right[THIRD_ADC_DIGIT] = '0';
  adc_char_right[FOURTH_ADC_DIGIT] = '0';
  
  if (hex_value > HEX_MAX){
    hex_value = hex_value -HEX_MAX;
    adc_char_right[FIRST_ADC_DIGIT] = '1';
  }
  value = LOW;
  
  while (hex_value > HEX_MAX_TWO){
    hex_value = hex_value - HEX_MAX_TWO_SHIFT;
    value = value + ONE;
    adc_char_right[SECOND_ADC_DIGIT] = PLACE_VALUE + value;
  }
  value = LOW;
  
  while (hex_value > HEX_MAX_THREE){
    hex_value = hex_value - HEX_MAX_THREE_SHIFT;
    value = value + ONE;
    adc_char_right[THIRD_ADC_DIGIT] = PLACE_VALUE + value;
  }
  adc_char_right[FOURTH_ADC_DIGIT] = PLACE_VALUE + hex_value;
}