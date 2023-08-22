/*
  Author:      Ehab Roshdy
  Version:     0.1
  Date:        21/8/2023
  Description: GPIO driver interface file
*/

#pragma once

// Function prototype to initialize a GPIO port with specific input and output pins
// Parameters:
//   port: The GPIO port number to initialize
//   inputPins: A bitmask representing the input pins to initialize
//   outputPins: A bitmask representing the output pins to initialize
void GPIO_Init_Port(unsigned char port, unsigned char inputPins, unsigned char outputPins);

// Function prototype to read the state of specific pins from a given GPIO port
// Parameters:
//   port: The GPIO port number to read from
//   pins: A bitmask representing the pins to read
// Returns:
//   A char value where each bit represents the state of a corresponding pin
char GPIO_Read_Pins(unsigned char port, unsigned char pins);

// Function prototype to write a value to specific pins of a given GPIO port
// Parameters:
//   port: The GPIO port number to write to
//   pins: A bitmask representing the pins to write to
//   value: The value (usually 0 or 1) to write to the pins
void GPIO_Write_Pins(unsigned char port, unsigned char pins, unsigned char value);
