#include <Arduino.h>
#include "Hardware/Display.h"
#include "Services/Timekeeping.h"
#include "Hardware/Input.h"
#include "Config/State.h"
#include "Config/Modes.h"
#include "Services/Persistence.h"
#include <EEPROM.h>
#include "RTC.h"
#include "RTClib.h"

// This pin is also defined in Input.cpp. For a future improvement,
// consider moving all pin definitions to a single "HardwarePins.h" header.
const int ON_OFF_PIN = 4;

// Define the global state object.
ProjectorState state;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("--- Projector Booting Up ---");

  // --- FIX: Initialize inputs and check power switch FIRST ---
  setupInputs();
  bool isPowerSwitchOn = (digitalRead(ON_OFF_PIN) == LOW);

  // Attempt to load the rest of the state from EEPROM
  EEPROM.get(0, state);

  // --- FIX: Immediately override the loaded 'isOn' state with the physical switch's actual state ---
  state.isOn = isPowerSwitchOn;

  // Validate loaded state. If invalid, reset to defaults.
  if (state.currentModeIndex >= NUM_MODES || state.currentModeIndex < 0 || state.brightness > 1.0 || state.brightness < 0.0) {
      Serial.println("WARNING: Loaded EEPROM state appears invalid. Resetting to defaults.");
      // Note: state.isOn is already correctly set from the physical switch, so we don't reset it here.
      state.brightness = 1.0;
      state.currentModeIndex = 0;
      for(int i = 0; i < sizeof(state.modeSubmodeIndices)/sizeof(state.modeSubmodeIndices[0]); i++) {
        state.modeSubmodeIndices[i] = 0;
      }
      state.currentThemeIndex = 0;
      state.customColor = {255, 255, 255};
      
      // Only save the new default state if the switch is on.
      if (state.isOn) {
        saveState();
        Serial.println("INFO: Defaults applied and saved to EEPROM.");
      }
  } else {
    Serial.println("INFO: Loaded EEPROM state is valid.");
  }

  // Initialize the rest of the hardware
  setupTime();
  setupDisplay();

  // Apply initial brightness only if the device is supposed to be on
  if (state.isOn) {
    strip.setBrightness(state.brightness * 255);
  } else {
    // If off, ensure the display is blank and brightness is zero
    strip.setBrightness(0);
    strip.clear();
    strip.show();
  }

  Serial.println("Setup complete. Entering main loop.");
}

void loop() {
  handleInputs();

  if (state.isOn) {
    runCurrentMode();
  } else {
    // To be safe, ensure the strip is off if the state was toggled off during runtime.
    strip.clear();
    strip.show();
    delay(100); // A small delay to prevent the loop from spinning too fast when off.
  }
}