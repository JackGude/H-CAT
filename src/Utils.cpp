#include "Utils.h"
#include <math.h> // For fmod

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
