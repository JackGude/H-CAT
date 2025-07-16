---
layout: default
title: Hardware Overview - H-CAT
---

# Hardware Overview

## Core Components

* **Arduino Uno:**
    * The brain of the H-CAT, responsible for running all firmware, managing display modes, processing sensor inputs, and handling user interaction.
    * *Motivation:* Mainly, I have a couple on hand. They're cheap and easy to work with. They strike an interesting balance of size and power for this project. I wanted to see how much machine learning I can pull out of an Arduino.

* **Adafruit DotStar RGB LED Matrix - 8x8 (x2):**
    * These two 8x8 (64-pixel) matrices are daisy-chained to form a seamless 16x8 pixel canvas. They are the primary visual output for the holographic display.
    * *Motivation:* These were the components that finalized this project for me. I was shopping on Adafruit and saw these 1" x 1", super bright lil guys. They looked like candy in the pictures so that was that.

* **DS3231 Precision Real-Time Clock (RTC) Module:**
    * Provides accurate timekeeping capabilities, ensuring the H-CAT's clock mode remains precise even when the device is unpowered. Features an integrated temperature-compensated crystal for superior accuracy.
    * *Motivation:* Essential for Clock Mode

* **5V 4A DC Wall Adapter Power Supply:**
    * The main power source for the entire H-CAT system, providing a stable 5V at up to 4 amps to reliably drive the 128 DotStar LEDs and the Arduino Uno.
    * *Motivation:* The LEDs pull quite a bit of power, at full power this isn't actually enought to push them to 100% brightness and run the arduino. I don't plan to ever do that though, and Adafruit didn't have a 5V 5A adapter.

* **Power Adapters:**
    * USB-C to Barrel Jack Power Adapter
    * Barrel Jack to Positive and Negative Power Rails
    * *Motivation:* The idea here is to be able to put a port on the H-CAT. With this setup you should be able to just plug in the 5V4A USB-C cable and it will power the entire thing.
    
    
## User Interface Components

* **Dual Linear Potentiometer with Integrated On/Off Switch:**
    * Dual Purpose Component:
        * The potentiometer serves as the primary brightness control for the display.
        * The integrated switch will act as an on/off toggle for the device.
    * *Motivation:* Combines two essential controls into one compact panel-mount component.

* **Momentary Panel Mount Pushbuttons (x2):**
    * Dedicated buttons for cycling through main display modes and sub-modes, providing intuitive navigation of H-CAT's features.
    * *Motivation:* Provides clear, physical interaction points for mode selection.
## Enclosure & Illusion Components

* **1/8" MDF / Plywood:**
    * The primary material for the custom enclosure, providing structural integrity and a paintable surface for the desired aesthetic.
    * *Motivation:* Chosen for its cost-effectiveness, ease of workability with basic tools, and ability to be transformed visually.

* **Clear Acrylic Sheet (~ 3mm thick):**
    * The crucial component for creating the Pepper's Ghost holographic illusion. Positioned at a precise angle to reflect the downward-facing LEDs upwards towards the viewer.
    * *Motivation:* Offers excellent clarity and sufficient rigidity for the illusion, while being safer and easier to cut than glass.

* **Matte Black Paint / Internal Lining:**
    * Applied to the interior surfaces of the enclosure to absorb stray light and enhance the contrast of the holographic projection, making the illusion more convincing.
    * *Motivation:* Essential for the visual fidelity of the Pepper's Ghost effect.

* **Internal Weighting (Lead/Steel):**
    * Iron wheel weights are cheap and can be hidden in the base of the box. This provides a premium feel to the device and prevents it from being easily knocked over.
    * *Motivation:* Anchors the lightweight MDF/plywood box and adds to the perceived quality of the device.

---
