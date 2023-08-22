/*
  Author:      Ehab Roshdy                                                                      
  Version:     0.1                                                                       
  Date:        21/8/2023                                                                             
  Description: KEYPAD driver program file    
*/

#include "./HAL/KEYPAD/KEYPAD_interface.h"
#include "./HAL/KEYPAD/KEYPAD_private.h"
#include "./HAL/KEYPAD/KEYPAD_config.h"

#include "./MCAL/GPIO/GPIO_interface.h"   // Include the GPIO module interface header
//////////////////////////////////////////////////////////////////////////////////////////////

// Initialize the keypad with specified ports and pins for columns and rows
void KeypadInit(unsigned char rowPort, unsigned char rowPins, unsigned char colPort, unsigned char colPins)
{
    ColPort = colPort;            // Store column port information
    ColPins = colPins;            // Store column pin information
    RowPort = rowPort;            // Store row port information
    RowPins = rowPins;            // Store row pin information

    // Initialize columns as outputs and set them to high
    GPIO_Init_Port(ColPort, ColPins, 0);   // columns 0x0f

    // Initialize rows as outputs and set them to high
    GPIO_Init_Port(RowPort, 0, RowPins); // rows 0x0f

    // Set all row pins to low
    GPIO_Write_Pins(RowPort, RowPins, 0x00);
}

// Get the pressed key from the keypad
char KeypadGetKey()
{
    unsigned char row = 0;
    unsigned char col = 0;

    // Iterate through each row
    for (row = 0; row < 4; ++row)
    {
        // Set all row pins to high except the current row
        GPIO_Write_Pins(RowPort, 0x0F, ~(1 << row));

        // Iterate through each column
        for (col = 0; col < 4; ++col)
        {
            // Read the state of the column pin
            unsigned char val = GPIO_Read_Pins(ColPort, (1 << col));

            // Check if the column pin is low (indicating a key press)
            if ((val & (1 << col)) == 0)
            {
                // Clear row pins and return the corresponding key character
                GPIO_Write_Pins(RowPort, RowPins, 0x00);
                return keypadMap[row][col];
            }
        }
    }

    // Clear row pins and return 0 if no key is pressed
    GPIO_Write_Pins(RowPort, RowPins, 0x00);
    return 0;
}
