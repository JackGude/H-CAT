#include "ClockMode.h"
#include "Config/State.h"
#include "Hardware/Display.h"     // Needed for strip.Color and xyToIndex from DisplayUtils.cpp, if not implicitly included via DisplayUtils.h
#include "Services/Timekeeping.h" // Needed for rtc object
#include <Arduino.h>
#include <avr/pgmspace.h> // Still needed for FONT array in DisplayUtils.cpp.
#include <math.h>         // Needed for fmod and round functions

// Include our new utility headers
#include "Utils/DisplayUtils.h" // For drawCharacter, drawOne, drawDigit, drawBinaryHorizontal
#include "Utils/TimeUtils.h"    // For isLeapYear, daysInMonth, daysInYear, dayOfWeek, dayOfYear
#include "RTC.h"
#include "RTClib.h"

// --- Birthstone Colors (for Month Progress Bar) ---
// Indexed 0-11 for Jan-Dec. Stored in PROGMEM.
const uint32_t BIRTHSTONE_COLORS[] PROGMEM = {
    // Month 1 (Jan): Garnet (Dark Red)
    0x800000,
    // Month 2 (Feb): Amethyst (Purple)
    0x8A2BE2,
    // Month 3 (Mar): Aquamarine (Light Blue)
    0x7FFFD4,
    // Month 4 (Apr): Diamond (White)
    0xFFFFFF,
    // Month 5 (May): Emerald (Dark Green)
    0x006400,
    // Month 6 (Jun): Pearl/Alexandrite (Cream/Light Purple) - Using light purple
    0xDDA0DD,
    // Month 7 (Jul): Ruby (Bright Red)
    0xE00000,
    // Month 8 (Aug): Peridot (Lime Green)
    0x9ACD32,
    // Month 9 (Sep): Sapphire (Deep Blue)
    0x00008B,
    // Month 10 (Oct): Tourmaline/Opal (Pink/Rainbow) - Using Pink
    0xFFC0CB,
    // Month 11 (Nov): Topaz (Orange)
    0xFFA500,
    // Month 12 (Dec): Turquoise/Zircon (Cyan/Light Blue) - Using Cyan
    0x00FFFF};

// This function is called once every time the mode is switched to.
void initClock()
{
  // Nothing to initialize for this mode yet.
}

