//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  John Malatras
//  Jan 2017
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

// System variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
char led_smclk;
volatile char one_time;
volatile unsigned int five_msec_count;

// Display Variables
extern char display_line_1[ELEVEN_DISPLAY_LINE];
extern char display_line_2[ELEVEN_DISPLAY_LINE];
extern char display_line_3[ELEVEN_DISPLAY_LINE];
extern char display_line_4[ELEVEN_DISPLAY_LINE];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
char posL1;
char posL2;
char posL3;
char posL4;
char size_count;
char big;

// Main timer variable, incremented in interrupts
volatile unsigned int timerCounter0 = LOW;

// Debounce from switch presses
volatile unsigned int debounceCounter = LOW;

// Import receiving ring buffers to keep track of 
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_rd;
extern volatile unsigned int cpu_rx_ring_wr;
extern volatile unsigned int cpu_rx_ring_rd;

// flags and information on received text
extern int received;
extern char commandChar;
extern char inputString[SMALL_RING_SIZE];
extern unsigned int counter;
extern char saveflash;
extern char statuscheck;
extern char f;
extern char parsecommand;

// Black line following details
int circling = FALSE;
int Line_State = OFF_LEFT;
int initBlack = TRUE;

// Black line following values
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;
extern char adc_char_left[ADC_DISPLAY];
extern char adc_char_right[ADC_DISPLAY];
int lastOnTime = MAX_INT;
int keepCount = TRUE;

void main(void){
//------------------------------------------------------------------------------ 
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------

  // System initializations
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System
  Init_Conditions();
  Time_Sequence = ZERO_INIT_TIME_SEQUENCE; 
  Init_Timers();                            // Initialize Timers
  Init_LCD();                               // Initialize LCD
  Init_ADC();

  // Initialize Serial Ports with 9600 Baud
  Init_Serial_UCA0(BAUD_9600_1, BAUD_9600_2); 
  Init_Serial_UCA1(BAUD_9600_1, BAUD_9600_2);

  // Pause to let serial ports catch up
  Five_msec_delay(FIFTY_SLEEP_TIME);

  // Turn on IOT
  PJOUT |= IOT_RESET;

  // initialize IP and SSID placeholders
  char ipstring1[TEN_LENGTH] = "          ";
  char ipstring2[TEN_LENGTH] = "          ";
  char ssid[TEN_LENGTH] = "          ";

  // Flags and timer values
  int initTime = timerCounter0;
  char scanning = LOW;
  int blacklineTime = MAX_INT;
  int leftTime = MAX_INT;
  int postLeftTime = MAX_INT;
  int circleState = LOW;
  int circleTime = MAX_INT;

  // Turn on Infared detector and make sure wheels are off
  P3OUT |= IR_LED;
  Wheels_Off();

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {

    // Update IR detector values and check for line status 
    ADC_Process();
    Check_Line();
    
    // If serial text received from IOT, parse 
    if(parsecommand){ 

      // SSID flagged, parse and display   
      if((inputString[INDEX_6] == CHAR_2_ASCII) && (inputString[INDEX_7] == CHAR_5_ASCII)){
        ssid[LOW] = inputString[INDEX_32];
        ssid[HIGH] = inputString[INDEX_33];
        ssid[INDEX_2] = inputString[INDEX_34];
        ssid[INDEX_3] = inputString[INDEX_35];  
        //display_1 = ssid;
      }
    
      // IP flagged, parse and display 
      if((inputString[INDEX_6] == CHAR_2_ASCII) && (inputString[INDEX_7] == CHAR_4_ASCII)){
               
        ipstring1[LOW] = inputString[INDEX_17];
        ipstring2[LOW] = inputString[INDEX_24];
        ipstring1[INDEX_1] = inputString[INDEX_18];
        ipstring2[INDEX_1] = inputString[INDEX_25];
        ipstring1[INDEX_3] = inputString[INDEX_20];
        ipstring2[INDEX_3] = inputString[INDEX_27];
        ipstring1[INDEX_4] = inputString[INDEX_21];
        ipstring2[INDEX_4] = inputString[INDEX_28];
        ipstring1[INDEX_5] = inputString[INDEX_22];
        ipstring2[INDEX_5] = inputString[INDEX_29];

        display_1 = ipstring1;
        display_2 = ipstring2;
      }
    
      // If move command received and passcode = 1212, send relevant information to commandAction to execute
      if((inputString[LOW] == CHAR_DOT_ASCII) &&( inputString[HIGH] == CHAR_1_ASCII) && (inputString[INDEX_2] == CHAR_2_ASCII) && (inputString[INDEX_3] == CHAR_1_ASCII)&&( inputString[INDEX_4] == CHAR_2_ASCII)){
        int count = INDEX_4;

        // Loop through if multiple commands in same string
        do {
          commandAction(inputString[count + INDEX_1], inputString[count + INDEX_2]);
        }
        while(inputString[count += INDEX_3] == CHAR_DOT_ASCII);
      }
      
      // Update input string with null values
      parsecommand = LOW;
      f = LOW;
      int y = LOW;
      while(y < SMALL_RING_SIZE){
        inputString[y] = '\0';
        y++;
      }
    }

    // Update receiving ring buffer counters
    if (usb_rx_ring_wr != usb_rx_ring_rd) {
      usb_rx_ring_rd++;
      if (usb_rx_ring_rd >= SMALL_RING_SIZE) {
        usb_rx_ring_rd = BEGINNING;
      }
    }
    
    if (circling == TRUE) {

      // State machine for black line detecting/following
      switch (circleState) {

        // Slowly approach until black line is detected
        case LINE_CASE_0: {
          Left_Reverse(LOW);
          Right_Reverse(LOW);
          Right_Forward(TURN_SPEED);
          Left_Forward(TURN_SPEED);
          
          if (Line_State == ON_LINE) {
            circleState = LINE_CASE_1;
          }
          break;
        }

        // Stay on black line indefinitely
        case LINE_CASE_1: {        
          Right_Reverse(LOW);
          Left_Reverse(LOW);
                    
          switch (Line_State) {
            case LINE_UNKNOWN: {
              Left_Forward(TURN_SPEED);
              Right_Forward(LOW);
              break;
            }
          
            case ON_LINE: {
              Left_Forward(ON_LINE_SPEED);
              Right_Forward(ON_LINE_SPEED);
              initBlack = TRUE;
              break;
            }
          
            case DRIFT_RIGHT: {
              Left_Forward(LOW);
              Right_Forward(TURN_SPEED);
              break;
            }
          
            case DRIFT_LEFT: {
              Left_Forward(TURN_SPEED);
              Right_Forward(LOW);
              break;
            }
          }

        
          posL1 = LINE_1;

          break;
        }
      }
    }
    
    // Update display every half second and show millisecond counter if course still in progress
    if (timerCounter0 % DISPLAY_UPDATE == LOW) {
      if (keepCount == TRUE) {
        int mseconds = timerCounter0 * TIMER_DIVISOR;
        int length = snprintf( NULL, LOW, "%d", mseconds );
        snprintf( display_4, length + HIGH, "%d", mseconds );
        posL3 = LINE_1;
      }
      Display_Process();
    }
    
  }
//------------------------------------------------------------------------------
}

