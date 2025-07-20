#include "Display.h"
#include <SPI.h>
#include <Arduino.h> // Include Arduino.h for Serial

// --- LED PANEL CONFIGURATION ---
const int NUM_PIXELS = 128;
const int GRID_WIDTH = 16;
const int GRID_HEIGHT = 8;
const int DATA_PIN = 11;
const int CLOCK_PIN = 13;

// --- Global Object Definition ---
// This is where the 'strip' object is actually created.
Adafruit_DotStar strip = Adafruit_DotStar(NUM_PIXELS, DATA_PIN, CLOCK_PIN, DOTSTAR_BGR);

// --- Function Definitions ---

void setupDisplay() {
  Serial.println("DEBUG: Entering setupDisplay()...");
  Serial.print("DEBUG: Calling strip.begin()... ");
  strip.begin();
  Serial.println("DEBUG: strip.begin() called.");

  Serial.print("DEBUG: Setting brightness to 10... ");
  strip.setBrightness(10); // A moderate, safe brightness
  Serial.println("DEBUG: Brightness set.");

  // Temporarily comment out strip.show() to isolate.
  // Serial.print("DEBUG: Calling strip.show()... ");
  // strip.show(); // Initialize all pixels to 'off'
  // Serial.println("DEBUG: strip.show() called.");

  Serial.println("DEBUG: Exiting setupDisplay().");
  Serial.println("  - Display Initialized."); // Original message
}

// This is the correct mapping for your 16x8 non-serpentine, column-major panel.
// (0,0) is the top-left pixel.
int xyToIndex(int x, int y) {
  if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) {
    return -1; // Return an invalid index if out of bounds
  }
  return x * GRID_HEIGHT + y;
}