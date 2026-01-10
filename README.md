# H-CAT: Holographic Cellular Automata Toy

A compact desktop display featuring generative art, cellular automata simulations, and a precision clock.

![H-CAT Device](https://img.shields.io/badge/Status-Working%20Prototype-green)
![Platform](https://img.shields.io/badge/Platform-Arduino%20Uno-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B-orange)

## Overview

H-CAT is an embedded engineering project that combines hardware design, firmware development, and optical physics to create an engaging desktop display. The device features three main modes:

- **Cellular Automata**: Conway's Game of Life and other rule-based simulations
- **Generative Art**: Algorithmic patterns and evolving visual displays  
- **Precision Clock**: Real-time display with custom typography

The holographic effect is achieved using downward-facing LED matrices reflected at an angle through a clear acrylic panel, creating an interesting floating display illusion.

## Quick Start

```bash
# Clone the repository
git clone https://github.com/jackgude/H-CAT.git
cd H-CAT

# Open in Arduino IDE
# - Select Arduino R4 Minima board
# - Upload the firmware from src/
```

## Hardware

- **Arduino R4 Minima** - Main controller
- **2x Adafruit DotStar 8x8 LED Matrices** - 128-pixel display canvas
- **DS3231 RTC Module** - Precision timekeeping
- **Custom 3D Printed Enclosure** - Optimized for Pepper's Ghost reflection effect
- **Interface** - Mode and brightness controls via buttons and potentiometer dial

## Technical Features

- **Finite State Machine Architecture** - Clean mode switching and user interaction
- **EEPROM Storage** - Persistent user preferences
- **Power Management** - External 5V 4A supply for high-current LED driving
- **Memory Optimization** - Efficient code structure for embedded constraints

## Project Documentation

📖 **Full Project Documentation**: [https://jackgude.github.io/H-CAT/](https://jackgude.github.io/H-CAT/)

The complete technical deep-dive includes:

- [Hardware Overview](https://jackgude.github.io/H-CAT/hardware-overview.html)
- [Wiring Guide](https://jackgude.github.io/H-CAT/wiring-guide.html)
- [Software Architecture](https://jackgude.github.io/H-CAT/software-architecture.html)
- [Challenges & Solutions](https://jackgude.github.io/H-CAT/challenges-solutions.html)
- [Gallery](https://jackgude.github.io/H-CAT/gallery.html)
- [Future Work](https://jackgude.github.io/H-CAT/future-work.html)

## Development Status

✅ **Completed**: Working prototype with all core features implemented  
🔄 **Next Steps**: 3D printed enclosure design and fabrication

---

**Summer 2025 Engineering Project** | Developed as a portfolio piece showcasing embedded systems development, hardware integration, and creative engineering problem-solving.
