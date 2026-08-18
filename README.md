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
├── PCB/                          # KiCad PCB Files, Schematics & Renders
│   ├── Hand_gerbers.zip
│   ├── Robotic_HAND.png
│   ├── Robotic_HAND_top.png
│   └── Robotic_HAND_schematic.svg
├── LICENSE
└── README.md

Component,Quantity,Connection / Function
Arduino Uno R3,1,Primary Microcontroller
Micro Servos (SG90 / MG90S),6,"Pins 2–7 (Pinky, Ring, Middle, Index, Thumb, Palm)"
28BYJ-48 Stepper Motor,1,"Pins 8, 9, 10, 11 (Base Rotation)"
ULN2003 Driver Module,1,Connects to ULN2003_J1 & JULNpwr_J2 PCB headers
Trimmer Potentiometers,3,"Onboard inputs RV1 (A0), RV2 (A1), RV3 (A2)"
2-Pin Screw Terminal (J1),1,Dedicated external DC supply input for actuators
Custom Arduino Shield PCB,1,Custom 2-layer power & signal routing PCB
Pin Headers (Male & Female),Assorted,"Component, servo, and Arduino stacking connections"
