#ifndef TIMEKEEPING_H
#define TIMEKEEPING_H

// #include "RTClib.h"   // Not needed here for this step
// #include "RTC.h"      // Not needed here for this step

extern bool rtc_found;   // Flag to indicate if RTC is functional

// Function to initialize the RTC module
void setupTime();

// Function to get current time as string (for simple testing)
// We won't return DateTime object yet, to keep it simple
void printCurrentR4Time();

#endif // TIMEKEEPING_H