#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

// Converts a Hue value to an RGB color.
void hsvToRgb(float h, float s, float v, uint8_t& r, uint8_t& g, uint8_t& b);

#endif // UTILS_H
