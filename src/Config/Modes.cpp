#include "Modes.h"
#include "State.h"
#include "Hardware/Display.h"
#include <Arduino.h>

// Include the mode-specific headers
#include "Modes/ClockMode.h"
#include "Modes/GoLMode.h"
#include "Modes/DLAMode.h"

// --- MODE DEFINITIONS ---
const int NUM_MODES = 3;
const Mode modes[NUM_MODES] = {
  // { "Name", Num Submodes, Init Function, Display Function }
  { "Clock", 5, &initClock, &displayClock },
  { "Game of Life", 6, &initGoLSim, &displayGoLSim },
  { "Art", 5, &initDLASim, &displayDLASim }
};

void runCurrentMode() {
  static int lastModeIndex = -1;

  if (state.currentModeIndex != lastModeIndex) {
    Serial.print("DEBUG: Mode changed to: "); Serial.println(modes[state.currentModeIndex].name);
    if (modes[state.currentModeIndex].initFunction != nullptr) {
      modes[state.currentModeIndex].initFunction();
    }
    lastModeIndex = state.currentModeIndex;
  }

  int newBrightness = state.brightness * 255;
  strip.setBrightness(newBrightness);

  modes[state.currentModeIndex].displayFunction();

  strip.show();
}