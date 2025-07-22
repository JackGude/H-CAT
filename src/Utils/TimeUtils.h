#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <Arduino.h> // For uint16_t, uint8_t types

// A struct to hold the day-of-year for each season's start
struct SeasonStartDates {
  int marchEquinox;
  int juneSolstice;
  int septemberEquinox;
  int decemberSolstice;
};

// Calculates the approximate day of the year for the four major astronomical events.
SeasonStartDates getSeasonStartDates(int year);

// Checks if a given year is a leap year.
bool isLeapYear(int year);

// Returns the number of days in a given month of a given year.
int daysInMonth(int year, int month);

// Returns the total number of days in a given year (365 or 366).
int daysInYear(int year);

// Calculates day of the week (0=Sunday, 1=Monday, ..., 6=Saturday) using Zeller's congruence.
int dayOfWeek(uint16_t year, uint8_t month, uint8_t day);

// Calculates day of the year (1-365 or 1-366).
int dayOfYear(uint16_t year, uint8_t month, uint8_t day);

#endif // TIME_UTILS_H