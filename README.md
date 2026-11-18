# Three-ECU CAN-Based Automotive Dashboard

![Embedded Systems](https://img.shields.io/badge/Domain-Embedded%20Systems-blue)
![Language](https://img.shields.io/badge/Language-Embedded%20C-green)
![Microcontroller](https://img.shields.io/badge/MCU-PIC18F4580-orange)
![Protocol](https://img.shields.io/badge/Protocol-CAN-red)

## Project Overview

This project demonstrates a distributed automotive dashboard system using three PIC18F4580 microcontrollers communicating through the Controller Area Network (CAN) protocol.

Each ECU performs a dedicated function, processes input data, and communicates with the dashboard controller through CAN messages. The receiving ECU processes the messages and updates the character LCD and indicator LEDs.

The project was developed using Embedded C and MPLAB X IDE with the XC8 compiler as an embedded systems simulation project.

## System Architecture

The system consists of three independent ECUs connected through a CAN communication network.

### ECU1 – Vehicle Input Processing
- Reads vehicle speed using ADC.
- Detects gear selection through a matrix keypad.
- Transmits speed and gear information through CAN.

### ECU2 – Engine and Indicator Processing
- Reads engine RPM using ADC.
- Detects indicator selection using a digital keypad.
- Transmits RPM and indicator status through CAN.

### ECU3 – Dashboard Display Controller
- Receives CAN messages from the network.
- Identifies messages using CAN identifiers.
- Displays speed, gear and RPM information on the character LCD.
- Controls left and right indicator LEDs.
- Uses Timer0 interrupt functionality for indicator blinking.

## CAN Message Identifiers

| Parameter | CAN ID |
|---|---|
| Speed | 0x10 |
| Gear | 0x20 |
| RPM | 0x30 |
| Engine Temperature | 0x40 |
| Indicator | 0x50 |

Note: Engine temperature has a reserved message identifier, but its processing is not yet implemented in the current source code.

## Technologies Used

- Embedded C
- PIC18F4580 Microcontroller
- CAN Communication Protocol
- ADC
- Matrix Keypad
- Digital Keypad
- Character LCD
- UART
- Timer0 and Interrupts
- MPLAB X IDE
- XC8 Compiler

## Repository Structure

```text
CAN-Based-Automotive-Dashboard/
│
├── ECU1.X/
│   ├── main.c
│   ├── adc.c / adc.h
│   ├── can.c / can.h
│   ├── clcd.c / clcd.h
│   └── other source files
│
├── ECU2.X/
│   ├── main.c
│   ├── adc.c / adc.h
│   ├── can.c / can.h
│   ├── digital_keypad.c / .h
│   └── other source files
│
├── ECU3.X/
│   ├── main.c
│   ├── can.c / can.h
│   ├── message_handler.c / .h
│   ├── timer0.c / .h
│   └── other source files
│
├── Documentation/
│   └── three_ecu_can_architecture.png
│
└── README.md
```

## Development Environment

- MPLAB X IDE
- XC8 Compiler
- PIC18F4580 device support

## Key Learning Outcomes

- Understanding distributed embedded systems.
- Implementing CAN message transmission and reception.
- Working with ADC and keypad interfacing.
- Developing modular Embedded C programs.
- Handling interrupts and timer functionality.
- Understanding communication between multiple microcontrollers.

## Future Improvements

- Implement engine temperature monitoring.
- Improve CAN error handling and message validation.
- Add communication failure detection.
- Extend dashboard functionality.

## Author

**Purushothama K**

Embedded Software Engineer | Embedded C | Microcontrollers | CAN Communication
