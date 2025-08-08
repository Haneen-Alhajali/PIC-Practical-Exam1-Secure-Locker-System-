# Microcontrollers Lab Practical Exam #1 – 🗄️ Secure Locker System

**Project:** Practical Exam #1 – Embedded System Locker Guessing Mechanism  
**Course:** Microcontrollers Lab  
**Platform:** MPLAB Harmony (Microchip)

---

## 🧠 Project Overview

This project implements a **🔐secure locker system** where a user must guess a secret 3-digit code using a **4x4 keypad**. The secret code is sent from a **PC via UART**, and the user has **3 attempts** to enter the correct code. Depending on the result, the system performs various actions using LEDs, UART messaging, and a stepper motor.

---

## 🔧 Features

- **UART Communication:**
  - Receives a 3-digit code from the PC on startup.
  - Sends back **"success"** or **"fails"** messages to the PC after the guessing process.

- **Keypad Input:**
  - Accepts user input via a 4x4 matrix keypad.
  - Compares user input with the received code.

- **LED Indicators:**
  - LEDs indicate the number of failed attempts.
    - 1st wrong attempt → 1 LED ON.
    - 2nd wrong attempt → 2 LEDs ON.
    - 3rd wrong attempt → 3 LEDs ON.
  - On success → All 4 LEDs ON.
  - On failure → All LEDs flash continuously using a timer.

- **Stepper Motor Control:**
  - If the correct number is guessed, rotate the stepper motor by the number of degrees equal to the secret code (e.g., 123 rotates 123°).

---

## 🛠 System Requirements

### Hardware:
- Microchip microcontroller (with Harmony framework support)
- 4x4 Keypad **connected to port JF**
- UART-connected PC
- 4 LEDs (built_in)
- Stepper Motor **connected to port JA**
- Timer Module (period=312500, oparation mode 32bit, prescale=256

### Software:
- MPLAB X IDE
- MPLAB Harmony Framework
- XC32 Compiler

---

## 📁 Project Structure

```plaintext
📂 exam1/
├── README.md                                  # Project documentation
├── 📂 assets/
│   └── requirements.png                       # System requirements image provided by the doctor
└── 📂 firmware/
    └── 📂 src/
        ├── app.c                              # Main application logic with state machine
        ├── app.h                              # Application states and data structure definitions
        └── 📂 system_config/
            └── 📂 default/
                └── system_interrupt.c         # Timer interrupt handler for LED flashing

```

---

## 📷 System Behavior Flow

1. PC sends a 3-digit number via UART to the microcontroller.  
2. User guesses the code using the keypad (max 3 tries).  
3. After each wrong guess:  
   - An additional LED turns on.  
4. If the guess is correct:  
   - Sends **"success"** via UART.  
   - All LEDs turn on.  
   - Stepper motor rotates by the given number in degrees.  
5. If the guess fails after 3 tries:  
   - Sends **"fails"** via UART.  
   - All LEDs flash continuously.

---

## 🔄 State Machine Overview

| State         | Description                                             |
|---------------|---------------------------------------------------------|
| `APP_STATE_INIT` | Initializes system peripherals and starts Timer         |
| `RX`           | Receives 3-digit code from PC via UART                 |
| `enter`        | Reads user input from keypad                           |
| `check`        | Compares user input with received code                 |
| `nextattempt`  | Updates LED based on attempt count                     |
| `TX`           | Sends success/failure message via UART                 |
| `FS`           | Rotates the stepper motor if the guess is correct      |
| `flashing`     | Flashes all LEDs continuously (on failure)             |
| `noop`         | Idle state                                              |

---

## ✅ Project Status

- ✅ Fully functional and tested  
- ✅ Proper UART communication  
- ✅ Accurate keypad detection  
- ✅ Timer-based LED flashing  
- ✅ Stepper motor integration  

---

## 📌 How to Use

1. Connect the system to your PC and power up the microcontroller.  
2. Send a 3-digit number via UART terminal (e.g., TeraTerm).  
3. Use the keypad to input your guess (max 3 tries).  
4. Observe LEDs, motor, and UART messages for results.  

---

## 👨‍💻 Author

- **Student :** Haneen Alhajali and Nour Alhuda Kilany 
- **Lab:** Microcontrollers – Practical Exam #1  
- **Supervisor:** *Dr.Manar Qamhieh*
