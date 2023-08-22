/*
  Author:      Ehab Roshdy                                                                      
  Version:     0.1                                                                       
  Date:        21/8/2023                                                                             
  Description: GPIO driver program file    
*/

#include "./MCAL/GPIO/GPIO_interface.h"
#include "./MCAL/GPIO/GPIO_private.h"
#include "./MCAL/GPIO/GPIO_config.h"
//////////////////////////////////////////////////////////////////////////////////////////////

// Function to initialize GPIO port with specified input and output pins
void GPIO_Init_Port(unsigned char port, unsigned char inputPins, unsigned char outputPins)
{
    // Enable the clock for the specified GPIO port
    SYSCTL_RCGCGPIO_R |= (1 << port);

    // Wait until the GPIO port is ready for access
    while ((SYSCTL_PRGPIO_R & (1 << port)) == 0);

    // Calculate the base address of the GPIO port
    unsigned int base_address = ADDRESS_PORTN(port);

    // Unlock the GPIO port using the magic number (LOCK_R)
    (*((volatile unsigned long *)(base_address + 0x520))) = 0x4c4f434b;

    // Configure the pins as both input and output as specified (CR_R)
    (*((volatile unsigned long *)(base_address + 0x524))) = (inputPins | outputPins);

    // Set the pins as input by clearing their corresponding output bits (DIR_R)
    (*((volatile unsigned long *)(base_address + 0x400))) = ~(inputPins & ~outputPins);

    // Set the pins as output by setting their corresponding output bits (PUR_R)
    (*((volatile unsigned long *)(base_address + 0x510))) = (inputPins | outputPins);

    // Enable digitalization of input and output pins (DEN_R)
    (*((volatile unsigned long *)(base_address + 0x51C))) = (inputPins | outputPins);
}

// Function to read the value of specified pins on a GPIO port
char GPIO_Read_Pins(unsigned char port, unsigned char pins)
{
    // Read and return the value of the specified pins on the GPIO port
    return ((volatile unsigned long *)(ADDRESS_PORTN(port)))[pins];
}

// Function to write a value to specified pins on a GPIO port
void GPIO_Write_Pins(unsigned char port, unsigned char pins, unsigned char value)
{
    // Clear the specified pins' values by writing 0
    ((volatile unsigned long *)(ADDRESS_PORTN(port)))[pins] = 0;

    // Write the specified value to the pins on the GPIO port
    ((volatile unsigned long *)(ADDRESS_PORTN(port)))[pins] = value;
}
