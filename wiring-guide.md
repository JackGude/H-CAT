Desktop Projector Wiring Guide

This document outlines the wiring connections for the Arduino, both LED panels, the RTC module, and all input components. A common ground is essential for all components to communicate correctly.
1. Power Distribution

The external 5V power supply is the primary source of power for the LEDs and the Arduino. We have a separate 5V bus on a breadboard, powered by the Arduino, for more sensitive low-current components.

    

    Power Supply (+) Positive Terminal:

        Connect to the VIN pin on the Arduino.

        Connect to the +5V pin on LED Panel 1.

        Connect to the +5V pin on LED Panel 2.

    Power Supply (-) Negative/Ground Terminal:

        Connect to a GND pin on the Arduino. (This creates the essential common ground.)

        Connect to the GND pin on LED Panel 1.

        Connect to the GND pin on LED Panel 2.
    
    Arduino

        5V to Arduino 5V Bus.

        GND to Arduino GND Bus.


2. LED Panel Connections

The two LED panels are chained together. The Arduino talks to the first panel, which then passes the signal to the second.

    Arduino Connections:

        Arduino Pin D11 (MOSI) → Data In (DI) on LED Panel 1.

        Arduino Pin D13 (SCK) → Clock In (CI) on LED Panel 1.

    Panel-to-Panel Connection:

        LED Panel 1 Data Out (DO) → LED Panel 2 Data In (DI).

        LED Panel 1 Clock Out (CO) → LED Panel 2 Clock In (CI).

3. Component Connections (to Arduino)

These are the lower-power components that are controlled by and receive power from the Arduino itself.

    Real-Time Clock (RTC) Module:

        Arduino 5V Bus → RTC VCC (or 5V) Pin.

        Arduino GND Bus → RTC GND Pin.

        Arduino Pin A4 (SDA) → RTC SDA Pin.

        Arduino Pin A5 (SCL) → RTC SCL Pin.

    Buttons & Switch:
    (All connected to Arduino GND Bus)

        Arduino Pin D2 → Mode Button.

        Arduino Pin D3 → Submode Button.

        Arduino Pin D4 → On/Off Switch.

    Potentiometer (Dial):

        Arduino Pin A0 → Middle Pin of Potentiometer.

        (The other two pins of the potentiometer connect to 5V and GND Busses from the Arduino).