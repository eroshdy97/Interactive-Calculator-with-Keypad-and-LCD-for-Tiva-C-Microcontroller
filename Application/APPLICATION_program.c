/*
  Author:      Ehab Roshdy
  Version:     0.1
  Date:        21/8/2023
  Description: APPLICATION driver program file
*/

#include "./APPLICATION/APPLICATION_interface.h"
#include "./APPLICATION/APPLICATION_private.h"
#include "./APPLICATION/APPLICATION_config.h"

#include "./LIB/STD_TYPES.h"
#include "./HAL/KEYPAD/KEYPAD_interface.h"
#include "./HAL/LCD/LCD_interface.h"
/*****************************************************************************************/

void Application(void)
{
    /* Initialize keypad and LCD */
    KeypadInit(PORTD, 0x0F, PORTE, 0x0F);  /* Initialize the keypad on PORTD with rows 0-3 and PORTE with columns 0-3 */
    LcdInit(PORTB, 0x0F, PORTB, PIN4, PORTB, PIN5);  /* Initialize the LCD on PORTB, with data pins on PIN4 and PIN5 */

    /* Configure keypad interrupt settings */
    GPIO_PORTE_IS_R &= ~(0x0F << 0);   /* Configure PORTE as edge-sensitive for keypad interrupt */
    GPIO_PORTE_IBE_R &= ~(0x0F << 0);  /* Disable both edges interrupt for keypad */
    GPIO_PORTE_IEV_R &= ~(0x0F << 0);  /* Set the interrupt event to trigger on falling edge */
    GPIO_PORTE_IM_R |= (0x0F << 0);    /* Enable interrupt masks for the keypad columns (0-3) */

    NVIC_EN0_R |= (1U << 4U);            /* Enable interrupt 4 in the NVIC (GPIO Port E) */
    __asm(" CPSIE i ");                /* Enable global interrupts (interrupts are allowed) */

    /* Reset application variables */
    resetVariables();                  /* Call the function to reset various application-related variables */

    char KeypadReading = 0;            /* Variable to store the currently pressed keypad key */
    char inputArrayIndex = 0;          /* Index for storing key presses in inputArray */
    uint8 isComplete = 0;      /* Flag indicating if the current input is complete */
    intFlag = 0;
    /* Main loop of the application */
    while (1)
    {
        if (intFlag)
        {
            delayMs(50);                    /* Introduce a delay to debounce the keypad */
            KeypadReading = KeypadGetKey(); /* Read the currently pressed key from the keypad */
            intFlag = 0;                    /* Clear the interrupt flag */

            /* Process keypad input */
            if (KeypadReading == 'R')
            {
                /* Clear the LCD display and reset variables */
                LcdSendCommand(0x40);     /* Set DDRAM address to 0 (start of 1st line) */
                LcdSendCommand(0x01);     /* Clear the display */
                resetVariables();         /* Call the function to reset variables */
                inputArrayIndex = 0;      /* Reset the inputArrayIndex */
                isComplete = 0;           /* Reset the isComplete flag */
            }
            else if (KeypadReading && !isComplete)
            {
                LcdSendData(KeypadReading);  /* Display the pressed key on the LCD */
                inputArray[inputArrayIndex] = KeypadReading;  /* Store the key in inputArray */
                inputArrayIndex++;

                if (KeypadReading == '=' || inputArrayIndex > 15)
                {
                    /* Calculate and display result when '=' is pressed or input is full */
                    inputArrayIndex = 0;  /* Reset inputArrayIndex */
                    parseInputString();   /* Call the function to parse the input string */
                    float64 res = calculateResultWithPriority();  /* Calculate the result of the expression */

                    char outputResult[16] = {0};  /* Initialize an array to store the result string */
                    ftoa(&res, outputResult, 5);  /* Convert the result to a string */
                    trimFloat(outputResult);  /* Remove unnecessary zeros from the result string */

                    LcdSendCommand(0xC0);  /* Set DDRAM address to 40 (start of 2nd line) */
                    LcdSendString(outputResult);  /* Display the result on the LCD */

                    inputArrayIndex = 0;   /* Reset inputArrayIndex */
                    isComplete = 1;        /* Set isComplete flag to indicate completion */
                }
            }
            else{}

            KeypadReading = 0;  /* Clear the KeypadReading variable */
        }  /* End of if(intFlag) */
    }  /* End of while(1) */
}  /* End of Application function */

/*****************************************************************************************/

void KeypadInterrupt(void)
{
    intFlag = 1;                   /* Set the interrupt flag to indicate an interrupt has occurred */
    GPIO_PORTE_ICR_R |= 0x0F;      /* Clear the interrupt flags on specific bits of GPIO Port E */
}

/*****************************************************************************************/

