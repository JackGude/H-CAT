---
layout: default
title: Hardware Overview
nav_order: 2
parent: Hardware
has_children: false
---


## Overview

The H-CAT hardware is carefully selected to balance performance, cost, and size constraints while delivering an engaging visual experience through the Pepper's Ghost holographic illusion.

## Core Components

### Arduino R4 Minima

**Primary microcontroller responsible for:**

- Running all firmware and managing display modes

- Processing sensor inputs and user interactions

- Handling real-time clock communication

- Controlling LED matrix rendering

**Selection Rationale:**

- Significant memory upgrade from Uno R3 (32KB SRAM vs 2KB)

- Improved processing performance for complex animations

- Backward compatibility with existing Uno codebase

- Same form factor for easy integration

### Adafruit DotStar RGB LED Matrix - 8x8 (x2)

**Display system configuration:**

- Two 8x8 (64-pixel) matrices daisy-chained to form 16x8 canvas

- High-brightness LEDs for vivid holographic projection

- Individual pixel addressing for complex patterns

**Selection Rationale:**

- Compact 1"×1" form factor perfect for desktop display

- Superior brightness compared to NeoPixels for holographic effect

- SPI interface for fast, reliable communication

### DS3231 Precision Real-Time Clock (RTC) Module

**Timekeeping capabilities:**

- Temperature-compensated crystal oscillator

- Battery backup for time retention during power loss

- I2C communication interface

- ±2ppm accuracy (±1 minute per year)

## Power System

### 5V 4A DC Wall Adapter Power Supply

**Primary power source providing:**

- Stable 5V output at up to 4 amps

- Sufficient current for full-brightness LED operation

- Reliable power for continuous operation

**Power Requirements Analysis:**

- Maximum LED current: 128 LEDs × 40mA = 5.12A

- Maximum working load: 4A/5.12A = 78.125%

- Arduino current: ~100mA

### Power Distribution Architecture

**USB-C Integration:**

- USB-C to barrel jack adapter for modern connectivity

- Internal power distribution board for clean wiring

- Common ground network for all components

**Power Busses:**

- High-current bus: External 5V for LED matrices

- Low-current bus: Arduino 5V for sensitive components

- Isolated grounds to prevent noise interference

## User Interface

### Dual Linear Potentiometer with Integrated Switch

**Multi-function control:**

- Potentiometer: Brightness control (16 levels)

- Integrated switch: Main power toggle

- Panel-mount design for clean installation

**Interface Design:**

- Smooth, analog brightness adjustment

- Positive detent for power on/off position

- Compact form factor and dual functionality

### Momentary Panel Mount Pushbuttons (x2)

**Mode navigation controls:**

- Mode button: Cycle through primary display modes

- Submode button: Access mode-specific options

- Tactile feedback for positive user experience

**Button Implementation:**

- Active-low configuration with internal pull-ups

- Debounced in software for reliable operation

## Enclosure & Optical System

### 3D Printed PLA Enclosure

**Structural design:**

- Custom-designed for optimal component placement

- Internal chamber separation for electronics and display

- Matte black interior for light absorption

- Compact dimensions (Target: 2.5"×2.5"×4")

**Design Features:**

- Two-chamber layout isolates power electronics from display

- Removable back panel with magnetic attachment

- Integrated mounting points for all components

- Ventilation channels for heat dissipation

### Pepper's Ghost Optical System

**Holographic illusion components:**

- 3mm clear acrylic reflector at 33° angle

- Optimized for desk-level viewing (1.3ft eye level)

- Matte black interior for contrast enhancement

**Optical Design:**

- Downward-facing LED matrices for hidden light source

- Angled reflector projects "floating" image

- Carefully calculated geometry for convincing illusion

### Internal Weighting System

**Stability enhancement:**

- Iron wheel weights concealed in base

- Low center of gravity for tip resistance

- Premium feel despite lightweight construction

## Component Layout

### Display Chamber (Front Half)

- LED matrices mounted on top interior surface

- Acrylic reflector at specified angle

- Front aperature size optimized for viewing

### Electronics Chamber (Rear Half)

- Arduino mounted on removable back panel

- Power distribution board with standoff mounting

- RTC module and input controls on roof panel

- Weight system integrated into base

### Cable Management

- Organized wire routing channels

- Strain relief for external connections

- Serviceable design for maintenance access

## Bill of Materials

| Component | Quantity | Cost (USD) | Notes |
| ----------- | ---------- | ------------ | ------- |
| Arduino R4 Minima | 1 | ~$20 | Main controller |
| DotStar 8x8 Matrix | 2 | ~$25 | LED display |
| DS3231 RTC Module | 1 | ~$18 | Timekeeping |
| 5V 4A Power Supply | 1 | ~$8 | External power |
| USB-C Barrel Adapter | 1 | ~$2 | Power interface |
| Potentiometer w/Switch | 1 | ~$2 | Brightness/power |
| Panel Pushbuttons | 2 | ~$1 | Mode controls |
| Acrylic Sheet | 1 | ~$16 | Reflector |
| Iron Weights (60oz) | 1 | ~$17 | Stability |
| **Total** | | **~$135** | **Prototype cost** |

---

## Design Philosophy

The H-CAT hardware embodies several key engineering principles:

1. **Modularity**: Each subsystem can be independently tested and replaced
2. **Scalability**: Architecture supports future feature additions
3. **Serviceability**: Designed for maintenance and modification
4. **Aesthetics**: Professional appearance suitable for portfolio display
5. **Reliability**: Robust power management and error handling

This hardware foundation enables sophisticated software features while maintaining a precise, compact form factor.
