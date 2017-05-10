// Required defines

// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define CNTL_STATE_INDEX        (3) // Control States
#define LED1                 (0x01) // LED 1
#define LED2                 (0x02) // LED 2
#define LED3                 (0x04) // LED 3
#define LED4                 (0x08) // LED 4
#define LED5                 (0x10) // LED 5
#define LED6                 (0x20) // LED 6
#define LED7                 (0x40) // LED 7
#define LED8                 (0x80) // LED 8
#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2
#define CNTL_STATE_INDEX        (3)
#define ELEVEN_DISPLAY_LINE  (11)
#define ZERO_INIT_TIME_SEQUENCE                    (0)
#define FIFTY_SLEEP_TIME                   (50)
#define ONE_LINE_POS                     (1)
#define TWO_LINE_POS                     (2)
#define THREE_LINE_POS                   (3)
#define TIME_SEQ_CASE_250       (250)
#define TIME_SEQ_CASE_200       (200)
#define TIME_SEQ_CASE_150       (150)
#define TIME_SEQ_CASE_100       (100)
#define TIME_SEQ_CASE_50       (50)
#define ZERO_ONE_TIME           (0)
#define ZERO_SIZE_COUNT         (0)
#define FIVE_SIZE_COUNT         (5)
#define ONE_BIG                 (1)
#define ZERO_BIG                (0)
#define ZERO_DISPLAY_LINE       (0)
#define HIGH                    (1)
#define LOW                     (0)
#define LINE_3 3
#define LINE_1 1
#define LINE_2 2
#define LINE_4 4
#define MAX_INT                 (2147483647)

// LCD
#define LCD_HOME_L1              0x80
#define LCD_HOME_L2             0xA0
#define LCD_HOME_L3             0xC0
#define LCD_HOME_L4             0xE0

// From Ports.c
#define ZEROHEX              (0x00)

  // P1
#define V_DETECT_R           (0x01) //
#define V_DETECT_L           (0x02) //
#define LCD_BACKLITE         (0x04) //
#define V_THUMB              (0x08) //
#define SPI_CS_LCD           (0x10) //
#define RESET_LCD            (0x20) //
#define SIMO_B               (0x40) //
#define SOMI_B               (0x80) //

// P2
#define USB_TXD              (0x01) //
#define USB_RXD              (0x02) //
#define SPI_SCK (0x04) //
#define UNKNOWN_1            (0x08) //
#define UNKNOWN_2            (0x10) //
#define CPU_TXD              (0x20) //
#define CPU_RXD              (0x40) //
#define UNKNOWN_3            (0x80) //

// P3
#define XL_X                 (0x01) //
#define XL_Y (0x02) //
#define XL_Z                 (0x04) //
#define IR_LED (0x08) //
#define R_REVERSE            (0x10) //
#define R_FORWARD            (0x20) //
#define L_FORWARD            (0x40) //
#define L_REVERSE            (0x80) //

// Port J Pins
#define XINR                 (0x10) // XINR
#define XOUTR                (0x20) // XOUTR
#define CLEAR_REGISTER     (0X0000)
#define USE_IOT_WAKEUP		(0x00)
#define USE_SMCLK			(0x01)

//Switch Check
#define TRUE  (0x01)
#define FALSE (0x00)

//Timer Debounce
#define TA0CCR0_INTERVAL (25000) 
#define TA0CCR1_INTERVAL (25000)
#define DEBOUNCE_LIMIT   (1000)
#define TIMER_A0 1000

// Interrupts
#define DISPLAY_UPDATE	 (10)
#define SECOND_1         (20)
#define SECOND_2         (40)
#define SECOND_3         (60)
#define SECOND_4         (80)
#define SECOND_5         (100)
#define SECOND_6         (120)
#define SECOND_7         (140)
#define SECOND_8         (160)
#define SECOND_9         (180)
#define SECOND_10        (200)
#define SECOND_11        (220)
#define OVERFLOW_CASE_0         (0)
#define OVERFLOW_CASE_2         (2)
#define OVERFLOW_CASE_4         (4)
#define OVERFLOW_CASE_6         (6)
#define OVERFLOW_CASE_8         (8)
#define OVERFLOW_CASE_10         (10)
#define OVERFLOW_CASE_12         (12)


// ADC
#define ADC_DISPLAY (10)
#define FIRST_ADC_DIGIT (0)
#define SECOND_ADC_DIGIT (1)
#define THIRD_ADC_DIGIT (2)
#define FOURTH_ADC_DIGIT (3)
#define HEX_MAX (1000)
#define HEX_MAX_TWO (99)
#define HEX_MAX_TWO_SHIFT (100)
#define HEX_MAX_THREE (9)
#define HEX_MAX_THREE_SHIFT (10)
#define PLACE_VALUE (0x30)
#define ONE 1
#define RESET_STATE (0)
#define LEFT_CASE (0x00)
#define RIGHT_CASE (0x01)
#define THUMB_CASE (0x02)
#define BLACKLINE_RIGHT (400)
#define BLACKLINE_LEFT (175)


// PWM
#define WHEEL_PERIOD (4000)

//Circling
#define LINE_UNKNOWN (-1)
#define ON_LINE         (0)
#define DRIFT_RIGHT     (1)
#define DRIFT_LEFT      (2)
#define OFF_RIGHT       (3)
#define OFF_LEFT        (4)
#define INIT_TURN       (5)
#define NULL 0L

// serial
#define BEGINNING (0)
#define SMALL_RING_SIZE (64)
#define BAUD_9600_1     (52)
#define BAUD_9600_2     (0x4911)
#define BAUD_115200_1   (4)
#define BAUD_115200_2   (0x5551)
#define INTERRUPT_RANGE (0x08)
#define INTERRUPT_CASE_0        (0)
#define INTERRUPT_CASE_2        (2)
#define INTERRUPT_CASE_4        (4)

// IOT
#define IOT_WAKEUP           (0x00) 
#define IOT_FACTORY          (0x02) 
#define IOT_STA_MINIAP       (0x04) 
#define IOT_RESET            (0x08) 
#define IOT_BOOT             (0x01) 
#define TEN_LENGTH           (10)
#define INDEX_1              (1)
#define INDEX_2              (2)
#define INDEX_3              (3)
#define INDEX_4              (4)
#define INDEX_5              (5)
#define INDEX_6              (6)
#define INDEX_7              (7)
#define INDEX_17              (17)
#define INDEX_24              (24)
#define INDEX_18              (18)
#define INDEX_25              (25)
#define INDEX_20              (20)
#define INDEX_27              (27)
#define INDEX_21              (21)
#define INDEX_28              (28)
#define INDEX_22              (22)
#define INDEX_29              (29)
#define INDEX_32              (32)
#define INDEX_33              (33)
#define INDEX_34              (34)
#define INDEX_35              (35)
#define INDEX_36              (36)
#define CHAR_0_ASCII         (48)
#define CHAR_3_ASCII         (0x33)
#define CHAR_2_ASCII         (0x32)
#define CHAR_1_ASCII         (0x31)
#define CHAR_4_ASCII         (0x34)
#define CHAR_5_ASCII         (0x35)
#define CHAR_DOT_ASCII         (0x2E)
#define CHAR_PLUS_ASCII         (0x2B)
#define CHAR_CR_ASCII         (0x0D)

// Project 10
#define MOVE_SPEED			(3000)
#define TURN_SPEED			(1400)
#define TIMER_DIVISOR		(5)
#define ON_LINE_SPEED		(1600)
#define LINE_CASE_0			(0)
#define LINE_CASE_1			(1)