static void parseInputString(void)
{
    uint32 left = 0;               /* Index for the left boundary of the current substring */
    uint32 right = 0;              /* Index for the right boundary of the current substring */
    uint8 opCounter = 0;           /* Counter for the number of parseduint8 */
    uint8 numCounter = 0;          /* Counter for the number of parsed numbers */

    while (right < 17)  /* Process up to the 17th element of inputArray */
    {
        if (inputArray[right] >= '0' && inputArray[right] <= '9' && right < 17)
        {
            right++;  /* Move the right boundary to the right while parsing digits */
        }
        else
        {
            uint64 val = 0;

            /* Convert the substring from left to right to an integer value */
            while (left < right)
            {
                val = val * 10 + (inputArray[left] - '0');  /* Convert ASCII to numerical value */
                left++;  /* Move the left boundary to the right */
            }

            /* Store the parsed number */
            parsedNumbers[numCounter] = val;
            numCounter++;
            if (inputArray[right] == '=')
            {
                break;  /* Exit the loop if '=' is encountered */
            }

            /* Store the parsed operand and move boundaries to the right */
            parsedOperands[opCounter] = inputArray[right];
            opCounter++;
            right++;
            left++;
        }
    }
}

static float64 calculateResultWithPriority(void)
{
    uint8 i = 0;
    float64 orderedNumbers[8];
    signed char orderedOperators[8];

    /* Initialize arrays to store ordered numbers and operators */
    for(i = 0; i < 8; ++i)
    {
        orderedNumbers[i] = -1.0;         /* Initialize orderedNumbers with -1 */
        orderedOperators[i] = -1;       /* Initialize orderedOperators with -1 */
    }

    uint8 c = 0;
    i = (uint8)0;

    /* First pass: Order and process numbers and operators */
    for (i = 0; (i < 8) && (parsedNumbers[i] != -1); ++i)
    {
        if(parsedNumbers[i] != -2)  /* If parsedNumber is not a placeholder */
        {
            switch (parsedOperands[i])
            {
                case '+':
                case '-':
                    orderedNumbers[c] = parsedNumbers[i];     /* Store the number */
                    orderedOperators[c] = parsedOperands[i];  /* Store the operator */
                    c++;  /* Move to the next index in ordered arrays */
                    break;

                case '*':
                    orderedNumbers[c] = parsedNumbers[i] * parsedNumbers[i+1];  /* Perform multiplication */
                    parsedNumbers[i+1] = -2;  /* Mark the second operand as used */
                    break;
                case '/':
                    orderedNumbers[c] = (float64)parsedNumbers[i] / parsedNumbers[i+1];  /* Perform division */
                    parsedNumbers[i+1] = -2;  /* Mark the second operand as used */
                    break;
                default:
                    orderedNumbers[c] = parsedNumbers[i];  /* Store the number */
                    break;
            }
        }
        else /* parsedNumber is -2 (placeholder for the second operand of * and /) */
        {
            switch (parsedOperands[i])
            {
                case '+':
                case '-':
                    orderedOperators[c] = parsedOperands[i];  /* Store the operator */
                    c++;  /* Move to the next index in orderedOperators array */
                    break;

                case '*':
                    orderedNumbers[c] = orderedNumbers[c] * parsedNumbers[i+1];  /* Perform multiplication */
                    parsedNumbers[i+1] = -2;  /* Mark the second operand as used */
                    break;
                case '/':
                    orderedNumbers[c] = orderedNumbers[c] / parsedNumbers[i+1];  /* Perform division */
                    parsedNumbers[i+1] = -2;  /* Mark the second operand as used */
                    break;
                default:
                    break;
            }
        }
    }

    /* Second pass: Perform addition and subtraction based on ordered numbers and operators */
    float64 result = orderedNumbers[0];
    i = (uint8)1;
    for (i = 1; (orderedNumbers[i] != -1) && (i < 8); ++i)
    {
        switch (orderedOperators[i-1])
        {
            case '+':
                result += orderedNumbers[i];
                break;
            case '-':
                result -= orderedNumbers[i];
                break;
            case '*':
                result *= orderedNumbers[i];
                break;
            case '/':
                result /= orderedNumbers[i];
                break;
            default:
                break;
        }
    }
    return result;  /* Return the final calculated result */
}

static void resetVariables(void)
{
    sint32 i = 0;

    /* Reset the inputArray to -1 for the first 16 elements and set the last element to '=' */
    for (i = 0; i < 16; ++i)
    {
        inputArray[i] = -1;
    }
    inputArray[16] = '=';

    /* Reset parsedNumbers array to -1 for the first 8 elements */
    for (i = 0; i < 8; ++i)
    {
        parsedNumbers[i] = -1;
    }


    /* Reset parsedOperands array to -1 for the first 8 elements */
    for (i = 0; i < 8; ++i)
        {
            parsedOperands[i] = -1;
        }
}

