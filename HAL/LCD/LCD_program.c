/*
  Author:      Ehab Roshdy                                                                      
  Version:     0.1                                                                       
  Date:        21/8/2023                                                                             
  Description: LCD driver program file    
*/

#include "./HAL/LCD/LCD_interface.h"
#include "./HAL/LCD/LCD_private.h"
#include "./HAL/LCD/LCD_config.h"

#include "./MCAL/GPIO/GPIO_interface.h" // Include the header for GPIO control
//////////////////////////////////////////////////////////////////////////////////////////////

// Initialize the LCD module
void LcdInit(unsigned char dataPort, unsigned char dataPins, unsigned char rsPort, unsigned char rsPin, unsigned char enPort, unsigned char enPin)
{
    // Store the provided pin and port information in the corresponding variables
    DataPort = dataPort;
    DataPins = dataPins;
    RSPort = rsPort;
    RSPin = rsPin;
    ENPort = enPort;
    ENPin = enPin;

    // Initialize the data port pins for output
    GPIO_Init_Port(dataPort, 0, 0x3F);
    // Note: The initialization of RS and EN lines is currently commented out

    // Initialize the LCD module
    // Set up the 4-bit data communication
    GPIO_Write_Pins(dataPort, dataPins, 0x02); // Set 4-bit mode
    sendEnablePulse();

    // Send commands to configure the LCD
    LcdSendCommand(0x28); // Set display mode to 2 lines, 4-bit, 5x7 dot
    LcdSendCommand(0x06); // Set cursor increment mode, no display shift
    LcdSendCommand(0x0F); // Turn on display, cursor, and blinking
    LcdSendCommand(0x01); // Clear display
    // Note: The lines for moving the cursor and sending characters are currently commented out
}

// Send a data byte to the LCD
void LcdSendData(char c)
{
    GPIO_Write_Pins(RSPort, 1<<RSPin, (1<<RSPin)); // Set RS to indicate data

    // Send the higher 4 bits of the data
    GPIO_Write_Pins(DataPort, DataPins, c >> 4);
    sendEnablePulse();

    // Send the lower 4 bits of the data
    GPIO_Write_Pins(DataPort, DataPins, (c & 0x0F));
    sendEnablePulse();
}

// Send a command byte to the LCD
void LcdSendCommand(char c)
{
    GPIO_Write_Pins(RSPort, 1<<RSPin, (0<<RSPin)); // Clear RS to indicate command

    // Send the higher 4 bits of the command
    GPIO_Write_Pins(DataPort, DataPins, c >> 4);
    sendEnablePulse();

    // Send the lower 4 bits of the command
    GPIO_Write_Pins(DataPort, DataPins, (c & 0x0F));
    sendEnablePulse();
}

// Send a string of characters to the LCD
void LcdSendString(char* str)
{
    int i = 0;
    for (i = 0; str[i]; ++i)
    {
        LcdSendData(str[i]);
    }
}

// Function to introduce a delay in milliseconds
static void delayMs(unsigned int delay)
{
    int i, j;
    for (i = 0; i < delay; i++)
        for (j = 0; j < 3180; j++){} // Delay
}

// Function to send the enable pulse to the LCD
static void sendEnablePulse()
{
    GPIO_Write_Pins(ENPort, 1<<ENPin, (1<<ENPin)); // Set EN to high
    delayMs(2); // Delay for stability
    GPIO_Write_Pins(ENPort, 1<<ENPin, (0<<ENPin)); // Set EN to low
    delayMs(2); // Delay for stability
}
