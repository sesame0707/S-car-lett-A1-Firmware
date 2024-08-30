# S(car)lett A1 Firmware

<img src="Pictures/Logos/S(car)lett%20Firmware%20logo/S(car)lett%20Firmware%20logo%20(v1).png" alt="S(car)lett A1 Firmware Logo" width="700">

## The Repository
This is the repository of the firmware suited for the first A-line car in the [`S(car)lett`](https://github.com/sesame0707/S-car-lett) project.

## High-Level Goals
Those are the initial goals of this module:
- Compliance with new standards
- High software modularity
- The use of more expensive, but desirable components instead of cheaper, but weaker ones

All of the above goals have been achieved throughout this module's implementation.

## Results
The wireless communication infrastructure that has been implemented can be observed in the following picture:

<img src="Pictures/Diagrams/Wireless%20Communication%20Infrastructure.png" alt="Wireless Communication Infrastructure" width="700">

The resulting software for `ST NUCLEO-F767ZI` (main MCU-based board) is written in `C` with the use of `FreeRTOS` and `CMSIS` abstraction layer, while the software for `Raspberry Pi Pico W` (secondary MCU-based board acting as a Wi-Fi module) is written in `MicroPython`.

Both pieces of software encompass the usage of non-standard libraries, so their licenses must be respected by anyone, who uses this project module.

The FreeRTOS task diagram looks as follows:

<img src="Pictures/Diagrams/Inter-Process%20Communication.png" alt="Inter-Process Communication" width="700">

The hardware-related wiring scheme is presented below:

<img src="Pictures/Diagrams/Wiring%20Scheme.png" alt="Wiring Scheme" width="700">

## Q&A
1. Does ST NUCLEO-F767ZI have crystal on-board?
\
*No. Therefore, you must avoid HSE as clock source for SYSCLK. HSI is a microcontroller’s built-in crystal with low accuracy (but it is allowed to use). The best option is to use PLLCLK with the “BYPASS Clock Source” option for HSE. Make sure that the input frequency for HSE is set to 8 MHz (the built-in ST-LINK’s XTAL frequency).*
