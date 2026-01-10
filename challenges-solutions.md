---
layout: default
title: Challenges & Solutions
nav_order: 5
parent: Project Documentation
has_children: false
---

Developing H-CAT presented several interesting technical and design challenges. Overcoming these hurdles was a key learning experience in this project.

## Power Management Solutions

**Challenge:** The 128 LEDs can draw significantly more current than the Arduino Uno's onboard 5V regulator or USB port can safely supply. Directly powering the LEDs from the Uno's 5V pin would likely damage the board.

**Solution:** This challenge led to an improved system design with an embedded USB-C port instead of a dedicated external power cable. The solution incorporates:

- External 5V 4A DC wall adapter power supply for both LEDs and Arduino

- USB-C port integration for modern connectivity

- Internal power distribution via barrel jack adapter

- Common ground network ensuring proper communication between all components

**Learning:** Emphasized the critical importance of proper power budgeting and distribution in embedded systems, especially when dealing with high-power components.

## User Interface Design

**Challenge:** Designing an intuitive control scheme for multiple modes and custom settings with limited physical controls, while ensuring user preferences persist between power cycles.

**Solution:** Implemented a finite state machine architecture with:

- Mode button for cycling through primary display modes

- Submode button for accessing mode-specific options

- Switched potentiometer controlling both brightness and power functionality

- EEPROM storage for brightness, mode, and color settings persistence

**Learning:** Gained extensive experience with embedded systems design, finite state machine implementation, and EEPROM usage for persistent user preferences.

## Enclosure Design

**Challenge:** The enclosure needed to:

- Organize all electronic components precisely for the optical effect

- Maintain compact dimensions while allowing component access

- Provide structural integrity and professional appearance

**Solutions:** The design evolved from a wooden puzzle box construction to 3D printing:

**Initial Approach (Wood):**

- Complicated hand-carved puzzle box design

- Splined butt joints for structural reinforcement

- Two-chamber layout separating electronics and display

**Final Solution (3D Printed):**

- Access to school 3D printer enabled design improvement

- CAD-designed enclosure with precise component placement

- Extremely compact dimensions optimized for Arduino footprint

- Removable magnetic back panel for Arduino access

- Integrated ventilation channels for heat dissipation

**Learning:** Gained practical experience in project planning, design iteration, working within constraints, and modern fabrication methods.

## Holographic Illusion Implementation

**Challenge:** Creating a convincing Pepper's Ghost effect requires precise positioning of light source, reflector, and ambient light control within a compact form factor.

**Solution:** Optical engineering approach with:

**Enclosure Design:**

- Downward-facing DotStar matrices hidden in top interior

- Dark, non-reflective chamber to minimize stray light

- Acrylic reflector mounted on bottom interior

**Optical Calculations:**

- Reflector angle optimized at 33° above horizontal (reduced from 45°)

- Calculated for desk-level viewing (arms length, 1.3ft eye height)

- Precise geometric alignment for convincing "floating" illusion

**Learning:** Reinforced principles of optics, 3D spatial design, and understanding of material properties on visual effects.

## Memory Management Challenges

**Challenge:** Both RAM and Flash memory were exhausted on the Arduino Uno R3. While all three modes ran minimally on a single screen, adding the second screen caused memory overflow.

**Solutions:**

**Long-term Strategy:**

- Upgrade from Uno R3 to R4 Minima

- Expands memory from 2KB SRAM to 32KB SRAM

- Minimal code changes required for compatibility

**Short-term Workaround:**

- Disabled extra modes to develop one at a time

- Moved custom font to flash memory to free RAM

- Optimized data structures and code organization

**Learning:** Gained valuable experience working at embedded memory limits and understanding memory hierarchy in microcontroller systems.

## Hardware-Specific Bug Resolution

**Challenge:** Encountered severe performance degradation when using the Arduino random number library on the R4 Minima, causing massive slowdowns in display updates.

**Solution:** After online research confirmed this as a known R4 Minima hardware issue:

- Implemented custom random number generator

- Used analog signal from floating pin as entropy source

- Bypassed problematic hardware random number generator

- Restored normal system performance

**Learning:** Gained experience troubleshooting hardware-specific software issues and implementing workarounds for platform limitations.
