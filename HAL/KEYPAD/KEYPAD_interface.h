/*
  Author:      Ehab Roshdy
  Version:     0.1
  Date:        21/8/2023
  Description: KEYPAD driver interface file
*/

#pragma once

/*
 * Function declaration for initializing the keypad.
 * This function sets up the necessary configurations to interface with the keypad hardware.
 * Parameters:
 * - rowPort: The port to which the keypad rows are connected.
 * - rowPins: The pins on the specified row port that correspond to the keypad rows.
 * - colPort: The port to which the keypad columns are connected.
 * - colPins: The pins on the specified column port that correspond to the keypad columns.
 */
void KeypadInit(unsigned char rowPort, unsigned char rowPins, unsigned char colPort, unsigned char colPins);

/*
 * Function declaration for getting a key press from the keypad.
 * This function checks the keypad and returns the character representing the key that was pressed.
 * Returns:
 * - A char representing the key pressed on the keypad.
 */
char KeypadGetKey(void);
