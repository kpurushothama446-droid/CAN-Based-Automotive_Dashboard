# 🚗 CAN-BASED AUTOMOTIVE DASHBOARD

### Multi-ECU Communication | Embedded Firmware | Automotive Systems

<div align="center">

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&weight=700&size=22&duration=2500&pause=800&color=00F5A0&center=true&vCenter=true&width=800&lines=3+ECUs+%7C+1+CAN+Network;Automotive+Embedded+Systems;Real-Time+CAN+Communication;Designed+with+Embedded+C;Engineering+Software+That+Talks+to+Hardware" />

<br/>

<img src="https://img.shields.io/badge/Language-Embedded%20C-00599C?style=for-the-badge&logo=c"/>
<img src="https://img.shields.io/badge/Controller-PIC18-168B70?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Protocol-CAN%20Bus-00A98F?style=for-the-badge"/>
<img src="https://img.shields.io/badge/IDE-MPLAB%20X-3949AB?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Compiler-XC8-orange?style=for-the-badge"/>

**PURUSHOTHAMA K | EMBEDDED SOFTWARE ENGINEER ASPIRANT**

</div>

---

## `01 / PROJECT INTRODUCTION`

### Connecting Multiple ECUs Through CAN Communication

An automotive instrument cluster simulation developed using three independent PIC18 microcontroller-based Electronic Control Units (ECUs).

The system demonstrates how multiple embedded controllers exchange vehicle information over a shared Controller Area Network (CAN) bus.

Each ECU performs a dedicated operation, while the dashboard ECU receives and processes messages to display vehicle information through a 16×2 LCD, indicator LEDs and a warning buzzer.

**The engineering objective:** Build a distributed embedded system that demonstrates sensor interfacing, CAN communication, message processing and real-time output control.

### Key System Capabilities

- Vehicle speed acquisition using ADC.
- Gear selection through digital keypad.
- Engine RPM acquisition using ADC.
- Turn indicator input processing.
- CAN-based communication between three ECUs.
- Dashboard information display.
- Reverse gear warning through a buzzer.

---

## `02 / SYSTEM ARCHITECTURE`

### Distributed Three-ECU Architecture

```text
 ┌────────────────────┐
 │       ECU 1        │
 │                    │
 │  Speed Acquisition │
 │  Gear Selection    │
 │                    │
 │  CAN TRANSMITTER   │
 └──────────┬─────────┘
            │
            │
 ═══════════╪═══════════════
            │
         CAN BUS
            │
 ═══════════╪═══════════════
            │
 ┌──────────┴─────────┐
 │       ECU 2        │
 │                    │
 │  RPM Acquisition   │
 │  Turn Indicators   │
 │                    │
 │  CAN TRANSMITTER   │
 └──────────┬─────────┘
            │
            │ CAN MESSAGES
            ▼
 ┌────────────────────┐
 │       ECU 3        │
 │                    │
 │  CAN RECEIVER      │
 │  Message Handler   │
 │                    │
 │  ┌──────────────┐  │
 │  │ 16x2 LCD     │  │
 │  │ Indicator LED│  │
 │  │ Warning Buzzer│ │
 │  └──────────────┘  │
 └────────────────────┘
```

### ECU Functional Responsibilities

| Controller | Function | Main Operations |
|---|---|---|
| ECU1 | Speed and gear | ADC, keypad, CAN TX |
| ECU2 | RPM and indicators | ADC, keypad, CAN TX |
| ECU3 | Dashboard | CAN RX, LCD, LEDs, buzzer |

---

## `03 / HOW THE SYSTEM WORKS`

### End-to-End Data Flow

**STEP 01 — INPUT ACQUISITION**

ECU1 reads the speed input and gear selection. ECU2 reads the RPM input and turn indicator selection.

**STEP 02 — DATA PROCESSING**

The respective controllers process the acquired analog and digital inputs.

**STEP 03 — CAN FRAME GENERATION**

Each transmitting ECU prepares CAN messages using dedicated standard identifiers and corresponding data.

**STEP 04 — NETWORK COMMUNICATION**

The messages are transmitted through the shared CAN network.

**STEP 05 — MESSAGE DECODING**

ECU3 receives the messages and identifies their purpose using CAN message identifiers.

**STEP 06 — DASHBOARD UPDATE**

The dashboard updates the LCD, turn indicator LEDs and warning buzzer according to the received information.

---

## `04 / CAN COMMUNICATION MATRIX`

### Message Identification and Routing

| Parameter | CAN ID | Transmitter | Receiver |
|---|---|---|---|
| Vehicle Speed | `0x10` | ECU1 | ECU3 |
| Gear Position | `0x20` | ECU1 | ECU3 |
| Engine RPM | `0x30` | ECU2 | ECU3 |
| Engine Temperature | `0x40` | Reserved | Not implemented |
| Turn Indicator | `0x50` | ECU2 | ECU3 |

**Communication characteristics**

- Standard 11-bit CAN identifiers.
- Dedicated identifiers for individual signals.
- Distributed message transmission.
- Centralized dashboard message processing.

---

## `05 / HARDWARE INTEGRATION`

| Hardware | Function |
|---|---|
| PIC18 Microcontrollers | ECU processing |
| CAN Transceiver | Physical CAN interface |
| Potentiometers | Speed and RPM simulation |
| Digital Keypad | Gear and indicator selection |
| 16×2 Character LCD | Dashboard display |
| LEDs | Turn signal indication |
| Buzzer | Reverse gear warning |
| 120Ω Termination | CAN bus termination |

