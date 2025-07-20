#include "Timekeeping.h"
#include <Arduino.h>

// Define the RTC object and its status flag
RTC_DS3231 rtc;
bool rtc_found = false;

void setupTime() {
  // Initialize the RTC, but do not halt if it fails.
  if (rtc.begin()) {
    Serial.println("  - RTC found successfully.");
    rtc_found = true;
  } else {
    Serial.println("  - ERROR: Couldn't find RTC! Clock will not work.");
    rtc_found = false;
  }

  // Set the time automatically if the RTC has lost power
  if (rtc_found && rtc.lostPower()) {
    Serial.println("  - RTC lost power, setting time to compile time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}
