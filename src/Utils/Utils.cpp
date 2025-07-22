#include "Utils.h"
#include <math.h> // For fmod

// --- Custom Pseudo-Random Number Generator (PRNG) ---
// Define and initialize the global seed variable
unsigned long s_custom_random_seed = 1;

void myRandomSeed(unsigned long seed) {
    if (seed == 0) seed = 42; // Seed 0 can sometimes cause issues with LCGs
    s_custom_random_seed = seed;
}

long myRandom(long howBig) {
    s_custom_random_seed = s_custom_random_seed * 1103515245UL + 12345UL; // LCG formula (parameters for good distribution)
    // Use higher bits (divide by 65536) for better randomness, then modulo
    return (unsigned long)(s_custom_random_seed / 65536UL) % howBig;
}

long myRandom(long howSmall, long howBig) {
    if (howSmall >= howBig) return howSmall; // Handle invalid range
    long diff = howBig - howSmall;
    return myRandom(diff) + howSmall; // Scale the 0-diff result to the desired range
}
// --- END Custom PRNG ---

// Original hsvToRgb function (unchanged)
void hsvToRgb(float h, float s, float v, uint8_t& r, uint8_t& g, uint8_t& b) {
    float C = v * s;
    float X = C * (1 - abs(fmod(h / 60.0, 2) - 1));
    float m = v - C;
    float rs, gs, bs;

    if (h >= 0 && h < 60) {
        rs = C; gs = X; bs = 0;
    } else if (h >= 60 && h < 120) {
        rs = X; gs = C; bs = 0;
    } else if (h >= 120 && h < 180) {
        rs = 0; gs = C; bs = X;
    } else if (h >= 180 && h < 240) {
        rs = 0; gs = X; bs = C;
    } else if (h >= 240 && h < 300) {
        rs = X; gs = 0; bs = C;
    } else {
        rs = C; gs = 0; bs = X;
    }

    r = (rs + m) * 255;
    g = (gs + m) * 255;
    b = (bs + m) * 255;
}