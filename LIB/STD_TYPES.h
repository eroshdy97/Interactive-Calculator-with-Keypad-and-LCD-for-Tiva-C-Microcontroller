#pragma once

typedef unsigned char       uint8;
typedef signed char         sint8;
typedef unsigned short      uint16;
typedef signed short        sint16;
typedef unsigned int        uint32;
typedef signed int          sint32;
typedef unsigned long long  uint64;
typedef signed long long    sint64;

typedef float               float32;
typedef double              float64;
typedef long double         float128;

typedef unsigned char       bool;
#define true                (1)
#define false               (0)

/* Bit manipulation macros */
#define SET_BIT(reg, bit)     ((reg) |= (1U << (bit)))
#define CLEAR_BIT(reg, bit)   ((reg) &= ~(1U << (bit)))
#define TOGGLE_BIT(reg, bit)  ((reg) ^= (1U << (bit)))
#define GET_BIT(reg, bit)     (((reg) >> (bit)) & 1U)

/* Maximum and minimum values for fixed-width types */
#define INT8_MIN      (-128)
#define INT8_MAX       127
#define UINT8_MAX      255
#define INT16_MIN     (-32768)
#define INT16_MAX      32767
#define UINT16_MAX     65535
#define INT32_MIN     (-2147483647 - 1)
#define INT32_MAX      2147483647
#define UINT32_MAX     4294967295U
#define INT64_MIN     (-9223372036854775807LL - 1)
#define INT64_MAX      9223372036854775807LL
#define UINT64_MAX     18446744073709551615ULL

/* Macro to calculate the number of elements in an array */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/* Define constants for port names */
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

/*******************************************************************************/

/* Define constants for pin positions within a port */
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

/*******************************************************************************/

/* Define constants for digital logic levels */
#define HIGH 1
#define LOW 0

/*******************************************************************************/

/* Define constants for LED pin positions and their indices */
#define LED_RED_PIN 0x02
#define LED_BLUE_PIN 0x04
#define LED_GREEN_PIN 0x08

#define LED_RED_PIN_INDEX 1
#define LED_BLUE_PIN_INDEX 2
#define LED_GREEN_PIN_INDEX 3

/*******************************************************************************/

/* Define constants for switch pin positions and their indices */
#define SWITCH_1_PIN 0x10
#define SWITCH_2_PIN 0x01

#define SWITCH_1_PIN_INDEX 4
#define SWITCH_2_PIN_INDEX 0
