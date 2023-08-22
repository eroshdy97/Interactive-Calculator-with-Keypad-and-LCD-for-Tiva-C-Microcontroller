# Interactive Calculator with Keypad and LCD for Tiva-C Microcontroller

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Project Demo](#project-demo)
- [Getting Started](#getting-started)
  - [Hardware Setup](#hardware-setup)
  - [Software Compilation](#software-compilation)
  - [Upload the Code](#upload-the-code)
  - [Power Up](#power-up)
- [Usage](#usage)
- [Future Work](#future-work)
- [Contributing](#contributing)
- [Acknowledgments](#acknowledgments)
- [Contact](#contact)

## Overview

Welcome to the Interactive Calculator project, designed for the Tiva-C microcontroller platform. This project combines the power of a 4x4 keypad for user input and an alphanumeric LCD screen for real-time output, creating a dynamic and interactive arithmetic calculator. :rocket:

## Features

- **Real-time Interaction:** This calculator offers a user-friendly interface that allows users to input numbers and operations via the 4x4 keypad. The results are instantly displayed on the connected LCD screen, providing a seamless experience. :keyboard: :1234:

- **Arithmetic Operations:** Perform fundamental arithmetic operations such as addition (+), subtraction (-), multiplication (*), and division (/). The calculator follows the order of operations, with multiplication and division taking priority. :heavy_plus_sign: :heavy_minus_sign: :heavy_multiplication_x: :heavy_division_sign:

- **Support for Integers and Decimals:** The calculator caters to both integer and floating-point calculations, accommodating a wide range of mathematical tasks. :1234: :chart_with_upwards_trend:

- **Error Handling:** To ensure a smooth experience, the application includes error prevention mechanisms. These safeguards prevent issues like input overflow and division by zero. :no_entry_sign:

- **Keypad Interrupts:** Keypad input is captured using interrupts, ensuring responsive and efficient interaction. Interrupts also enhance the energy efficiency of the system. :electric_plug: :zap:

- **Precise Calculations:** The calculator is designed to handle negative numbers and perform calculations with a high degree of precision, even for irrational numbers. This ensures accurate and reliable results for various mathematical scenarios. :infinity: :heavy_minus_sign:

## Hardware Requirements

To run this project, you'll need the following hardware components:

- **Tiva-C Series Microcontroller (TM4C123GH6PM):** The project is designed to work with the Tiva-C microcontroller, specifically the TM4C123GH6PM model. This microcontroller provides the processing power and I/O capabilities needed for the calculator application.

- **4x4 Keypad:** The keypad allows users to input numbers and operations for calculations.

- **Alphanumeric LCD Screen:** The LCD screen displays the entered input and the calculated results.

- **Jumper Wires:** Use jumper wires to establish connections between the microcontroller, keypad, and LCD screen.

- **Breadboard (if required):** A breadboard can be used to organize and manage the connections between components.

## Project Demo

See the calculator in action! Below is a detailed demo video demonstrating the calculator's functionality.

[Watch Demo Video](https://www.github.com/eroshdy97/Interactive-Calculator-with-Keypad-and-LCD-for-Tiva-C-Microcontroller/blob/main/Demo/Demo.mp4)

## Getting Started

Follow these steps to get the project up and running on your Tiva-C microcontroller:

### Hardware Setup

1. Connect the 4x4 keypad and the alphanumeric LCD screen to the designated ports and pins on the Tiva-C microcontroller.
2. Update the configuration files (`HAL/KEYPAD/KEYPAD_config.h` and `HAL/LCD/LCD_config.h`) to match your hardware connections.

### Software Compilation

1. Choose your preferred integrated development environment (IDE) or toolchain. We recommend using Code Composer Studio (CCS).
2. Compile the provided source code.

### Upload the Code

1. Use a USB Micro B to flash the compiled binary onto the Tiva-C microcontroller.

### Power Up

1. Power on the Tiva-C microcontroller.
2. Make sure the keypad and LCD screen are properly connected and functional.

## Usage

1. Press the numeric keys on the keypad to input numbers.
2. Use the `+`, `-`, `*`, and `/` keys to perform arithmetic operations.
3. Press the `=` key to calculate the result of the entered expression. The result will be displayed on the LCD screen.
4. To start a new calculation, press the `R` key to clear the LCD screen.

## Future Work

Here are some potential improvements and features that could be added in the future:

- **Advanced Functions:** Expand the calculator's capabilities by incorporating trigonometric functions (sin, cos, tan) for more complex calculations. :triangular_ruler:
- **Exponential Power:** Enhance the calculator's functionality by adding support for exponentiation using the `**` operator. :arrow_up:
- **User Interface Enhancements:** Consider improving the user interface with a graphical display, more intuitive keypad layout, and additional error handling. :art:

## Contributing

Contributions to this project are welcomed and appreciated! If you find bugs or want to enhance the application, please submit a pull request. For significant changes, consider opening an issue first to discuss the proposed modifications.

## Acknowledgments

This project draws inspiration from educational resources provided by Egypt Make Electronics (EME). :thumbsup:

## Contact

For inquiries, questions, or collaboration opportunities, feel free to reach out to <e.roshdy97@gmail.com>. :email:
