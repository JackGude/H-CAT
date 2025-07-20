# Environment Setup:

Install your chosen IDE (Arduino IDE or PlatformIO on VS Code) on Pop!_OS.

Connect your Arduino and confirm you can upload a basic "Blink" sketch to it. Make sure you can see its output on the Serial Monitor.

# Basic Input & State "Skeleton":

Wire up your buttons and potentiometer to the Arduino.

Write the skeleton code: Define the ProjectorState struct and the setup() and loop() functions.

In setup(), initialize Serial communication. For now, just set default state values.

In loop(), read the button and potentiometer values. Use the Serial Monitor to print these raw values. This confirms your wiring is correct.

# Implement Input Logic & Persistence:

Add debouncing logic for the buttons. A simple millis()-based check is a good start.

Implement the full Input-to-Action Mapping from the table above.

After each action that changes the state (like changing a mode or theme), print the new state to the Serial Monitor (e.g., "Mode changed to: 1").

Integrate the saveState() and loadState() EEPROM functions. After a value changes and you save it, restart the Arduino and verify the state is loaded correctly.

# Develop Mode 1: The Clock:

Connect your RTC module.

Using a library like "RTClib," write the updateClock() function. Start simple: just get the time from the RTC and print it to the Serial Monitor.

Once that works, you can start thinking about how to visually represent that data for the projector.
