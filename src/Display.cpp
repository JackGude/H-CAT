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
  strip.begin();
  strip.setBrightness(10); // A moderate, safe brightness
  strip.show(); // Initialize all pixels to 'off'
  Serial.println("  - Display Initialized.");
}

// This is the correct mapping for your 16x8 non-serpentine, column-major panel.
// (0,0) is the top-left pixel.
int xyToIndex(int x, int y) {
  if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) {
    return -1; // Return an invalid index if out of bounds
  }
  return x * GRID_HEIGHT + y;
}