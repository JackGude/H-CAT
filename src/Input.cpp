#include "Input.h" // <-- This now includes the new header
#include "State.h"
#include "Persistence.h"
#include "Modes.h"
#include "Themes.h"
#include "Utils.h"

// --- HARDWARE PIN DEFINITIONS ---
const int MODE_BUTTON_PIN = 2;
const int SUBMODE_BUTTON_PIN = 3;
const int ON_OFF_PIN = 4;
const int DIAL_PIN = A0;

// --- DEFINE BUTTON OBJECTS ---
// These lines create the actual button objects that the 'extern' declarations point to.
Button modeButton(MODE_BUTTON_PIN);
Button submodeButton(SUBMODE_BUTTON_PIN);

void setupInputs()
{
  modeButton.begin();
  submodeButton.begin();
  pinMode(ON_OFF_PIN, INPUT_PULLUP);
}

void handleInputs()
{
  bool powerSwitchOn = (digitalRead(ON_OFF_PIN) == LOW);
  state.isOn = powerSwitchOn;
  if (!state.isOn)
  {
    return;
  }

  // Update both buttons on every loop
  modeButton.update();
  submodeButton.update();

  // --- HANDLE TAPS ---
  if (modeButton.wasTapped())
  {
    state.currentModeIndex = (state.currentModeIndex + 1) % NUM_MODES;
    saveState();
  }

  if (submodeButton.wasTapped())
  {
    int currentMode = state.currentModeIndex;
    state.modeSubmodeIndices[currentMode] = (state.modeSubmodeIndices[currentMode] + 1) % modes[currentMode].numSubmodes;
    saveState();
  }

  // --- HANDLE HOLDS AND DIAL ---
  int dialValue = analogRead(DIAL_PIN);
  bool modeHeld = modeButton.isHeld();
  bool submodeHeld = submodeButton.isHeld();

  if (modeHeld && submodeHeld)
  {
    // Set Theme
    int newThemeIndex = map(dialValue, 0, 1023, 0, NUM_THEMES - 1);
    if (newThemeIndex != state.currentThemeIndex)
    {
      state.currentThemeIndex = newThemeIndex;
      saveState();
    }
  }
  else if (modeHeld)
  {
    // Set Custom Color
    state.currentThemeIndex = 0;
    uint8_t r, g, b;
    if (dialValue > 1000)
    {
      r = 255;
      g = 255;
      b = 255;
    }
    else
    {
      float hue = map(dialValue, 0, 1000, 0, 280);
      hsvToRgb(hue, 1.0, 1.0, r, g, b);
    }
    if (r != state.customColor.r || g != state.customColor.g || b != state.customColor.b)
    {
      state.customColor.r = r;
      state.customColor.g = g;
      state.customColor.b = b;
      saveState();
    }
  }
  else if (submodeHeld)
  {
    // Set Submode Directly
    int currentMode = state.currentModeIndex;
    int newSubmode = map(dialValue, 0, 1023, 0, modes[currentMode].numSubmodes - 1);
    if (newSubmode != state.modeSubmodeIndices[currentMode])
    {
      state.modeSubmodeIndices[currentMode] = newSubmode;
      saveState();
    }
  }
  else
  {
    // Control Brightness
    const int BRIGHTNESS_CUTOFF = 225;        // AnalogRead value below which brightness is 0 (approx 23% of 1023)
    const float MAX_LOWEND_BRIGHTNESS = 0.20; // Midpoint max brightness (20%)

    if (dialValue < BRIGHTNESS_CUTOFF)
    {
      state.brightness = 0.0; // Cut off, set to absolute 0 brightness
    }
    else
    {
      // Map the usable range (BRIGHTNESS_CUTOFF to 1023) to (0.0 to MAX_LOWEND_BRIGHTNESS)
      if (dialValue < (1000))
      {
        state.brightness = map(dialValue, BRIGHTNESS_CUTOFF, 1000, 0, (int)(1023 * MAX_LOWEND_BRIGHTNESS)) / 1023.0;
      }
      else
      {

        state.brightness = 1.0;
      }
    }
  }
}
