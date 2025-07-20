#include "TimeUtils.h"

// Checks if a given year is a leap year.
bool isLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Returns the number of days in a given month of a given year.
int daysInMonth(int year, int month) {
  if (month < 1 || month > 12) return 0;
  if (month == 2) return isLeapYear(year) ? 29 : 28;
  if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
  return 31;
}

// Returns the total number of days in a given year (365 or 366).
int daysInYear(int year) {
  return isLeapYear(year) ? 366 : 365;
}

// Calculates day of the week (0=Sunday, 1=Monday, ..., 6=Saturday) using Zeller's congruence.
int dayOfWeek(uint16_t year, uint8_t month, uint8_t day) {
  if (month < 3) {
    month += 12;
    year--;
  }
  int k = year % 100;
  int j = year / 100;
  int h = (day + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
  return (h+5) % 7; // Adjust to 0=Monday, 6=Sunday
}

// Calculates day of the year (1-365 or 1-366).
int dayOfYear(uint16_t year, uint8_t month, uint8_t day) {
    int daysInMonths[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) {
        daysInMonths[2] = 29; // February in a leap year
    }
    int day_of_year = 0;
    for (int i = 1; i < month; i++) {
        day_of_year += daysInMonths[i];
    }
    day_of_year += day;
    return day_of_year;
}