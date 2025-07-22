#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

// Converts a Hue value to an RGB color.
void hsvToRgb(float h, float s, float v, uint8_t& r, uint8_t& g, uint8_t& b);

// --- Custom Pseudo-Random Number Generator (PRNG) ---
// Declared as extern because its definition (initialization) is in Utils.cpp
extern unsigned long s_custom_random_seed; // Declare global seed variable
void myRandomSeed(unsigned long seed);      // Declare custom seeding function
long myRandom(long howBig);                 // Declare custom random function (0 to howBig-1)
long myRandom(long howSmall, long howBig); // Declare custom random function (howSmall to howBig-1)
// --- END Custom PRNG ---

#endif // UTILS_H