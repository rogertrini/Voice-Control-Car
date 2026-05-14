# Voice Controlled Robotic Car

## Project Description

This project implements a voice-controlled robotic vehicle using an AVR microcontroller programmed in C. The system controls a four-wheel drive chassis through an L298N motor driver and receives movement commands through UART communication and Bluetooth integration.

Current implemented features include:

- Forward motor control  
- Reverse motor control  
- UART command interface  
- Bluetooth communication testing  
- Hardware validation of drivetrain system  

Future work includes voice recognition integration, PWM speed balancing, and autonomous movement refinement.

---

# Hardware Requirements

- AVR development board / Atmega Xplained Mini  
- L298N Motor Driver Module  
- 4 DC motors  
- Robot chassis  
- Bluetooth UART module  
- Battery pack  
- Jumper wires  

---

# Software Requirements

- [Microchip Studio](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio)  
- AVR-GCC Toolchain  
- USB programmer/debugger  
- Python (for Bluetooth command testing)

---

# Building the Project

1. Open the project in Microchip Studio  
2. Verify the correct AVR device is selected  
3. Connect the AVR board to the computer through USB  
4. Build the project using:

```text
Build → Build Solution
```

or press:

```text
Ctrl + Shift + B
```

5. Ensure compilation completes with no errors.

---

# Flashing the Project to the AVR

1. Connect the AVR board through USB  
2. In Microchip Studio select:

```text
Tools → Device Programming
```

3. Select:
- Tool: Atmel-ICE or onboard debugger  
- Device: correct ATmega device  
- Interface: ISP

4. Click “Apply”  
5. Program the compiled `.hex` file onto the board using:

```text
Program → Memories → Program
```

---

# Running the System

After flashing:

1. Power the motor driver and motors using the battery pack  
2. Connect Bluetooth module to UART pins  
3. Open the Python Bluetooth controller or UART terminal  
4. Send movement commands such as:

```text
F = Forward
B = Backward
S = Stop
L = Left
R = Right
```

5. The AVR processes incoming UART data and drives the motors accordingly.

---

# Current Status

## Completed
- Basic drivetrain testing  
- UART motor control  
- Bluetooth communication validation  
- Forward/backward movement testing  

## In Progress
- Voice command processing  
- PWM speed balancing  
- Mechanical reliability improvements  
- Full autonomous command handling  

---

# System Architecture

```text
Python Voice/Bluetooth Interface
              |
              v
      Bluetooth UART Module
              |
              v
      AVR Microcontroller
              |
        GPIO / UART
              |
              v
       L298N Motor Driver
              |
              v
          4 DC Motors
```

---

# Authors

Developed as an embedded systems and AVR programming project focused on:
- Embedded C development  
- UART communication  
- Motor driver interfacing  
- Wireless command systems  
- Hardware/software debugging
