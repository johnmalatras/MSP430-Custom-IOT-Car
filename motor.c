//------------------------------------------------------------------------------
#include "macros.h"
#include "msp430.h"
#include "functions.h"

void Left_Off(void);
void Right_Off(void);

//------------------------------------------------------------------------------
//TB2CCR1 = Right Forward
//TB2CCR2 = Right Reverse
//TB1CCR2 = Left Forward
//TB1CCR1 = Left Reverse

void Wheels_Off(void) {
  Left_Off();
  Right_Off();
}

void Left_Off(void) {
  TB1CCR1 = LOW;
  TB1CCR2 = LOW;
}

void Right_Off(void) {
  TB2CCR2 = LOW;
  TB2CCR1 = LOW;
}

void Right_Forward(int amount) {
  TB2CCR1 = amount;
}

void Left_Forward(int amount) {
  TB1CCR2 = amount;
}

void Left_Reverse(int amount){
  TB1CCR1 = amount;
}

void Right_Reverse(int amount){
  TB2CCR2 = amount;
}

  
  

