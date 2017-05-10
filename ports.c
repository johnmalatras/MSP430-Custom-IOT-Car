//=========================================================================== 
// File Name : ports.c // 
// Description: This file initializes the ports 
// Author: John Malatras // Date: February 2017 
// Compiler: Built with IAR Embedded Workbench Version 6.50.4 
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_PortJ(void);

//------------------------------------------------------------------------------
// Init Ports
// This function calls the functions to initialize each individual port
// No local variables used
// No global variables used
//
// John Malatras
// Feb 2017
//------------------------------------------------------------------------------
void Init_Ports(void) {
	Init_Port1();
  Init_Port2();
  Init_Port3();
  Init_Port4();
  Init_PortJ();
}


//------------------------------------------------------------------------------
// Initialize Port 1
// This function initializes each pin in Port 1
// No local variables used
// No global variables used
//
// Pin 0 Select 0 -> Voltage from Right Detector, Pin 0 Select 1 -> Voltage from Right Detector
// Pin 1 Select 0 -> Voltage from Left Detector, Pin 0 Select 1 -> Voltage from Left Detector
// Pin 2 Select 0 -> Not of Control Signal for LCD_BACKLITE, Pin 0 Select 1 -> Not of Control Signal for LCD_BACKLITE, Direction = output, output = 1
// Pin 3 Select 0 -> Voltage from Thumb Wheel, Pin 0 Select 1 -> Voltage from Thumb Wheel
// Pin 4 Select 0 -> Not of LCD Chip Select, Pin 0 Select 1 -> Not of LCD Chip Select, Direction = output, output = 0
// Pin 5 Select 0 -> Not of LCD Reset, Pin 0 Select 1 -> Not of LCD Reset, Direction = output, output = 0
// Pin 6 Select 0 -> Not of slave in/master out, Pin 0 Select 1 -> slave in/master out, Direction = output
// Pin 7 Select 0 -> slave out/master in, Pin 0 Select 1 -> slave out/master in, Direction = output, enable pullup resistor
//
// John Malatras
// Feb 2017
//------------------------------------------------------------------------------
void Init_Port1(void) {
// Configure Port 1-------------------------------------------------------------
// V_DETECT_R                   (0x01) // Voltage from Right Detector
// V_DETECT_L                   (0x02) // Volage from Left Detector
// LCD_BACKLITE                 (0x04) // Control Signal for LCD_BACKLITE
// V_THUMB                      (0x08) // Voltage from Thumb Wheel
// SPI_CS_LCD                   (0x10) // LCD Chip Select
// RESET_LCD                    (0x20) // LCD Reset
// SIMO_B                       (0x40) // SPI mode - slave in/master out of USCI_B0
// SOMI_B                       (0x80) // SPI mode - slave out/master in of USCI_B0
//------------------------------------------------------------------------------
  P1SEL0 = ZEROHEX;                // P1 set as I/O
  P1SEL1 = ZEROHEX;                // P1 set as I/O
  P1DIR = ZEROHEX;                 // Set P1 direction to input

  P1SEL0 |= V_DETECT_R;         // V_DETECT_R selected
  P1SEL1 |= V_DETECT_R;         // V_DETECT_R selected

  P1SEL0 |= V_DETECT_L;         // V_DETECT_L selected
  P1SEL1 |= V_DETECT_L;         // V_DETECT_L selected

  P1SEL0 &= ~LCD_BACKLITE;      // LCD_BACKLITE GPI/O selected
  P1SEL1 &= ~LCD_BACKLITE;      // LCD_BACKLITE GPI/O selected
  P1OUT |= LCD_BACKLITE ;       // LCD_BACKLITE Port Pin set low
  P1DIR |= LCD_BACKLITE ;       // Set LCD_BACKLITE direction to output

  P1SEL0 |= V_THUMB;            // V_THUMB selected
  P1SEL1 |= V_THUMB;            // V_THUMB selected

  P1SEL0 &= ~SPI_CS_LCD;        // SPI_CS_LCD GPI/O selected
  P1SEL1 &= ~SPI_CS_LCD;        // SPI_CS_LCD GPI/O selected
  P1OUT |= SPI_CS_LCD;          // SPI_CS_LCD Port Pin set high
  P1DIR |= SPI_CS_LCD;          // Set SPI_CS_LCD output direction
   
  P1SEL0 &= ~RESET_LCD;         // RESET_LCD GPI/O selected
  P1SEL1 &= ~ RESET_LCD;        // RESET_LCD GPI/O selected
  P1OUT &= ~ RESET_LCD;         // RESET_LCD Port Pin set low
  P1DIR |= RESET_LCD;           // Set RESET_LCD output direction

  P1SEL0 &= ~SIMO_B;            // SIMO_B selected
  P1SEL1 |= SIMO_B;             // SIMO_B selected
  P1DIR |= SIMO_B;              // SIMO_B set to Output
  P1SEL0 &= ~SOMI_B;            // SOMI_B is used on the LCD

  P1SEL1 |= SOMI_B;             // SOMI_B is used on the LCD
  P1OUT |= SOMI_B;              // SOMI_B Port Pin set for Pull-up
  P1DIR &= ~SOMI_B;             // SOMI_B set to Input
  P1REN |= SOMI_B;              // Enable pullup resistor
//------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
// Initialize Port 2
// This function initializes each pin in Port 2
// No local variables used
// No global variables used
//
// Pin 0 Select 0 -> not of slave in/master out, Pin 0 Select 1 -> slave out/master in, Direction = output, output = 0
// Pin 1 Select 0 -> not of slave out/master in, Pin 0 Select 1 -> slave out/master in, Direction = input, enable pullup resistor
// Pin 2 Select 0 -> not of clock signal input, Pin 0 Select 1 -> clock signal input, Direction = output, output = 1
// Pin 3 Select 0/Select 1 -> UNKNOWN
// Pin 4 Select 0/Select 1 -> UNKNOWN
// Pin 5 Select 0 -> Not of Transmit Data, Pin 0 Select 1 -> Transmit Data, Direction = output, output = 0
// Pin 6 Select 0 -> Not of Receive Data, Pin 0 Select 1 -> Receive Data, Direction = output, output = 0, enable pullup resistor
// Pin 7 Select 0/Select 1 -> UNKNOWN
//
// John Malatras
// Feb 2017
//------------------------------------------------------------------------------
void Init_Port2(void){
//------------------------------------------------------------------------------
//Configure Port 2
// Port 2 Pins
// USB_TXD                     (0x01) // Slave in, master out – eUSCI_A0 SPI mode
// USB_RXD                     (0x02) // Slave out, master in – eUSCI_A0 SPI mode
// SPI_SCK                     (0x04) // Clock signal input – eUSCI_B0 SPI slave mode, Clock signal output – eUSCI_B0 SPI master mode
// UNKNOWN                     (0x08) //
// UNKNOWN                     (0x10) //
// CPU_TXD                     (0x20) // Transmit data – eUSCI_A1 UART mode, Slave in, master out – eUSCI_A1 SPI mode (not available on devices without UCSI_A1)
// CPU_RXD                     (0x40) // Receive data – eUSCI_A1 UART mode, Slave out, master in – eUSCI_A1 SPI mode (not available on devices without UCSI_A1)
// UNKNOWN                     (0x80) //
//------------------------------------------------------------------------------
  P2SEL0 = ZEROHEX;                // P2 set as I/0
  P2SEL1 = ZEROHEX;                // P2 set as I/0
  P2DIR = ZEROHEX;                 // set P2 direction to input
  
  P2SEL0 &= ~USB_TXD;           // USB_TXD selected
  P2SEL1 |= USB_TXD;            // USB_TXD selected
  P2DIR |= USB_TXD;             // USB_TXD Port Pin set high
  P2OUT &= ~USB_TXD;            // Set USB_TXD output direction
  
  P2SEL0 &= ~USB_RXD;           // USB_RXD selected
  P2SEL1 |= USB_RXD;            // USB_RXD selected
  P2DIR |= USB_RXD;             // USB_RXD Port Pin set high
  P2OUT &= ~USB_RXD;            // Set USB_RXD direction
  P2REN &= ~USB_RXD;            // Set USB_RXD resistor
  
  P2SEL0 &= ~SPI_SCK;           // SPI_SCK selected
  P2SEL1 |= SPI_SCK;            // SPI_SCK selected
  P2DIR |= SPI_SCK;             // SPI_SCK Port Pin set Low
  P2OUT |= SPI_SCK;             // Set SPI_SCK direction
  
  P2SEL0 &= ~UNKNOWN_1;         // UNKNOWN GP/O selected
  P2SEL1 &= ~UNKNOWN_1;         // UNKNOWN GP/O selected
  P2DIR &= ~UNKNOWN_1;          // UNKNOWN Port Pin set Low
  P2REN &= ~UNKNOWN_1;          // Disable pullup resistor
  
  P2SEL0 &= ~UNKNOWN_2;         // UNKNOWN GP/O selected
  P2SEL1 &= ~UNKNOWN_2;         // UNKNOWN GP/O selected
  P2DIR &= ~UNKNOWN_2;          // UNKNOWN Port Pin set Low
  P2REN &= ~UNKNOWN_2;          // Disable pullup resistor
  
  P2SEL0 &= ~CPU_TXD;           // CPU_TXD selected
  P2SEL1 |= CPU_TXD;            // CPU_TXD selected
  P2DIR |= CPU_TXD;             // CPU_TXD Port Pin set high
  P2OUT &= ~CPU_TXD;            // Set CPU_TXD direction
  
  P2SEL0 &= ~CPU_RXD;           // CPU_RXD selected
  P2SEL1 |= CPU_RXD;            // CPU_RXD selected
  P2DIR |= CPU_RXD;             // CPU_RXD Port Pin set high
  P2OUT &= ~CPU_RXD;            // Set CPU_RXD direction
  P2REN &= ~CPU_RXD;            // Enable pullup resistor
  
  P2SEL0 &= ~UNKNOWN_3;         // UNKNOWN GP/O selected
  P2SEL1 &= ~UNKNOWN_3;         // UNKNOWN GP/O selected
  P2DIR &= ~UNKNOWN_3;          // UNKNOWN Port Pin set Low
  P2REN &= ~UNKNOWN_3;          // Disable pullup resistor
  
  
//------------------------------------------------------------------------------
}


//------------------------------------------------------------------------------
// Initialize Port 3
// This function initializes each pin in Port 3
// No local variables used
// No global variables used
//
// Pin 0 Select 0 -> not of Accelerometer Y-axis, Pin 0 Select 1 -> Not of Accelerometer Y-axis, Direction = input, output = 0
// Pin 1 Select 0 -> not of Accelerometer Y-axis, Pin 0 Select 1 -> Not of Accelerometer Y-axis, Direction = input, output = 0
// Pin 2 Select 0 -> not of Accelerometer Y-axis, Pin 0 Select 1 -> Not of Accelerometer Y-axis, Direction = input, output = 0
// Pin 3 Select 0 -> Not of Lightning LED, Pin 0 Select 1 -> Not of Lightning LED, Direction = output, output = 0
// Pin 4 Select 0 -> Not of Right Motor Reverse, Pin 0 Select 1 -> Not of Right Motor Reverse, Direction = output, output = 0
// Pin 5 Select 0 -> Not of Right Motor Forward, Pin 0 Select 1 -> Not of Right Motor Forward, Direction = output, output = 0
// Pin 6 Select 0 -> Not of Left Motor Forward, Pin 0 Select 1 -> Not of Left Motor Forward, Direction = output, output = 0
// Pin 7 Select 0 -> Not of Left Motor Reverse, Pin 0 Select 1 -> Not of Left Motor Reverse, Direction = output, output = 0
//
// John Malatras
// Feb 2017
//------------------------------------------------------------------------------
void Init_Port3(void){
//------------------------------------------------------------------------------
//Configure Port 3
// Port 3 Pins
// X                            (0x01) // Accelerometer X-axis
// Y                            (0x02) // Accelerometer Y-axis
// Z                            (0x04) // Accelerometer Z-axis
// IR_LED                       (0x08) // Lighting LED
// R_REVERSE                    (0x10) // Right Motor Reverse
// R_FORWARD                    (0x20) // Right Motor Forward
// L_FORWARD                    (0x40) // Left Motor Forward
// L_REVERSE                    (0x80) // Left Motor Reverse
//------------------------------------------------------------------------------
  P3SEL0 = ZEROHEX;                // P3 set as I/0
  P3SEL1 = ZEROHEX;                // P3 set as I/0
  P3DIR = ZEROHEX;                 // Set P3 direction to input
  
  
  P3SEL0 &= ~XL_X;              // X GP/O selected
  P3SEL1 &= ~XL_X;              // X GP/O selected
  P3DIR  &= ~XL_X;              // X Port pin set low
  P3REN  &= ~XL_X;              // Disable pullup Resistor
  
  P3SEL0 &= ~XL_Y;              // Y GP/O selected
  P3SEL1 &= ~XL_Y;              // Y GP/O selected
  P3DIR  &= ~XL_Y;              // Y Port pin set low
  P3REN  &= ~XL_Y;              // Disable pullup Resistor
  
  P3SEL0 &= ~XL_Z;              // Z GP/O selected
  P3SEL1 &= ~XL_Z;              // Z GP/O selected
  P3DIR  &= ~XL_Z;              // Y Port pin set low
  P3REN  &= ~XL_Z;              // Disable pullup Resistor
  
  P3SEL0 &= ~IR_LED;            // IR_LED GP/O selected
  P3SEL1 &= ~IR_LED;            // IR_LED GP/O selected
  P3DIR  |= IR_LED;             // IR_LED port pin set high
  P3OUT  &= ~IR_LED;            // Set IR_LED output direction
  
  P3SEL0 |= R_REVERSE;         // R_REVERSE GP/O selected
  P3SEL1 &= ~R_REVERSE;         // R_REVERSE GP/O selected
  P3DIR  |= R_REVERSE;          // R_REVERSE port pin set high
  //P3OUT  &= ~R_REVERSE;         // set R_REVERSE output direction
  
  P3SEL0 |= R_FORWARD;        // R_FORWARD GP/O selected
  P3SEL1 &= ~R_FORWARD;         // R_FORWARD GP/O selected
  P3DIR  |= R_FORWARD;          // R_FORWARD port pin set high
  //P3OUT  &= ~R_FORWARD;         // Set R_FORWARD output direction
  
  P3SEL0 |= L_FORWARD;        // L_FORWARD GP/O selected
  P3SEL1 &= ~L_FORWARD;         // L_FORWARD GP/O selected
  P3DIR  |= L_FORWARD;          // L_FORWARD port pin set high
  //P3OUT  &= ~L_FORWARD;         // Set L_FORWARD output direction
  
  P3SEL0 |= L_REVERSE;        // L_REVERSE GP/O selected
  P3SEL1 &= ~L_REVERSE;         // L_REVERSE GP/O selected
  P3DIR  |= L_REVERSE;          // L_REVERSE port pin set high
  //P3OUT  &= ~L_REVERSE;         // Set L_REVERSE output direction
  
//------------------------------------------------------------------------------
}


//------------------------------------------------------------------------------
// Initialize Port 4
// This function initializes each pin in Port 4
// No local variables used
// No global variables used
//
// Pin 0 Select 0 -> not of Switch 1, Pin 0 Select 1 -> Not of Switch 1, Direction = input, set pullup resistor, set Hi/Lo edge interrupt
// Pin 1 Select 0 -> not of Switch 2, Pin 0 Select 1 -> Not of Switch 2, Direction = input, set pullup resistor, set Hi/Lo edge interrupt
//
// John Malatras
// Feb 2017
//------------------------------------------------------------------------------
void Init_Port4(void){
  //----------------------------------------------------------------------------------
  // Configure PORT 4
  // Port 4 has only two pins 
  // Port 4 Pins
  // SW1                        (0x01) // Switch 1
  // SW2                        (0x02) // Switch 2
  //----------------------------------------------------------------------------------
  P4SEL0 = ZEROHEX;                // P4 set as I/O
  P4SEL1 = ZEROHEX;                // P4 set as I/O
  P4DIR = ZEROHEX;                 // Set P4 direction to input
  P4OUT = ZEROHEX;
  
// SW1
  P4SEL0 &= ~SW1;               // SW1 set as I/O
  P4SEL1 = ~SW1;                // SW1 set as I/O                 
  P4OUT |= SW1;                 // Configure pullup resistor
  P4DIR &= ~SW1;                // Direction = input
  P4REN |= SW1;                 // Enable pullup resistor
  P4IES |= SW1;                 // SW1 Hi/Lo edge interrupt
  P4IFG &= ~SW1;                // IFG SW1 cleared
  P4IE |= SW1;                  // SW1 interrupt Enabled
  
// SW2
  P4SEL0 &= ~SW2;               // SW2 set as I/O
  P4SEL1 &= ~SW2;               // SW2 set as I/0
  P4OUT |= SW2;                 // Configure pullup resistor
  P4DIR &= ~SW2;                // Direction = input
  P4REN |= SW2;                 // Enable pullup resistor
  P4IES |= SW2;                 // SW2 Hi/Lo edge interrupt
  P4IFG &= ~SW2;                // IFG SW2 cleared
  P4IE |= SW2;                  // SW2 interrupt enabled
//------------------------------------------------------------------------------
}


//------------------------------------------------------------------------------
// Initialize Port J
// This function initializes each pin in Port J
// No local variables used
// No global variables used
//
// Pin 0 Select 0 -> not of LED 5, Pin 0 Select 1 -> Not of LED 5, Direction = output, output = 0
// Pin 1 Select 0 -> not of LED 6, Pin 0 Select 1 -> Not of LED 6, Direction = output, output = 0
// Pin 2 Select 0 -> not of LED 7, Pin 0 Select 1 -> Not of LED 7, Direction = output, output = 0
// Pin 3 Select 0 -> not of LED 8, Pin 0 Select 1 -> Not of LED 8, Direction = output, output = 0
// Pin 4 Select 0 -> not of LED 5, Pin 0 Select 1 -> Not of LED 5, Direction = output, output = 0
// John Malatras
// Feb 2017
//------------------------------------------------------------------------------
void Init_PortJ(){ 
//------------------------------------------------------------------------------
// Port J Pins
// LED1 (0x01) // LED 5
// LED2 (0x02) // LED 6
// LED3 (0x04) // LED 7
// LED4 (0x08) // LED 8
// XINR (0x10) // XINR
// XOUTR (0x20) // XOUTR
//------------------------------------------------------------------------------
  PJSEL0 = ZEROHEX;       // PJ set as GP I/0 or SMCLK pin
  PJSEL1 = ZEROHEX;       // PJ set as GP I/0 or SMCLK pin
  PJDIR = ZEROHEX;        // Set PJ direction to output

  PJSEL0 &= ~IOT_WAKEUP;
  PJSEL1 &= ~IOT_WAKEUP;
  PJDIR  |= IOT_WAKEUP;
  PJOUT &= ~IOT_WAKEUP;
  
  PJSEL0 &= ~IOT_FACTORY;
  PJSEL1 &= ~IOT_FACTORY;
  PJOUT &= ~IOT_FACTORY;
  PJDIR |=  IOT_FACTORY; 

  PJSEL0 &= ~IOT_STA_MINIAP;
  PJSEL1 &= ~IOT_STA_MINIAP;
  PJOUT |=   IOT_STA_MINIAP;
  PJDIR |=   IOT_STA_MINIAP;

  PJSEL0 &= ~IOT_RESET;
  PJSEL1 &= ~IOT_RESET;
  PJOUT  &= ~IOT_RESET;
  PJDIR  |=  IOT_RESET;
  
  PJSEL0 &= ~IOT_BOOT;
  PJSEL1 &= ~IOT_BOOT;
  PJOUT &= ~IOT_BOOT; 
  PJDIR |= IOT_BOOT;
  
//------------------------------------------------------------------------------
}