// Send character to A0 out serial port
void out_character_to_A0(char character){
//------------------------------------------------------------------------------
// The while loop will stall as long as the Flag is not set [port is busy]
 while (!(UCA0IFG & UCTXIFG)); // USCI_A0 TX buffer ready?
 UCA0TXBUF = character;
//------------------------------------------------------------------------------
}

// Send character to A1 out serial port
void out_character_to_A1(char character){
//------------------------------------------------------------------------------
// The while loop will stall as long as the Flag is not set [port is busy]
 while (!(UCA1IFG & UCTXIFG)); // USCI_A0 TX buffer ready?
 UCA1TXBUF = character;
//------------------------------------------------------------------------------
}

// Execute approprate command for input from IOT
void commandAction(char command, char time) {
  int enterTime = timerCounter0;
  int timeInt = (int)time - CHAR_0_ASCII;
  
  // Run for time specific in input
  while ((timerCounter0 - enterTime < (timeInt * SECOND_1))) {
    
    // Continue to update IR input values
    ADC_Process();
    Check_Line();
    
    // Display IR values for verification
    HEXtoBCD_LEFT(ADC_Left_Detector); 
    HEXtoBCD_RIGHT(ADC_Right_Detector);
    display_1 = adc_char_left;
    posL1 = LINE_1;
    display_2 = adc_char_right;
    posL2 = LINE_1;

    switch (command) {
      
      // Forward
      case 'F': {
        Right_Reverse(LOW);
        Left_Reverse(LOW);
        Right_Forward(MOVE_SPEED);
        Left_Forward(MOVE_SPEED);
        break;
      }
    
      // Reverse
      case 'B': {
        Right_Forward(LOW);
        Left_Forward(LOW);
        Left_Reverse(MOVE_SPEED);        
        Right_Reverse(MOVE_SPEED);
        break;
      }
    
      // Left Turn
      case 'R': {
        Left_Forward(LOW);
        Right_Reverse(LOW);
        Left_Reverse(LOW);
        Right_Forward(TURN_SPEED); 
        break;
      }
    
      // Right Turn
      case 'L': {
        Right_Forward(LOW);
        Right_Reverse(LOW);
        Left_Reverse(LOW);
        Left_Forward(TURN_SPEED);
        break;
      }
      
      // Stop
      case 'S': {
        Right_Forward(LOW);
        Right_Reverse(LOW);
        Left_Reverse(LOW);
        Left_Forward(LOW);
        break;
      }
      
      // Exit black line following with success
      case 'C': {
        Right_Reverse(LOW);
        Left_Reverse(LOW);
        Left_Forward(MOVE_SPEED);
        Right_Forward(MOVE_SPEED);
        keepCount = FALSE;
        circling = FALSE;
        display_1 = "FINISHED!";
        break;
      }
      
      // Exit black line following with failure
      case 'Z': {
        Right_Reverse(LOW);
        Left_Reverse(LOW);
        Left_Forward(MOVE_SPEED);
        Right_Forward(MOVE_SPEED);
        circling = FALSE;
        break;
      }
      
      // Set circling flag to initiate state machine in main while loop OS
      case 'A': {
        circling = TRUE;
        break;
      }
    
    }
  }

  // Turn off wheels as precaution
  Wheels_Off();
}

// Check IR inputs and set approprate blackline state
void Check_Line(void){ 
    if((ADC_Right_Detector > BLACKLINE_RIGHT) && (ADC_Left_Detector < BLACKLINE_LEFT)) {
      Line_State = DRIFT_LEFT;
    } 
    if ((ADC_Left_Detector > BLACKLINE_LEFT) && (ADC_Right_Detector < BLACKLINE_RIGHT)) {
      Line_State = DRIFT_RIGHT;
    } 
    if ((ADC_Left_Detector < BLACKLINE_LEFT) && (ADC_Right_Detector < BLACKLINE_RIGHT)) {
      Line_State=LINE_UNKNOWN;      
    }  
    if ((ADC_Left_Detector > BLACKLINE_LEFT) && (ADC_Right_Detector > BLACKLINE_RIGHT)) {
      Line_State = ON_LINE;
      lastOnTime = timerCounter0;
    }
}



