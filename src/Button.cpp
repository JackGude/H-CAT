#include "Button.h"

Button::Button(uint8_t pin) {
  _pin = pin;
}

void Button::begin() {
  pinMode(_pin, INPUT_PULLUP);
}

void Button::update() {
  // Reset the one-shot tap flag at the beginning of each update cycle.
  _wasTapped = false;

  int currentReading = digitalRead(_pin);

  // If the physical state of the button changes, reset the timer.
  if (currentReading != _lastReading) {
    _pressStartTime = millis();
  }

  // After the debounce delay, we can trust the reading.
  if ((millis() - _pressStartTime) > _debounceDelay) {
    // If the debounced state has changed, it's a confirmed press or release.
    if (currentReading != _debouncedState) {
      _debouncedState = currentReading;

      if (_debouncedState == LOW) {
        // --- BUTTON WAS JUST PRESSED ---
        // Reset the hold flag for this new press cycle.
        _isHeldFlag = false;
      } else {
        // --- BUTTON WAS JUST RELEASED ---
        // If it wasn't considered a hold, then it must have been a tap.
        if (!_isHeldFlag) {
          _wasTapped = true;
        }
      }
    }
  }
  _lastReading = currentReading;

  // Check for a hold condition.
  // If the button is physically down and hasn't been flagged as a hold yet...
  if (_debouncedState == LOW && !_isHeldFlag) {
    // ...and it has been down for longer than the threshold...
    if ((millis() - _pressStartTime) > _holdThreshold) {
      // ...then it's officially a hold.
      _isHeldFlag = true;
    }
  }
}

bool Button::wasTapped() {
  return _wasTapped;
}

bool Button::isHeld() {
  // The button is considered "held" only if it's currently physically pressed
  // AND the hold threshold has been passed for this press cycle.
  return (_debouncedState == LOW && _isHeldFlag);
}
