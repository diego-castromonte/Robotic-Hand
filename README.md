# 6-DOF Robotic Hand with Rotating Base

A fully custom 3D-printed 6 Degree-of-Freedom (DOF) robotic hand powered by an Arduino Uno, custom PCB shield, 6x micro servos, and a 28BYJ-48 stepper motor base assembly.

---

## Overview

Unlike standard breadboard robotic hand builds, this project utilizes a custom-designed **Arduino Uno Shield PCB** to streamline wiring, route dedicated actuator power, and enable dual control via onboard analog potentiometers and direct USB Serial commands.

### Key Features
* **Full-Hand Actuation:** 5 individual finger servos + 1 wrist/palm tilt servo.
* **Continuous Base Rotation:** Driven by a 28BYJ-48 stepper motor via an integrated ULN2003 driver header.
* **Custom PCB Shield:** Integrates power distribution terminals, 6x 3-pin servo headers, stepper outputs, and 3 control potentiometers onto a single direct-mount Arduino shield.
* **Dual-Control Modes:** Manual potentiometer positioning (Base rotation, Palm pitch, Hand close) alongside a 115200 baud UART Serial Command Interface (`1o`/`1c` through `5o`/`5c`, `R`).

---

## Repository Structure

```text
├── CAD/                          # 3D Printable STL Files
│   ├── All_Fingers.stl
│   ├── Arm_Base_bottom.stl
│   ├── Arm_Base_top.stl
│   ├── Hand_Palm.stl
│   ├── Stepper_base_atch.stl
│   ├── Thumb.stl
│   ├── forarm.stl
│   ├── forarm_top.stl
│   ├── servo_mount.stl
│   └── servo_pull_atch.stl
├── Firmware/                     # Arduino MCU C++ Code
│   └── Hand_Code_Final.ino
├── PCB/                          # KiCad PCB Files & Renders
│   ├── Hand_gerbers.zip
│   ├── Robotic_HAND.png
│   └── Robotic_HAND_top.png
├── LICENSE
└── README.md
```

## Hardware & Bill of Materials 

### Electronics & Components
| Component | Quantity | Connection / Function |
| :--- | :--- | :--- |
| **Arduino Uno R3** | 1 | Primary Microcontroller |
| **Micro Servos (SG90 / MG90S)** | 6 | Pins 2–7 (Pinky, Ring, Middle, Index, Thumb, Palm) |
| **28BYJ-48 Stepper Motor** | 1 | Pins 8, 9, 10, 11 (Base Rotation) |
| **ULN2003 Driver Module** | 1 | Connects to `ULN2003_J1` & `JULNpwr_J2` PCB headers |
| **Trimmer Potentiometers** | 3 | Onboard inputs `RV1` (A0), `RV2` (A1), `RV3` (A2) |
| **2-Pin Screw Terminal (`J1`)** | 1 | Dedicated external DC supply input for actuators |
| **Custom Arduino Shield PCB** | 1 | Custom 2-layer power & signal routing PCB |
| **Pin Headers (Male & Female)** | Assorted | Component, servo, and Arduino stacking connections |

---

## Hardware Schematics & PCB Design

The custom shield isolates actuator power (`+5V_MOTOR`) from the logic supply to prevent microcontroller brownouts and reset loops during heavy multi-servo movement.

### Schematic
![Custom Shield Schematic](./PCB/Robotic_HAND_schematic.svg)

### Board Layout & 3D Renders
| Isometric View | Top View |
| :---: | :---: |
| ![Isometric Render](./PCB/Robotic_HAND.png) | ![Top Render](./PCB/Robotic_HAND_top.png) |

---

## Software & Control Logic

The primary controller code is located at `/Firmware/Hand_Code_Final.ino`.

### Serial Commands (115200 Baud)

Open the Arduino Serial Monitor at **115200 baud** to issue real-time positional commands:

| Command | Action | Command | Action |
| :--- | :--- | :--- | :--- |
| `1o` / `1c` | Pinky Open / Close | `4o` / `4c` | Index Open / Close |
| `2o` / `2c` | Ring Open / Close | `5o` / `5c` | Thumb Open / Close |
| `3o` / `3c` | Middle Open / Close | `R` or `r` | **Reset All** (All servos to default) |

---

## Getting Started

1. **Assemble Hardware:** Print the components from `/CAD` and press-fit the custom PCB shield onto your Arduino Uno.
2. **Power Supply:** Connect an external 5V 2A DC power source to terminal block `J1` to isolate motor power from the Arduino logic supply.
3. **Upload Firmware:** Open `/Firmware/Hand_Code_Final.ino` in the Arduino IDE, select **Arduino Uno**, choose your COM port, and click **Upload**.

---
