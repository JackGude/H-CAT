#ifndef THEMES_H
#define THEMES_H

// Defines the structure for a color theme and declares the global
// array of available themes.

struct Theme {
  const char* name;
  // Later, we will add color data here, e.g.:
  // uint32_t primaryColor;
  // uint32_t secondaryColor;
};

// Declare the global themes array and its size so other files can use them.
extern const Theme themes[];
extern const int NUM_THEMES;

#endif // THEMES_H
