#ifndef INPUT_H
#define INPUT_H

#include "Button.h" // Include the button class definition

// Declare the button objects as 'extern' so other files can access them.
// 'extern' tells the compiler "these variables exist, but are defined in another file".
extern Button modeButton;
extern Button submodeButton;

// Declarations for input handling functions.
void setupInputs();
void handleInputs();

#endif // INPUT_H
