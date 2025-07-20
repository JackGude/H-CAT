#ifndef MODES_H
#define MODES_H

// The Mode struct now includes a pointer to an initialization function.
struct Mode {
  const char* name;
  int numSubmodes;
  void (*initFunction)();   // Runs once when the mode is selected
  void (*displayFunction)(); // Runs on every frame
};

extern const Mode modes[];
extern const int NUM_MODES;

void runCurrentMode();

#endif // MODES_H
