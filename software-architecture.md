---
layout: default
title: Software Architecture
nav_order: 4
parent: Software
has_children: false
---


## Overview

The H-CAT firmware is built around a finite state machine architecture that cleanly separates the three main display modes while maintaining responsive user interaction and efficient resource utilization on the Arduino platform.

## Core Architecture

### Finite State Machine Design

The software operates as a state machine with three primary modes:

- **Clock Mode**: Real-time display with custom typography

- **Cellular Automata Mode**: Conway's Game of Life

- **Generative Art Mode**: Algorithmic patterns and evolving visual displays via diffusion-limited aggregation (DLA)

Each mode maintains its own state and rendering logic while sharing common hardware abstraction layers.

### Key Components

#### Hardware Abstraction Layer

```cpp
// LED Matrix Management
class DotStarController {
  void setPixel(uint8_t x, uint8_t y, uint32_t color);
  void show();
  void clear();
};

// RTC Interface  
class RTCManager {
  DateTime getTime();
  void setTime(DateTime time);
};
```

#### Input Management

```cpp
// Button and Potentiometer Handling
class InputManager {
  bool modeButtonPressed();
  bool submodeButtonPressed();
  uint8_t getBrightnessLevel();
  bool isPowerOn();
};
```

#### EEPROM Storage

```cpp
// Persistent User Preferences
struct UserSettings {
  uint8_t brightness;
  uint8_t currentMode;
  uint8_t colorScheme;
  bool powerOnState;
};
```

## Memory Management

### Optimization Strategies

Given the constrained memory environment of Arduino Uno/R4:

- **PROGMEM Storage**: Static data and font bitmaps stored in flash memory

- **Dynamic Allocation**: Minimal heap usage, primarily stack-based operations

- **Code Reuse**: Shared rendering functions across modes to reduce binary size

### Memory Layout

```markdown
Flash Memory: ~28KB

- Core firmware: ~20KB

- Font data: ~4KB  

- Pattern tables: ~3KB

- Buffer: ~1KB

RAM Usage: ~1.5KB

- State variables: ~200B

- Display buffer: ~1KB

- Stack/heap: ~300B
```

## Mode Implementations

### Clock Mode

- Custom 3x6 font optimized for LED matrix display

- Multiple display formats:

- Calendar Display

- 12-hour format

- 24-hour format

- Binary Clock

### Cellular Automata Mode

- Efficient Game of Life implementation using bit manipulation

- Support for multiple rule sets

- Supports 3 separate games in RGB mode or one game in interactive mode

- Configurable speed

### Generative Art Mode

- Mathematical pattern generation

- Adjustable color scheme and pattern parameters

## User Interaction

### Control Scheme

- **Mode Button**: Cycle through primary modes

- **Submode Button**: Access mode-specific options

- **Potentiometer**: Brightness control & power toggle

### State Persistence

All user preferences are automatically saved to EEPROM:

- Last selected mode and submode

- Brightness level

- Color scheme preferences

- Power stateS

## Development Tools

### Build System

- Arduino IDE with PlatformIO compatibility

- Memory usage profiling tools

### Debug Interface

- Serial output for development debugging

- Performance monitoring and timing analysis

- Memory usage tracking

---

## Technical Challenges Solved

1. **Memory Constraints**: Optimized data structures and code organization to fit within Arduino limits
2. **Real-time Performance**: Ensured smooth animations without blocking user input
3. **Cross-platform Compatibility**: Code works on both Arduino Uno and R4 Minima
4. **Random Number Generation**: Custom implementation to work around R4 Minima hardware issues

## Future Enhancements

- WiFi connectivity for time synchronization

- Additional cellular automata rules

- More sophisticated generative art algorithms

- Mobile app integration for remote control
