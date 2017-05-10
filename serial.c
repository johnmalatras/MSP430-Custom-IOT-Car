#include "macros.h"
#include "msp430.h"
#include "functions.h"

volatile unsigned int usb_rx_ring_wr;
volatile unsigned int usb_rx_ring_rd;
volatile unsigned int usb_tx_ring_wr;
volatile unsigned int usb_tx_ring_rd;
volatile unsigned int cpu_rx_ring_wr;
volatile unsigned int cpu_rx_ring_rd;
volatile unsigned int cpu_tx_ring_wr;
volatile unsigned int cpu_tx_ring_rd;
char USB_Char_Rx[SMALL_RING_SIZE];
char USB_Char_Rx_A1[SMALL_RING_SIZE];
volatile char USB_Char_Tx[SMALL_RING_SIZE];
char commandChar;
char inputString[SMALL_RING_SIZE];
extern unsigned int counter;
char saveflash = LOW;
char statuscheck = LOW;
char f = LOW;
char parsecommand = LOW;

//------------------------------------------------------------------------------
// Send/Receive Interrupts for A0 serial port
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
  unsigned int temp;
  switch(__even_in_range(UCA0IV, INTERRUPT_RANGE)){
    case INTERRUPT_CASE_0: // Vector 0 - no interrupt
      break;
    case INTERRUPT_CASE_2: // Vector 2 – RXIFG
      // code for Receive
      temp = usb_rx_ring_wr;
      UCA1TXBUF = UCA0RXBUF;
      USB_Char_Rx[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character 
      //UCA0TXBUF = USB_Char_Rx[temp];
      if (++usb_rx_ring_wr >= (SMALL_RING_SIZE)){
        usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
      } 
      break;
    case INTERRUPT_CASE_4: // Vector 4 – TXIFG
      // Code for Transmit
      break;
    default: break;
  }
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Send/Receive Interrupts for A1 serial port
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){
  unsigned int temp;
  switch(__even_in_range(UCA1IV,INTERRUPT_RANGE)){
    case INTERRUPT_CASE_0: // Vector 0 - no interrupt
      break;
    case INTERRUPT_CASE_2: // Vector 2 – RXIFG
      
      // Receiving from IOT
      temp = cpu_rx_ring_wr;
      USB_Char_Rx_A1[temp] = UCA1RXBUF; // RX -> USB_Char_Rx character
      UCA0TXBUF = USB_Char_Rx_A1[temp];
      
      if(USB_Char_Rx_A1[temp] == CHAR_PLUS_ASCII || USB_Char_Rx_A1[temp] == CHAR_DOT_ASCII){
         statuscheck = HIGH;
      }
       
      if((USB_Char_Rx_A1[temp] == '\n') || (USB_Char_Rx_A1[temp] == CHAR_CR_ASCII)){
        statuscheck = LOW;
        parsecommand = HIGH;   
      }
       
      if(statuscheck == HIGH){
        inputString[f] = UCA1RXBUF;
        f++;
      }
      
      if (++cpu_rx_ring_wr >= (SMALL_RING_SIZE)){
        cpu_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
      }
      break;
    case INTERRUPT_CASE_4: // Vector 4 – TXIFG
      // Code for Transmit
      break;
    default: break;
  }
}
//------------------------------------------------------------------------------

//----------------------------------------------------------------------------
void Init_Serial_UCA0(int baudBRW, int baudMCTLW){
  int i;
  for(i=LOW; i<SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = ZEROHEX; // USB Rx Buffer
  }
  usb_rx_ring_wr = BEGINNING;
  usb_rx_ring_rd = BEGINNING;

  usb_tx_ring_wr = BEGINNING;
  usb_tx_ring_rd = BEGINNING;
  // Configure UART 0
  UCA0CTLW0 = LOW; // Use word register
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 |= UCSWRST; // Set Software reset enable

  // 9,600 Baud Rate
  // 1. Calculate N = fBRCLK / Baudrate
  // N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
  // if N > 16 continue with step 3, otherwise with step 2
  // 2. OS16 = 0, UCBRx = INT(N)
  // continue with step 4
  // 3. OS16 = 1,
  // UCx = INT(N/16),
    // = INT(N/16) = 833.333/16 => 52
  // UCFx = INT([(N/16) – INT(N/16)] × 16)
    //= ([833.333/16-INT(833.333/16)]*16)
    //= (52.08333333-52)*16
    //= 0.083*16 = 1
  // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
  // Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
  // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14

  UCA0BRW = baudBRW; // 9,600 Baud

  // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
  // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;

  UCA0MCTLW = baudMCTLW ;
  UCA0CTL1 &= ~UCSWRST; // Release from reset
  UCA0IE |= UCRXIE; // Enable RX interrupt
}

//----------------------------------------------------------------------------
void Init_Serial_UCA1(int baudBRW, int baudMCTLW){
  int i;
  for(i=LOW; i<SMALL_RING_SIZE; i++){
    USB_Char_Rx_A1[i] = ZEROHEX; // USB Rx Buffer
  }
  cpu_rx_ring_wr = BEGINNING;
  cpu_rx_ring_rd = BEGINNING;

  cpu_tx_ring_wr = BEGINNING;
  cpu_tx_ring_rd = BEGINNING;
  // Configure UART 0
  UCA1CTLW0 = LOW; // Use word register
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA1CTLW0 |= UCSWRST; // Set Software reset enable

  // 115,200 Baud Rate
  // 1. Calculate N = fBRCLK / Baudrate
  // N = SMCLK / 115,200 => 8,000,000 / 115,200 = 69.4444
  // if N > 16 continue with step 3, otherwise with step 2
  // 2. OS16 = 0, UCBRx = INT(N)
  // continue with step 4
  // 3. OS16 = 1,
  // UCx = INT(N/16),
    // = INT(N/16) = 69.4444/16 => 4
  // UCFx = INT([(N/16) – INT(N/16)] × 16)
    //= 0.34028*16 = 5
  // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
  // Decimal of SMCLK / 8,000,000 / 115,200 = 69.4444 => 0.4444 yields 0x55 [Table]
  // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14

  UCA1BRW = baudBRW; // 9,600 Baud

  // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
  // UCA0MCTLW = 0x55 concatenate 5 concatenate 1;

  UCA1MCTLW = baudMCTLW ;
  UCA1CTL1 &= ~UCSWRST; // Release from reset
  UCA1IE |= UCRXIE; // Enable RX interrupt
}