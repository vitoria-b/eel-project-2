# BusSense  
**Assistive RF-Based Bus Identification System for Visually Impaired Users**

## Overview
BusSense is an assistive electronic system designed to help visually impaired users identify and board the correct public bus independently. The system uses low-cost RF communication at 433 MHz and embedded systems to establish bidirectional communication between the user and the bus.

The project was developed as part of undergraduate courses in Project of Electronics Level II.

## Problem Statement
Visually impaired individuals often face difficulties identifying approaching buses and confirming whether the arriving vehicle corresponds to their intended route. Existing urban infrastructure does not reliably address this issue, limiting autonomy and accessibility in public transportation.

## Proposed Solution
BusSense consists of two main modules:
- **User Module**: carried by the visually impaired user.
- **Bus Module**: installed inside the bus.

The system enables:
- Selection of the desired bus line by the user via a keypad.
- Periodic RF transmission of the bus line identifier from the bus module.
- Automatic comparison between the received bus line and the user-selected line.
- Tactile feedback (vibration) to alert the user when the correct bus is approaching.
- Visual alert (LED) inside the bus to notify the driver that a visually impaired passenger is waiting.

## System Architecture
- **Microcontroller**: Arduino Uno / Arduino Nano  
- **RF Communication**: 433 MHz ASK modules using the RadioHead library  
- **User Interface**: 4×4 membrane keypad with planned Braille labeling  
- **Feedback Mechanisms**:
  - Vibration motor for the user
  - Visual LED indicator for the bus driver  
- **Antenna**: Quarter-wave wire antenna (17.3 cm)

## Testing and Validation
- RF spectrum analysis using Software Defined Radio (SDR) and Gqrx
- Functional validation of simultaneous transmission and reception
- End-to-end system demonstration in a controlled environment

## Limitations and Future Improvements
- Miniaturization of the hardware into a compact enclosure
- Battery monitoring and USB recharging
- Improved user interface and ergonomics
- Integration with real urban transportation systems

## Technologies and Tools
- Embedded C / Arduino
- RF communication (433 MHz)
- RadioHead Library
- RTL SDR and Gqrx
- Electronic prototyping and PCB concepts

## Documentation
A complete technical report describing the design, implementation, testing, and results of the project is available in the repository.

## Authors
- Vitória Beatriz Bianchin  
- Gustavo Friol Bento  
- Matheus Bateli Neumann  

## License
This project was developed for academic purposes.  
