# 🚗 Voice-Control Car (ATmega328P + AVR C)

A voice-controlled 4-wheel drive car built using an ATmega328P, L298N motor driver, and Python-based voice recognition.

This project was developed step-by-step, starting from basic UART communication and progressing to full wireless voice control.

---

## 📌 Project Overview

- Microcontroller: ATmega328P (XBoard Mini)
- Motor Driver: L298N
- Communication: UART → Bluetooth (HC-06)
- Voice Processing: Python (SpeechRecognition)
- Motor Control: PWM + Direction Control

---

## 🧠 Development Phases

### 🔹 Phase 1: LED Control (`control-led.c`)

- Implemented UART communication  
- Sent commands: `F`, `B`, `L`, `R`, `S`  
- Verified functionality using LEDs  

---

### 🔹 Phase 2: Motor Control (Full Speed) (`control-motor.c`)

- Replaced LEDs with L298N motor driver  
- Used IN1–IN4 for direction control  
- ENA/ENB jumpers enabled → full speed operation  

---

### 🔹 Phase 3: Voice Control (Wired UART) (`voice-decode.py`)

- Python script captures voice input  
- Converts speech → command  
- Sends command over USB (UART)  

#### 🐍 Python Setup

```bash
python -m venv venv
venv\Scripts\activate
pip install pyserial SpeechRecognition pyaudio
python voice-decode.py

---

### 🔹 Phase 4: PWM + Direction Control (`control-motor-dir.c`)

- Implemented Timer1 PWM using hardware registers  
- Enabled variable speed control through ENA/ENB pins  
- Used differential speed for smoother turning  

---

### 🔹 Phase 5: Bluetooth Integration (HC-06)

- Replaced USB communication with Bluetooth  
- Connected HC-06 to ATmega UART (RX/TX)  
- System now supports wireless control  

System flow:

## 🎮 Controls

| Command | Action      |
|--------|------------|
| F      | Forward    |
| B      | Backward   |
| L      | Turn Left  |
| R      | Turn Right |
| S      | Stop       |

---

## 🧪 Final Testing

- Verified UART communication  
- Verified motor direction control  
- Verified PWM speed control  
- Verified voice command recognition  
- Verified Bluetooth communication  

Supports:

- Wired control (USB)  
- Wireless control (Bluetooth)  
- Voice navigation  

---

## ⚠️ Notes

- L298N has voltage drop → avoid low PWM values  
- Minimum effective speed ≈ 150–180  
- Always use common ground  
- Only one program can access COM port at a time  

---

## 🚀 Future Improvements

- Add speed commands ("slow", "fast")  
- Add obstacle detection (ultrasonic sensor)  
- Replace L298N with efficient driver (TB6612FNG)  
- Fully standalone system (ESP32 + onboard voice)  

---

## 👤 Author

Roger Trinidad  
Electrical / Computer Engineering