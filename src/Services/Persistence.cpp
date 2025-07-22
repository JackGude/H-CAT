#include "Persistence.h"
#include "Config/State.h"      // Needs to know about the ProjectorState struct
#include <EEPROM.h>     // Arduino's EEPROM library
#include <Arduino.h>    // For Serial

// Saves the current global 'state' object to EEPROM memory.
void saveState() {
  Serial.println("INFO: Saving state to EEPROM...");
  EEPROM.put(0, state);
  Serial.println("INFO: Save complete.");
}

// Loads the state from EEPROM into the global 'state' object.
void loadState() {
  Serial.println("INFO: Loading state from EEPROM...");
  EEPROM.get(0, state);
  Serial.println("INFO: Load complete.");
}
