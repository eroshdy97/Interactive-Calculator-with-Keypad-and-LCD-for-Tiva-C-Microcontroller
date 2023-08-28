/*
  Author:      Ehab Roshdy
  Version:     0.1
  Date:        21/8/2023
  Description: LCD driver private file
*/

#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H

#include "LIB/STD_TYPES.h"

/* Declare static helper functions */
static void delayMs(uint32 delay);    /* Function to introduce a delay in milliseconds */
static void sendEnablePulse(void);              /* Function to send the enable pulse to the LCD */

/* Declare variables to store pin and port information */
static unsigned char DataPort; /* Port for data lines */
static unsigned char DataPins; /* Pins for data lines */
static unsigned char RSPort;   /* Port for Register Select (RS) line */
static unsigned char RSPin;    /* Pin for RS line */
static unsigned char ENPort;   /* Port for Enable (EN) line */
static unsigned char ENPin;    /* Pin for EN line */

#endif /* LCD_PRIVATE_H */
