#include "DisplayUtils.h"
#include "Hardware/Display.h" // Needed to access the global 'strip' object and xyToIndex definition

// --- Custom Font Data (Stored in Flash Memory) ---
const byte FONT[10][3] PROGMEM = {
  {0x3F, 0x21, 0x3F}, // 0
  {0x00, 0x3F, 0x00}, // 1
  {0x13, 0x25, 0x19}, // 2
  {0x21, 0x25, 0x3F}, // 3
  {0x38, 0x08, 0x3F}, // 4
  {0x39, 0x29, 0x26}, // 5
  {0x3F, 0x25, 0x27}, // 6
  {0x20, 0x20, 0x3F}, // 7
  {0x3F, 0x29, 0x3F}, // 8
  {0x38, 0x28, 0x3F}  // 9
};

// --- Helper function to draw a character from the font ---
void drawCharacter(int character, int offsetX, int offsetY, uint32_t color) {
  for (int col = 0; col < 3; col++) { // Font characters are 3 columns wide
    byte colData = pgm_read_byte(&FONT[character][col]);
    for (int row = 0; row < 6; row++) {
      if ((colData >> row) & 1) {
        strip.setPixelColor(xyToIndex(offsetX + col, offsetY + (5 - row)), color);
      }
    }
  }
}

// --- Helper function to draw just the number '1' in a single column ---
void drawOne(int offsetX, int offsetY, uint32_t color) {
    byte colData = pgm_read_byte(&FONT[1][2]); // Get the data for the vertical bar of '1'
    for (int row = 0; row < 6; row++) {
        if ((colData >> row) & 1) {
            strip.setPixelColor(xyToIndex(offsetX, offsetY + (5 - row)), color);
        }
    }
}

// --- Helper function for the BCD Clock (2x2 bits, vertical) ---
void drawDigit(int digit, int columnOffset, uint32_t color) {
  for (int i = 0; i < 4; i++) { // Iterate through 4 bits
    if ((digit >> i) & 1) {
      int basePixelY = (3 - i) * 2; // Maps bit 0 to Y=6, bit 1 to Y=4, bit 2 to Y=2, bit 3 to Y=0

      // Draw the 2x2 block
      strip.setPixelColor(xyToIndex(columnOffset, basePixelY), color);
      strip.setPixelColor(xyToIndex(columnOffset + 1, basePixelY), color);
      strip.setPixelColor(xyToIndex(columnOffset, basePixelY + 1), color);
      strip.setPixelColor(xyToIndex(columnOffset + 1, basePixelY + 1), color);
    }
  }
}

// --- Helper function: Draw 1x1 binary digits horizontally (with inactive bits lit) ---
void drawBinaryHorizontal(int value, int numBits, int startX, int startY, uint32_t activeColor, uint32_t inactiveColor) {
  for (int i = 0; i < numBits; i++) {
    int currentBit = (value >> (numBits - 1 - i)) & 1; // Read from MSB (left) to LSB (right)
    if (currentBit == 1) {
      strip.setPixelColor(xyToIndex(startX + i, startY), activeColor);
    } else {
      strip.setPixelColor(xyToIndex(startX + i, startY), inactiveColor);
    }
  }
}