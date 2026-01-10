---
layout: default
title: Wiring Guide - H-CAT
---


## Overview

This document outlines the complete wiring connections for the H-CAT system, including the Arduino, dual LED panels, RTC module, and user input components. A common ground is essential for all components to communicate correctly.

## Power Distribution

The external 5V power supply serves as the primary power source for both the LED matrices and the Arduino. A separate 5V bus on the breadboard, powered by the Arduino, provides regulated power for sensitive low-current components.

### Main Power Connections

**Power Supply (+) Positive Terminal / Bus:**

- Connect to the VIN pin on the Arduino

- Connect to the +5V pin on LED Panel 1

- Connect to the +5V pin on LED Panel 2

**Power Supply (-) Negative/Ground Terminal / Bus:**

- Connect to a GND pin on the Arduino (creates essential common ground)

- Connect to the GND pin on LED Panel 1

- Connect to the GND pin on LED Panel 2

**Arduino Power Distribution:**

- Arduino 5V to Arduino 5V Bus (for low-power components)

- Arduino GND to Arduino GND Bus (for low-power components)

## LED Panel Configuration

The two LED panels are daisy-chained together. The Arduino communicates with the first panel, which then passes the signal to the second panel.

### Arduino to Panel 1 Connections

- Arduino Pin D11 (MOSI) → Data In (DI) on LED Panel 1

- Arduino Pin D13 (SCK) → Clock In (CI) on LED Panel 1

### Panel-to-Panel Connections

- LED Panel 1 Data Out (DO) → LED Panel 2 Data In (DI)

- LED Panel 1 Clock Out (CO) → LED Panel 2 Clock In (CI)

## Low-Power Components

These components are controlled by and receive power from the Arduino's regulated 5V bus.

### Real-Time Clock (RTC) Module

- Arduino 5V Bus → RTC VCC (or 5V) Pin

- Arduino GND Bus → RTC GND Pin

- Arduino Pin A4 (SDA) → RTC SDA Pin

- Arduino Pin A5 (SCL) → RTC SCL Pin

### User Input Controls

**Buttons and Switch** (all connected to Arduino GND Bus):

- Arduino Pin D2 → Mode Button

- Arduino Pin D3 → Submode Button

- Arduino Pin D4 → On/Off Switch (integrated in potentiometer)

**Potentiometer (Brightness Control):**

- Arduino Pin A0 → Middle Pin of Potentiometer

- Outer pins connect to Arduino 5V and GND Busses

## Wiring Diagram

```markdown
External 5V 4A Power Supply
├── VIN (Arduino)
├── +5V → LED Panel 1
└── +5V → LED Panel 2

Arduino Uno/R4 Minima
├── D11 (MOSI) → LED Panel 1 DI
├── D13 (SCK) → LED Panel 1 CI
├── A4 (SDA) → RTC SDA
├── A5 (SCL) → RTC SCL
├── D2 → Mode Button
├── D3 → Submode Button
├── D4 → Power Switch
└── A0 → Potentiometer Wiper

LED Panel 1 → LED Panel 2
├── DO → DI
└── CO → CI

Common Ground Network
├── Power Supply (-)
├── Arduino GND
├── LED Panel 1 GND
├── LED Panel 2 GND
├── RTC GND
├── Buttons (switched to ground)
└── Potentiometer (outer pin)
```

## Important Notes

### Power Considerations

- **Never power LEDs directly from Arduino's 5V pin** - use external supply

- **Ensure common ground** between all components for proper communication

- **Total LED current** can exceed 5A at full brightness (128 LEDs × 40mA)

- **LED heat dissipation** at full brightness can be significant

### Signal Integrity

- Keep data and clock lines as short as possible

- Avoid routing power lines near sensitive signal lines

- Use proper wire gauge for high-current LED connections

---

**Safety Note**: Always disconnect power before making or changing wiring connections. Double-check polarity before applying power to sensitive components.
