---
layout: default
title: H-CAT
nav_order: 1
---

H-CAT: Holographic Cellular Automata Toy

![H-CAT Status](https://img.shields.io/badge/Status-Working%20Prototype-green)
![Platform](https://img.shields.io/badge/Platform-Arduino%20R4%20Minima-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B-orange)

A compact desktop display featuring cellular automata simulations, generative art, and a precision clock, all brought to life through a Pepper's Ghost holographic illusion.

## Project Overview

H-CAT started as a computer engineering student project. I wanted to get more experience working in the real world, and to build up my electronics / EE skills. I've always enjoyed making things so I just wanted to make "something" that would be beautiful and/or useful (ideally both) and since I don't have a lot of space, it needs to be compact and unobtrusive.

## Key Features

- **Three Display Modes**: Cellular Automata, Generative Art, and Precision Clock
- **Holographic Illusion**: Pepper's Ghost effect with LED matrix projection
- **Compact Design**: 3D printed enclosure optimized for desk use
- **Professional Build**: Clean electronics integration and user interface

## Quick Start

```bash
# Clone the repository
git clone https://github.com/jackgude/H-CAT.git
cd H-CAT

# Open in Arduino IDE
# - Select Arduino R4 Minima board
# - Upload the firmware from src/
```

## Hardware Highlights

- **Arduino R4 Minima** - Main controller with 32KB SRAM
- **2x Adafruit DotStar 8x8 LED Matrices** - 128-pixel display canvas
- **DS3231 RTC Module** - Precision timekeeping
- **Custom 3D Printed Enclosure** - Optimized for Pepper's Ghost reflection effect
- **Interface** - Mode and brightness controls via buttons and potentiometer dial

## Project Documentation

This site contains comprehensive documentation for the H-CAT project:

- [Hardware Overview](hardware-overview.md) - Complete component analysis and design
- [Wiring Guide](wiring-guide.md) - Detailed connection diagrams and instructions
- [Software Architecture](software-architecture.md) - Firmware design and implementation
- [Challenges & Solutions](challenges-solutions.md) - Technical hurdles and learning experiences
- [Gallery](gallery.md) - Visual documentation of the development process
- [Future Work](future-work.md) - Enhancement ideas and development roadmap

## Development Status

✅ **Completed**: Working prototype with all core features implemented  
🔄 **In Progress**: 3D printed enclosure design and fabrication  

---

**Summer 2025 Engineering Project** | Developed as a portfolio piece showcasing embedded systems development, hardware integration, and creative engineering problem-solving.