static void trimFloat(char* str)
{
    char trim = 0;  /* Flag to indicate whether trimming should be performed */
    sint32 i = 0;

    /* Search for the decimal point in the string */
    for (i = 0; i < 16; ++i)
    {
        if (str[i] == '.')
        {
            trim = 1;  /* If decimal point is found, set the trim flag and exit the loop */
            break;
        }
    }

    i = 15;  /* Start from the last character of the string */
    while (trim && (str[i] == '0' || str[i] == '.'))
    {
        if (str[i] == '.')
        {
            str[i] = 0;  /* Convert the decimal point to null terminator to remove it */
            break;  /* Exit the loop after removing the decimal point */
        }
        str[i] = 0;  /* Convert trailing zeros to null terminators */
        i--;  /* Move to the previous character */
    }
}

/*****************************************************************************************/

/* Reverses a string 'str' of length 'len' */
static void reverse(char* str, uint32 len)
{
    sint32 i = 0, j = len - 1, temp;

    /* Iterate through the string from both ends towards the center */
    while (i < j)
    {
        temp = str[i];     /* Store the character at the current 'i' position */
        str[i] = str[j];   /* Replace character at 'i' with character at 'j' */
        str[j] = temp;     /* Replace character at 'j' with the stored character */
        i++;               /* Move 'i' towards the center of the string */
        j--;               /* Move 'j' towards the center of the string */
    }
}

/* Converts a given integer x to string str[].
   d is the number of digits required in the output.
   If d is more than the number of digits in x,
   then 0s are added at the beginning. */
static sint32 intToStr(sint64 x, char str[], sint32 d)
{
    sint32 i = 0;

    /* Convert each digit of the integer to its ASCII character representation */
    while (x)
    {
        str[i] = (x % 10) + '0';  /* Convert the least significant digit to ASCII character */
        i++;
        x = x / 10;  /* Move to the next digit */
    }

    /* If the number of digits required is more, add leading zeros */
    while (i < d)
    {
        str[i] = '0';  /* Fill remaining characters with '0' to achieve desired width */
        i++;
    }
    reverse(str, i);  /* Reverse the string to correct the digit order */
    str[i] = '\0';    /* Null-terminate the string to mark its end */
    return i;         /* Return the length of the string */
}

/* Converts a floating-point/double number to a string. */
static void ftoa(const float64* n, char* res, sint32 afterpoint)
{
    /* Handle the sign of the number */
    float64 number;
    uint8 isPositive = 1;

    if ((*n) < 0)
    {
        res[0] = '-';  /* Set the first character of the result string as '-' */
        res++;        /* Move the res pointer to the next character */
        number = (*n) * -1;  /* Convert the number to its positive counterpart */
        isPositive = 0;  /* Indicate that the number is negative */
    }
    else
    {
        number = (*n);
    }

    /* Extract integer part */
    sint64 ipart = (sint64)number;

    /* Extract fractional part */
    float64 fpart = number - (float64)ipart;

    /* Convert integer part to string */
    sint32 i = intToStr(ipart, res, 0);

    /* If there is no integer part, print '0' */
    if (i == 0)
    {
        res[i] = '0';  /* Set the first character of the integer part as '0' */
        i++;
    }
    else{}

    /* Calculate the number of digits after the decimal point */
    afterpoint = 16 - (i + !isPositive + 1);

    /* Check for the display option after the decimal point */
    if (afterpoint != 0)
    {
        res[i] = '.';  /* Add the decimal point to the result string */

        /* Calculate the value of the fractional part up to the specified number of decimal places */
        sint64 power = 1;  /* Initialize a power value to multiply the fractional part */
        uint8 x = 0;

        for (x = 0; x < afterpoint; ++x)
        {
            power *= 10;  /* Calculate 10 raised to the power of the desired decimal places */
        }

        fpart = fpart * power;  /* Multiply the fractional part by the power value */

        /* Convert the fractional part to a string and place it in the result string */
        intToStr((sint64)fpart, res + i + 1, afterpoint);
    }
}

static void delayMs(uint32 delay)
{
    sint32 i, j;

    /* Outer loop: Repeat for the specified delay in milliseconds */
    for (i = 0; i < delay; i++)
    {
        /* Inner loop: Repeat a certain number of times to achieve the desired delay */
        for (j = 0; j < 3180; j++)
        {
            /* This loop doesn't perform any actual operations, resulting in a delay
               The exact number of iterations needed to achieve 1 millisecond depends on the processor's clock speed and architecture
               This loop effectively wastes some processing cycles to introduce the delay */
        }
    }
}
