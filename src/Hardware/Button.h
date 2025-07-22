#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
public:
  // Constructor: Initializes the button on a specific pin.
  Button(uint8_t pin);

  // Must be called in setup() to set the pin mode.
  void begin();

  // Must be called on every loop to read the button's state.
  void update();

  // Returns true for ONE loop cycle when the button is tapped (pressed and released quickly).
  bool wasTapped();

  // Returns true continuously while the button is being held down past the hold threshold.
  bool isHeld();

private:
  uint8_t _pin; // The hardware pin the button is connected to

  // Timing constants
  const long _debounceDelay = 10;
  const long _holdThreshold = 500;

  // State-tracking variables
  long _pressStartTime = 0;
  bool _wasTapped = false;
  bool _isHeldFlag = false; // Tracks if the button has passed the hold threshold in the current press
  int _lastReading = HIGH;
  int _debouncedState = HIGH;
};

#endif // BUTTON_H
