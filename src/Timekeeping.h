#ifndef TIMEKEEPING_H
#define TIMEKEEPING_H

#include "RTClib.h"

// Declare the RTC object and a status flag so other files can use them.
extern RTC_DS3231 rtc;
extern bool rtc_found;

// Function to initialize the RTC module
void setupTime();

#endif // TIMEKEEPING_H
