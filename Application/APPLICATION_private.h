/*
  Author:      Ehab Roshdy                                                                      
  Version:     0.1                                                                       
  Date:        21/8/2023                                                                             
  Description: APPLICATION driver private file                                       
*/

#pragma once

#include "LIB/STD_TYPES.h"

#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))

static signed char inputArray[17];
static sint64 parsedNumbers[8];
static signed char parsedOperands[8];
static unsigned char intFlag;

void KeypadInterrupt(void);
static void parseInputString(void);
static float64 calculateResultWithPriority(void);
static void resetVariables(void);
static void trimFloat(char* str);
static void reverse(char* str, uint32 len);
static sint32 intToStr(sint64 x, char str[], sint32 d);
static void ftoa(const float64* n, char* res, sint32 afterpoint);
static void delayMs(uint32 delay);
