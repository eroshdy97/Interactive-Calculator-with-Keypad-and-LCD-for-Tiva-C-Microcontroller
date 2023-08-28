/*
  Author:      Ehab Roshdy
  Version:     0.1
  Date:        21/8/2023
  Description: LCD driver interface file
*/

#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

/* Function prototype for initializing the LCD module
 * Initializes the LCD module with specified configuration.
 * Arguments:
 *   dataPort: Data port for the LCD module.
 *   dataPins: Data pins connected to the LCD module.
 *   rsPort: Port where the Register Select (RS) pin is connected.
 *   rsPin: Specific pin number of the RS pin.
 *   enPort: Port where the Enable (EN) pin is connected.
 *   enPin: Specific pin number of the EN pin.
 */
void LcdInit(
    unsigned char dataPort,
    unsigned char dataPins,
    unsigned char rsPort,
    unsigned char rsPin,
    unsigned char enPort,
    unsigned char enPin
);

/* Function prototype for sending a command to the LCD module
 * Sends a command to configure the LCD module.
 * Argument:
 *   c: Command to be sent to the LCD module.
 */
void LcdSendCommand(char c);

/* Function prototype for sending data to the LCD module
 * Sends character data to be displayed on the LCD screen.
 * Argument:
 *   c: Character data to be sent to the LCD module.
 */
void LcdSendData(char c);

/* Function prototype for sending a string to the LCD module
 * Sends a sequence of characters (a string) to be displayed on the LCD screen.
 * Argument:
 *   str: Pointer to a char array (string) containing the data to be sent.
 */
void LcdSendString(const char* str);

#endif /* LCD_DRIVER_H */
