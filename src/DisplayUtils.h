#ifndef DISPLAY_UTILS_H
#define DISPLAY_UTILS_H

#include <Arduino.h>
#include <Adafruit_DotStar.h> // Needed for uint32_t color type and strip object access

// Forward declaration of the strip object from Display.h,
// so these utilities know it exists without a circular include.
extern Adafruit_DotStar strip;

// Converts (x,y) coordinates to a linear pixel index.
int xyToIndex(int x, int y); // This function is already in Display.h, we will call the one defined there.

// Helper function to draw a character from the custom font.
void drawCharacter(int character, int offsetX, int offsetY, uint32_t color);

// Helper function to draw just the number '1' in a single column.
void drawOne(int offsetX, int offsetY, uint32_t color);

// Helper function for the BCD Clock, draws a 2x2 bit.
void drawDigit(int digit, int columnOffset, uint32_t color);

// Helper function to draw 1x1 binary digits horizontally.
void drawBinaryHorizontal(int value, int numBits, int startX, int startY, uint32_t color, uint32_t inactiveColor);

#endif // DISPLAY_UTILS_H