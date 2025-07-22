#include "Timekeeping.h"
#include <Arduino.h>
#include "RTC.h"       // Include the R4's built-in RTC library (RTC.h)

// No need to define our own 'rtc' object, as `RTC` (capitalized) is global.
bool rtc_found = false;

// --- Helper function to parse __DATE__ and __TIME__ into RTCTime ---
RTCTime getCompileTime() {
    // __DATE__ is "Mmm dd yyyy" (e.g., "Jul 22 2025")
    // __TIME__ is "hh:mm:ss"

    // Parse __DATE__
    int year = atoi(__DATE__ + 7); // "Jul 22 2025" -> "2025"
    int day = atoi(__DATE__ + 4);  // "Jul 22 2025" -> "22"
    
    // Parse month string to int enum Month
    Month month;
    char monthStr[4];
    strncpy(monthStr, __DATE__, 3);
    monthStr[3] = '\0'; // Null-terminate
    if (strcmp(monthStr, "Jan") == 0) month = Month::JANUARY;
    else if (strcmp(monthStr, "Feb") == 0) month = Month::FEBRUARY;
    else if (strcmp(monthStr, "Mar") == 0) month = Month::MARCH;
    else if (strcmp(monthStr, "Apr") == 0) month = Month::APRIL;
    else if (strcmp(monthStr, "May") == 0) month = Month::MAY;
    else if (strcmp(monthStr, "Jun") == 0) month = Month::JUNE;
    else if (strcmp(monthStr, "Jul") == 0) month = Month::JULY;
    else if (strcmp(monthStr, "Aug") == 0) month = Month::AUGUST;
    else if (strcmp(monthStr, "Sep") == 0) month = Month::SEPTEMBER;
    else if (strcmp(monthStr, "Oct") == 0) month = Month::OCTOBER;
    else if (strcmp(monthStr, "Nov") == 0) month = Month::NOVEMBER;
    else if (strcmp(monthStr, "Dec") == 0) month = Month::DECEMBER;
    else month = Month::JANUARY; // Fallback

    // Parse __TIME__
    int hour = atoi(__TIME__);        // "HH:MM:SS" -> "HH"
    int minute = atoi(__TIME__ + 3);  // "HH:MM:SS" -> "MM"
    int second = atoi(__TIME__ + 6);  // "HH:MM:SS" -> "SS"

    // Create RTCTime object. DayOfWeek and SaveLight can be default placeholders.
    return RTCTime(day, month, year, hour, minute, second, DayOfWeek::SUNDAY, SaveLight::SAVING_TIME_INACTIVE);
}


void setupTime() {
  Serial.println("  - Initializing R4 Built-in RTC...");

  RTC.begin(); // Initialize the built-in RTC peripheral
  rtc_found = true; 

  // Setting RTC time from system time
  RTCTime compileTime = getCompileTime();
  RTC.setTime(compileTime);

  Serial.print("  - R4 RTC set to: ");
  Serial.print(compileTime.getYear()); Serial.print("-"); Serial.print(Month2int(compileTime.getMonth())); Serial.print("-"); Serial.print(compileTime.getDayOfMonth());
  Serial.print(" "); Serial.print(compileTime.getHour()); Serial.print(":"); Serial.print(compileTime.getMinutes()); Serial.print(":"); Serial.println(compileTime.getSeconds());
  
  Serial.println("  - R4 Built-in RTC Initialized.");
}

// Function to print current R4 time (from previous step)
void printCurrentR4Time() {
  if (rtc_found) {
    RTCTime currentTime;
    RTC.getTime(currentTime); // Use RTC.getTime() to retrieve current time into an RTCTime object

    Serial.print("R4 RTC Raw Time: ");
    Serial.print(currentTime.getYear());
    Serial.print("-");
    Serial.print(Month2int(currentTime.getMonth())); // Month2int is in RTC.h
    Serial.print("-");
    Serial.print(currentTime.getDayOfMonth());
    Serial.print(" ");
    Serial.print(currentTime.getHour());
    Serial.print(":");
    Serial.print(currentTime.getMinutes()); // Corrected from getMinute()
    Serial.print(":");
    Serial.println(currentTime.getSeconds());
  } else {
    Serial.println("R4 RTC not found/initialized.");
  }
}