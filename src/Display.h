#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_DotStar.h>

// --- Global Declarations ---
// We declare the 'strip' object here with 'extern' so that any file
// that includes this header knows that 'strip' exists somewhere else.
extern Adafruit_DotStar strip;

// --- Function Prototypes ---
// This tells the rest of the program that these functions exist.
void setupDisplay();
int xyToIndex(int x, int y);

#endif // DISPLAY_H
