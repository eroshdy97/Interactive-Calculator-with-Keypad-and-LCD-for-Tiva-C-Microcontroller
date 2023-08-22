/*
  Author:      Ehab Roshdy                                                                      
  Version:     0.1                                                                       
  Date:        21/8/2023                                                                             
  Description: APPLICATION driver private file                                       
*/

#pragma once

#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))

static signed char inputArray[17];
static signed long long parsedNumbers[8];
static signed char parsedOperands[8];
static unsigned char intFlag = 0;

void KeypadInterrupt(void);
static void parseInputString();
static double calculateResultWithPriority();
static void resetVariables();
static void trimFloat(char* str);
static void reverse(char* str, int len);
static int intToStr(long long x, char str[], int d);
static void ftoa(double* n, char* res, int afterpoint);
static void delayMs(unsigned int delay);
