#include <Arduino.h>
#include "Display.h"     // Our display functions
#include "Timekeeping.h" // Our new timekeeping functions
#include "Input.h"       // Our input handling functions
#include "State.h"       // Our state struct
#include "Modes.h"       // Our modes struct and runCurrentMode function
#include "Persistence.h" // Our persistence functions
#include <EEPROM.h>      // Include EEPROM library here for direct access

// Define the global state object.
ProjectorState state;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("--- Projector Booting Up (Attempting EEPROM Recovery) ---");

  // Attempt to load state from EEPROM
  EEPROM.get(0, state); // This loads directly into the global 'state' object

  // Validate loaded state. If invalid, reset to defaults and save.
  // We check bounds for currentModeIndex and brightness.
  // NUM_MODES is defined in Modes.h (and Modes.cpp).
  if (state.currentModeIndex >= NUM_MODES || state.currentModeIndex < 0 || state.brightness > 1.0 || state.brightness < 0.0) {
      Serial.println("WARNING: Loaded EEPROM state appears invalid. Resetting to defaults.");
      // Initialize state with default values (matching ProjectorState struct initializers)
      state.isOn = true;
      state.brightness = 1.0;
      state.currentModeIndex = 0;
      // Ensure all submode indices are valid for their respective modes' default setup
      // Assuming ClockMode is mode 0 with 5 submodes, others 0 for safety initially.
      for(int i = 0; i < sizeof(state.modeSubmodeIndices)/sizeof(state.modeSubmodeIndices[0]); i++) {
        state.modeSubmodeIndices[i] = 0;
      }
      state.currentThemeIndex = 0;
      state.customColor = {255, 255, 255};
      saveState(); // Save these fresh defaults back to EEPROM
      Serial.println("INFO: Defaults applied and saved to EEPROM.");
  } else {
    Serial.println("INFO: Loaded EEPROM state is valid.");
  }

  Serial.println("INFO: EEPROM load/validation complete.");

  // Initialize hardware
  setupTime();       // Initializes RTC
  setupDisplay();    // Initializes LED strip
  setupInputs();     // Initializes buttons and potentiometer

  // Apply initial brightness *after* state is loaded and display is setup
  strip.setBrightness(state.brightness * 255); // Assumes DotStar.setBrightness takes 0-255

  Serial.println("Setup complete. Entering main loop.");
}

void loop() {
  // Handle all button and dial inputs
  handleInputs();

  // Run the currently selected display mode logic
  runCurrentMode();

  // --- Time Logic (Keep for debugging) ---
  // if (rtc_found) { // Checks if RTC was found
  //   static int lastPrintedSecond = -1;
  //   DateTime now = rtc.now(); // Gets current time from RTC
  //   if (now.second() != lastPrintedSecond) {
  //     Serial.print("RTC Time: ");
  //     Serial.print(now.hour());
  //     Serial.print(":");
  //     if(now.minute() < 10) Serial.print('0');
  //     Serial.print(now.minute());
  //     Serial.print(":");
  //     if(now.second() < 10) Serial.print('0');
  //     Serial.println(now.second());
  //     lastPrintedSecond = now.second();

  //     // Debugging Input State - Keep this for now to ensure inputs are still working
  //     Serial.print("Mode: "); Serial.print(state.currentModeIndex);
  //     Serial.print(" Submode["); Serial.print(state.currentModeIndex); Serial.print("]: "); Serial.print(state.modeSubmodeIndices[state.currentModeIndex]);
  //     Serial.print(" Brightness: "); Serial.println(state.brightness);
  //     Serial.print(" Theme: "); Serial.print(state.currentThemeIndex);
  //     Serial.print(" Custom Color: "); Serial.print(state.customColor.r); Serial.print(","); Serial.print(state.customColor.g); Serial.print(","); Serial.println(state.customColor.b);
  //   }
  // }
}