### CAN Network Connection

```text
PIC18 MCU                CAN TRANSCEIVER
─────────                ────────────────
CAN TX  ───────────────► TXD
CAN RX  ◄─────────────── RXD
                            │
                            ├──── CAN_H
                            │
                            └──── CAN_L

ECU1 ───────────────┐
                    ├──── Shared CAN Network
ECU2 ───────────────┤
                    │
ECU3 ───────────────┘
```

Each ECU requires its own compatible CAN transceiver. The physical network requires 120Ω termination at its two ends.

---

## `06 / FIRMWARE ARCHITECTURE`

### Modular Embedded C Development

The firmware is organized into separate ECU applications and peripheral drivers.

| Firmware Module | Responsibility |
|---|---|
| `main.c` | Application execution |
| `can.c / can.h` | CAN initialization and communication |
| `adc.c / adc.h` | Analog input acquisition |
| `sensor.c` | Sensor processing |
| `digital_keypad.c` | Keypad scanning |
| `msg_handler.c` | CAN message processing |
| `clcd.c / clcd.h` | LCD interfacing |
| `timer0.c / timer0.h` | Timer configuration |
| `isr.c / isr.h` | Interrupt handling |
| `uart.c / uart.h` | Serial debugging support |

### Software Execution Flow

```text
             SYSTEM INITIALIZATION
                      |
                      ▼
             PERIPHERAL SETUP
                      |
                      ▼
              INPUT ACQUISITION
                      |
                      ▼
             CAN FRAME CREATION
                      |
                      ▼
               CAN TRANSMISSION
                      |
                      ▼
              CAN MESSAGE RECEIVE
                      |
                      ▼
               MESSAGE DECODING
                      |
                      ▼
               OUTPUT CONTROL
                      |
              ┌───────┼────────┐
              ▼       ▼        ▼
             LCD     LEDs    BUZZER
```

---

## `07 / DEVELOPMENT ENVIRONMENT`

| Category | Technology |
|---|---|
| Programming | Embedded C |
| Microcontroller | PIC18 Series |
| Communication | CAN / ECAN |
| IDE | MPLAB X IDE |
| Compiler | Microchip XC8 |
| Peripheral Interfaces | ADC, GPIO, LCD |
| Timing | Timer0 and Interrupts |

---

## `08 / PROJECT STRUCTURE`

```text
CAN-Based-Automotive_Dashboard/
│
├── ECU1/
│   ├── main.c
│   ├── can.c
│   ├── can.h
│   ├── adc.c
│   ├── adc.h
│   ├── sensor.c
│   ├── digital_keypad.c
│   └── msg_id.h
│
├── ECU2/
│   ├── main.c
│   ├── can.c
│   ├── can.h
│   ├── adc.c
│   ├── sensor.c
│   ├── digital_keypad.c
│   └── msg_id.h
│
├── ECU3/
│   ├── main.c
│   ├── can.c
│   ├── msg_handler.c
│   ├── clcd.c
│   ├── timer0.c
│   ├── isr.c
│   └── msg_id.h
│
└── README.md
```

*The structure above is a guide. The uploaded repository should reflect the actual files.*

---

## `09 / BUILD AND EXECUTION`

### Prerequisites

- MPLAB X IDE
- XC8 Compiler
- Compatible PIC18 development boards
- CAN transceivers
- CAN bus termination resistors
- PICkit programmer or compatible debugger

### Execution Steps

1. Open the individual ECU projects in MPLAB X.
2. Select the correct target microcontroller.
3. Configure the XC8 compiler.
4. Build the firmware for each ECU.
5. Program the respective microcontrollers.
6. Connect the nodes through the shared CAN network.
7. Power up the system and observe dashboard operation.

---

## `10 / ENGINEERING CONCEPTS DEMONSTRATED`

- CAN protocol and message identifiers.
- ADC-based sensor interfacing.
- Digital input and output control.
- LCD interfacing.
- Timer configuration.
- Interrupt handling.
- Modular firmware development.
- Distributed microcontroller communication.

---

## `11 / FUTURE DEVELOPMENT`

- [ ] Add actual engine temperature sensing.
- [ ] Implement CAN acceptance filtering.
- [ ] Introduce UART-based debugging.
- [ ] Add CAN bus fault monitoring.
- [ ] Improve error handling and diagnostics.
- [ ] Extend the dashboard with additional automotive parameters.

---

## `12 / ABOUT THE DEVELOPER`

<div align="center">

### PURUSHOTHAMA K

**Embedded Systems | Embedded C | Firmware Development**

Electrical and Electronics Engineering Graduate

Focused on developing embedded applications, understanding microcontroller peripherals and building practical hardware-software solutions.

[![GitHub](https://img.shields.io/badge/GitHub-Profile-181717?style=for-the-badge&logo=github)](https://github.com/kpurushothama446-droid)

[![LinkedIn](https://img.shields.io/badge/LinkedIn-Connect-0A66C2?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/in/purushothama-k-b8413227b/L)

</div>

---

<div align="center">

### ENGINEERING IS WHERE SOFTWARE MEETS HARDWARE.

**DESIGN • DEVELOP • DEBUG • BUILD**

</div>
