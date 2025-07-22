#include "Modes.h"
#include "State.h"
#include "Display.h"
#include <Arduino.h>

// Include the mode-specific headers
#include "ClockMode.h"
#include "CAMode.h"
#include "ArtMode.h"

// --- MODE DEFINITIONS ---
const int NUM_MODES = 3;
const Mode modes[NUM_MODES] = {
  // { "Name", Num Submodes, Init Function, Display Function }
  { "Clock", 5, &initClock, &displayClock },
  { "Cellular Automata", 6, &initCellularAutomata, &displayCellularAutomata },
  { "Art", 3, &initArt, &displayArt }
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