// This is the main display function for the Clock mode and all its submodes.
void displayClock()
{
  strip.clear();
  // --- CORRECTED RTC TIME RETRIEVAL AND DATETIME CONSTRUCTION ---
  RTCTime r4_currentTime; // Declare an RTCTime object (from R4's RTC.h)
  RTC.getTime(r4_currentTime); // Use the global RTC object to populate r4_currentTime

  // Construct an RTClib DateTime object from the R4's RTCTime object
    DateTime now(
      r4_currentTime.getYear(),
      Month2int(r4_currentTime.getMonth()), // Convert Month enum to int
      r4_currentTime.getDayOfMonth(),
      r4_currentTime.getHour(),
      r4_currentTime.getMinutes(),
      r4_currentTime.getSeconds());
  // --- END CORRECTED RTC TIME RETRIEVAL ---

  uint32_t customColor = strip.Color(state.customColor.r, state.customColor.g, state.customColor.b); // Use customColor for general fills

  // --- DEBUGGING: Print the time and input state to the Serial Monitor (once per second) ---
  static int lastPrintedSecond = -1;
  if (now.second() != lastPrintedSecond)
  {
    Serial.print("RTC Time: ");
    Serial.print(now.hour());
    Serial.print(":");
    if (now.minute() < 10)
      Serial.print('0');
    Serial.print(now.minute());
    Serial.print(":");
    if (now.second() < 10)
      Serial.print('0');
    Serial.println(now.second());
    lastPrintedSecond = now.second();

    Serial.print("Mode: ");
    Serial.print(state.currentModeIndex);
    Serial.print(" Submode[");
    Serial.print(state.currentModeIndex);
    Serial.print("]: ");
    Serial.print(state.modeSubmodeIndices[state.currentModeIndex]);
    Serial.print(" Brightness: ");
    Serial.println(state.brightness);
    Serial.print(" Theme: ");
    Serial.print(state.currentThemeIndex);
    Serial.print(" Custom Color: ");
    Serial.print(state.customColor.r);
    Serial.print(",");
    Serial.print(state.customColor.g);
    Serial.print(",");
    Serial.println(state.customColor.b);
  }

  switch (state.modeSubmodeIndices[state.currentModeIndex])
  {
  case 0:
  { // "Seconds Bar"
    int pixelsToLight = map(now.second(), 0, 59, 0, 128);
    for (int i = 0; i < pixelsToLight; i++)
    {
      strip.setPixelColor(i, customColor); // Fills all 128 pixels linearly, using customColor
    }
    break;
  }
  case 1:
  { // "Progress Bar Clock"
    // Get current date/time components using RTClib methods
    uint16_t currentYear = now.year();
    uint8_t currentMonth = now.month();
    uint8_t currentDay = now.day();
    uint8_t currentHour = now.hour();
    uint8_t currentMinute = now.minute();
    uint8_t currentSecond = now.second();

    // Define colors
    uint32_t inactiveBinaryColor = strip.Color(5, 5, 5); // 2% brightness white for inactive binary digits
    uint32_t whiteColor = strip.Color(255, 255, 255);    // Solid white for Hour/Minute progress bars

    // --- Calculations & Drawing for Progress Bars ---
    long secondsIntoDay = currentHour * 3600 + currentMinute * 60 + currentSecond;
    
    // Calculate total seconds elapsed so far this year
    int currentDayOfYear = dayOfYear(currentYear, currentMonth, currentDay);
    long secondsIntoYear = (long)(currentDayOfYear - 1) * 86400L + secondsIntoDay;
    long totalSecondsInYear = (long)daysInYear(currentYear) * 86400L;

    // Row 0: Year Progress (Custom Color)
    float yearProgress = (float)secondsIntoYear / totalSecondsInYear;
    for (int i = 0; i < round(yearProgress * 16.0); i++) {
      strip.setPixelColor(xyToIndex(i, 0), customColor);
    }

    // --- UPDATED SEASON LOGIC ---
    // Row 1: Season Progress (More Accurate)
    SeasonStartDates seasonStarts = getSeasonStartDates(currentYear);
    const int SPRING_START_DOY = seasonStarts.marchEquinox;
    const int SUMMER_START_DOY = seasonStarts.juneSolstice;
    const int AUTUMN_START_DOY = seasonStarts.septemberEquinox;
    const int WINTER_START_DOY = seasonStarts.decemberSolstice;

    uint32_t seasonColor;
    float seasonProgress;

    int springLength = SUMMER_START_DOY - SPRING_START_DOY;
    int summerLength = AUTUMN_START_DOY - SUMMER_START_DOY;
    int autumnLength = WINTER_START_DOY - AUTUMN_START_DOY;
    int winterLength = (daysInYear(currentYear) - WINTER_START_DOY) + SPRING_START_DOY;

    if (currentDayOfYear >= SPRING_START_DOY && currentDayOfYear < SUMMER_START_DOY)
    { // Spring
      seasonColor = strip.Color(0, 255, 0); // Green
      long secondsIntoSeason = secondsIntoYear - (long)(SPRING_START_DOY - 1) * 86400L;
      seasonProgress = (float)secondsIntoSeason / ((long)springLength * 86400.0);
    }
    else if (currentDayOfYear >= SUMMER_START_DOY && currentDayOfYear < AUTUMN_START_DOY)
    { // Summer
      seasonColor = strip.Color(255, 255, 0); // Yellow
      long secondsIntoSeason = secondsIntoYear - (long)(SUMMER_START_DOY - 1) * 86400L;
      seasonProgress = (float)secondsIntoSeason / ((long)summerLength * 86400.0);
    }
    else if (currentDayOfYear >= AUTUMN_START_DOY && currentDayOfYear < WINTER_START_DOY)
    { // Autumn
      seasonColor = strip.Color(255, 165, 0); // Orange
      long secondsIntoSeason = secondsIntoYear - (long)(AUTUMN_START_DOY - 1) * 86400L;
      seasonProgress = (float)secondsIntoSeason / ((long)autumnLength * 86400.0);
    }
    else
    { // Winter
      seasonColor = strip.Color(200, 200, 255); // Light Blue
      long secondsIntoSeason;
      if (currentDayOfYear >= WINTER_START_DOY) { // Winter part 1 (Dec-end of year)
        secondsIntoSeason = secondsIntoYear - (long)(WINTER_START_DOY - 1) * 86400L;
      } else { // Winter part 2 (Jan-Mar)
        secondsIntoSeason = secondsIntoYear + (totalSecondsInYear - (long)(WINTER_START_DOY - 1) * 86400L);
      }
      seasonProgress = (float)secondsIntoSeason / ((long)winterLength * 86400.0);
    }
    
    seasonProgress = fmod(seasonProgress, 1.0); // Ensure it wraps around 0-1
    for (int i = 0; i < round(seasonProgress * 16.0); i++)
    {
      strip.setPixelColor(xyToIndex(i, 1), seasonColor);
    }
    // --- END UPDATED SEASON LOGIC ---

    // Row 2: Month Progress (Birthstone Colors)
    long secondsIntoMonth = (long)(currentDay - 1) * 86400L + secondsIntoDay;
    long totalSecondsInMonth = (long)daysInMonth(currentYear, currentMonth) * 86400L;
    uint32_t monthColor = pgm_read_dword(&BIRTHSTONE_COLORS[currentMonth - 1]);
    float monthProgress = (float)secondsIntoMonth / totalSecondsInMonth;
    for (int i = 0; i < round(monthProgress * 16.0); i++) {
      strip.setPixelColor(xyToIndex(i, 2), monthColor);
    }

    // Row 3: Week Progress (Custom Color, assuming Monday=0 from dayOfWeek)
    long secondsIntoWeek = (long)dayOfWeek(currentYear, currentMonth, currentDay) * 86400L + secondsIntoDay;
    float weekProgress = (float)secondsIntoWeek / (7.0f * 86400.0f);
    for (int i = 0; i < round(weekProgress * 16.0); i++) {
      strip.setPixelColor(xyToIndex(i, 3), customColor);
    }

    // Row 4: Day Progress (Custom Color)
    // The formula itself was correct, but applying the consistent 'L' for long constants is good practice.
    float dayProgress = (float)secondsIntoDay / (24.0f * 3600.0f);
    for (int i = 0; i < round(dayProgress * 16.0); i++) {
      strip.setPixelColor(xyToIndex(i, 4), customColor);
    }
    
    // Row 5: Hour Progress (White)
    float hourProgress = (float)(currentMinute * 60L + currentSecond) / 3600.0f;
    for (int i = 0; i < round(hourProgress * 16.0); i++) {
      strip.setPixelColor(xyToIndex(i, 5), whiteColor);
    }

    // Row 6: Minute Progress (White)
    float minuteProgress = (float)currentSecond / 59.0f;
    for (int i = 0; i < round(minuteProgress * 16.0); i++) {
      strip.setPixelColor(xyToIndex(i, 6), whiteColor);
    }

    // Row 7: Binary Clock (1x1 horizontal pixels with inactive lit)
    int h_12_display = currentHour;
    if (h_12_display == 0)
    {
      h_12_display = 12;
    }
    else if (h_12_display > 12)
    {
      h_12_display -= 12;
    } // Convert to 12-hour format (1-12)

    // FIX: Pass the actual 12-hour value (1-12) to drawBinaryHorizontal
    // It can represent 12 (binary 1100). No need to modulo by 12 unless we want 0-11.
    drawBinaryHorizontal(h_12_display, 4, 0, 7, customColor, inactiveBinaryColor); // 4 bits, starts at X=0, Row 7
    int m = currentMinute;

    // Minutes (6 bits, 0-59)
    drawBinaryHorizontal(m, 6, 10, 7, customColor, inactiveBinaryColor); // 6 bits, starts at X=10, Row 7 (leaving 4 columns blank between H and M)

    break;
  }
  case 2:
  { // "Font Clock - 12 Hour"
    int h = now.hour();
    if (h == 0)
    {
      h = 12;
    }
    if (h > 12)
    {
      h -= 12;
    }

    int h_tens = h / 10;
    int h_units = h % 10;

    // Tens Digit of Hours (only 0 or 1 for 12hr format)
    if (h_tens == 1)
    {
      drawCharacter(1, 0, 1, customColor);
    }

    // Units Digit of Hours (Column 3,4,5)
    drawCharacter(h_units, 3, 1, customColor);

    // Colon (Column 7)
    strip.setPixelColor(xyToIndex(7, 2), customColor);
    strip.setPixelColor(xyToIndex(7, 5), customColor);

    // Minute Tens Digit (Column 9, 10, 11)
    int m = now.minute();
    int m_tens = m / 10;
    int m_units = m % 10;
    drawCharacter(m_tens, 9, 1, customColor);

    // Minute Units Digit (Column 13, 14, 15)
    drawCharacter(m_units, 13, 1, customColor);
    break;
  }
  case 3:
  { // "Binary Clock - 24 Hour"
    int h = now.hour();
    int m = now.minute();
    int s = now.second();

    int h_tens = h / 10;
    int h_units = h % 10;
    int m_tens = m / 10;
    int m_units = m % 10;
    int s_tens = s / 10;
    int s_units = s % 10;

    // Hours
    drawDigit(h_tens, 1, customColor);
    drawDigit(h_units, 3, customColor);

    // Minutes
    drawDigit(m_tens, 6, customColor);
    drawDigit(m_units, 8, customColor);

    // Seconds
    drawDigit(s_tens, 11, customColor);
    drawDigit(s_units, 13, customColor);

    break;
  }
  case 4:
  { // "Binary Clock - 12 Hour"
    int h = now.hour();
    if (h == 0)
    {
      h = 12;
    }
    if (h > 12)
    {
      h -= 12;
    }
    int m = now.minute();
    int s = now.second();

    int h_tens = h / 10;
    int h_units = h % 10;
    int m_tens = m / 10;
    int m_units = m % 10;
    int s_tens = s / 10;
    int s_units = s % 10;

    // Hours
    drawDigit(h_tens, 1, customColor);
    drawDigit(h_units, 3, customColor);

    // Minutes
    drawDigit(m_tens, 6, customColor);
    drawDigit(m_units, 8, customColor);

    // Seconds
    drawDigit(s_tens, 11, customColor);
    drawDigit(s_units, 13, customColor);
    break;
  }
  default:
    strip.setPixelColor(xyToIndex(0, 0), 0, 255, 0); // Default to green pixel if submode invalid
    break;
  }
}