🚗 Voice-Control Car (ATmega328P + AVR C)

This project implements a voice-controlled 4-wheel drive car using an ATmega328P microcontroller, L298N motor driver, and Python-based voice recognition.

The system was built incrementally, starting from basic UART communication and scaling up to full wireless voice control.

📌 Project Overview
Microcontroller: ATmega328P (XBoard Mini)
Motor Driver: L298N
Communication: UART → Bluetooth (HC-06)
Voice Processing: Python (SpeechRecognition)
Motor Control: PWM + Direction control
🧠 Development Phases
🔹 Phase 1: LED Control (control-led.c)
Implemented UART communication
Sent single-character commands (F, B, L, R, S)
Verified functionality using LEDs
🔹 Phase 2: Motor Control (Full Speed) (control-motor.c)
Replaced LEDs with L298N motor driver
Used IN1–IN4 for direction control
ENA/ENB jumpers kept ON → motors run at full speed
🔹 Phase 3: Voice Control via Python (voice-decode.py)
Created Python script to:
Capture voice input
Convert speech → command (F, B, L, R, S)
Send via UART over USB
🐍 Python Setup

Create virtual environment:

python -m venv venv

Activate:

venv\Scripts\activate

Install dependencies:

pip install pyserial SpeechRecognition pyaudio

Run script:

python voice-decode.py
🔹 Phase 4: PWM Speed Control (control-motor-dir.c)
Implemented Timer1 PWM
Connected:
PB1 (OC1A) → ENA
PB2 (OC1B) → ENB
Enabled:
Variable speed control
Smooth turning (left/right speed differential)
🔹 Phase 5: Bluetooth Integration (HC-06)
Added HC-06 Bluetooth module
UART communication switched from USB → Bluetooth
System flow:
Voice → Laptop → Bluetooth → HC-06 → ATmega → Motors
🔌 Hardware Wiring
Direction Pins
PD2 → IN1
PD3 → IN2
PD4 → IN3
PD5 → IN4
PWM Pins
PB1 (OC1A) → ENA (Left motors)
PB2 (OC1B) → ENB (Right motors)
Motors
OUT1/OUT2 → Left motors
OUT3/OUT4 → Right motors
Power
Battery (+) → L298N VMS
Battery (-) → L298N GND
ATmega GND → SAME GND
🎮 Controls
Command	Action
F	Forward
B	Backward
L	Turn Left
R	Turn Right
S	Stop
🧪 Final Testing
Verified:
UART communication
Motor control
PWM speed variation
Voice command accuracy
Bluetooth communication
Final system supports:
Wired control (USB)
Wireless control (Bluetooth)
Voice-based navigation
⚠️ Notes
L298N introduces voltage drop → avoid very low PWM values
Minimum effective speed ≈ 150–180 PWM
Always ensure common ground between all components
Only one application can use the COM port at a time
🚀 Future Improvements
Add speed commands (“slow”, “fast”)
Implement obstacle detection (ultrasonic sensor)
Replace L298N with more efficient driver (e.g., TB6612FNG)
Fully standalone system (ESP32 + onboard voice)
👤 Author

Roger Trinidad
Electrical / Computer Engineering