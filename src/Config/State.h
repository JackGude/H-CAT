#ifndef STATE_H
#define STATE_H

#include <Arduino.h>

struct ProjectorState {
  bool isOn = true;
  float brightness = 1.0;
  int currentModeIndex = 0;
  int modeSubmodeIndices[3] = {0, 0, 0};
  int currentThemeIndex = 0;
  struct {
    uint8_t r, g, b;
  } customColor = {255, 255, 255};
};

extern ProjectorState state; // Declare it as extern

#endif // STATE_H