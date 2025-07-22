#include "Modes/DLAMode.h"
#include "Hardware/Display.h"
#include "Config/State.h"
#include <Arduino.h>
#include "Utils/Utils.h"

// --- Configuration ---
const int GRID_WIDTH = 16;
const int GRID_HEIGHT = 8;
const int MAX_PARTICLES = GRID_WIDTH * GRID_HEIGHT;
const long ART_UPDATE_INTERVAL = 20;
const long PAUSE_DURATION = 2000;

// --- Data Structures & State Variables ---
enum DLABias
{
  NONE,
  VERTICAL,
  HORIZONTAL
}; // **NEW**: Enum for bias direction

struct Particle
{
  bool active = false;
  uint32_t color = 0;
};

struct Walker
{
  int x;
  int y;
  bool active = false;
};

Particle crystal[MAX_PARTICLES];
Walker walker;
int particleCount;
int availableSpawns;
DLABias currentBias; // **NEW**: Global variable for the current bias
unsigned long lastArtUpdate = 0;
float hue_counter = 0;
bool simulationPaused = false;
unsigned long pauseStartTime = 0;

// --- Forward Declarations ---
void spawnWalker();
void updateDLA();
bool handleWalkerMove();
void endSimulation();
uint32_t getColor();
uint32_t getColor_Classic();
uint32_t getColor_Competitive();
uint32_t getColor_Rainbow();

// --- Spawning and Initialization ---

void spawnWalker()
{
  int attempts = 0;
  const int maxAttempts = 500;
  do
  {
    int edge;
    // **FIX**: Use the enum to determine spawn edge
    if (currentBias == VERTICAL)
      edge = 0; // Top edge only
    else if (currentBias == HORIZONTAL)
      edge = 2; // Left edge only
    else
      edge = myRandom(4); // Any edge

    switch (edge)
    {
    case 0:
      walker.x = myRandom(GRID_WIDTH);
      walker.y = 0;
      break;
    case 1:
      walker.x = myRandom(GRID_WIDTH);
      walker.y = GRID_HEIGHT - 1;
      break;
    case 2:
      walker.x = 0;
      walker.y = myRandom(GRID_HEIGHT);
      break;
    case 3:
      walker.x = GRID_WIDTH - 1;
      walker.y = myRandom(GRID_HEIGHT);
      break;
    }
    attempts++;
    if (attempts > maxAttempts)
    {
      endSimulation();
      return;
    }
  } while (crystal[xyToIndex(walker.x, walker.y)].active);
  walker.active = true;
}

void initDLASim()
{
  myRandomSeed(millis());
  memset(crystal, 0, sizeof(crystal));
  particleCount = 0;
  lastArtUpdate = millis();
  walker.active = false;
  simulationPaused = false;

  int submode = state.modeSubmodeIndices[state.currentModeIndex];

  switch (submode)
  {
  case 0:
  case 1:
  case 2:
    currentBias = NONE;
    availableSpawns = (GRID_WIDTH * 2) + (GRID_HEIGHT * 2) - 4;
    break;
  case 3: // Vertical Bias (Gravity)
    currentBias = VERTICAL;
    availableSpawns = GRID_WIDTH;
    break;
  case 4: // Horizontal Bias
    currentBias = HORIZONTAL;
    availableSpawns = GRID_HEIGHT;
    break;
  }

  // --- Seeding Logic ---
  switch (submode)
  {
  case 0:
  case 2:
    crystal[xyToIndex(GRID_WIDTH / 2, GRID_HEIGHT / 2)].active = true;
    crystal[xyToIndex(GRID_WIDTH / 2, GRID_HEIGHT / 2)].color = (submode == 0) ? getColor_Classic() : getColor_Rainbow();
    particleCount = 1;
    hue_counter = 0;
    break;
  case 1: // Competitive
  {
    uint32_t colors[3];
    int dominantChannel[] = {0, 1, 2};
    for (int i = 0; i < 3; i++)
    {
      int j = myRandom(i, 3);
      int temp = dominantChannel[i];
      dominantChannel[i] = dominantChannel[j];
      dominantChannel[j] = temp;
    }
    for (int i = 0; i < 3; i++)
    {
      uint8_t r = 0, g = 0, b = 0, lim = 150;
      if (dominantChannel[i] == 0)
      {
        r = 255;
        g = myRandom(lim);
        b = myRandom(lim);
      }
      else if (dominantChannel[i] == 1)
      {
        g = 255;
        r = myRandom(lim);
        b = myRandom(lim);
      }
      else
      {
        b = 255;
        r = myRandom(lim);
        g = myRandom(lim);
      }
      colors[i] = strip.Color(r, g, b);
    }
    for (int i = 0; i < 3; i++)
    {
      int cx, cy;
      do
      {
        cx = myRandom(6, 10);
        cy = myRandom(2, 6);
      } while (crystal[xyToIndex(cx, cy)].active);
      crystal[xyToIndex(cx, cy)].active = true;
      crystal[xyToIndex(cx, cy)].color = colors[i];
      particleCount++;
    }
  }
  break;
  case 3: // Vertical Bias
    for (int i = 0; i < GRID_WIDTH; i++)
    {
      if (myRandom(100) < 15)
      {
        crystal[xyToIndex(i, GRID_HEIGHT - 1)].active = true;
        crystal[xyToIndex(i, GRID_HEIGHT - 1)].color = getColor_Classic();
        particleCount++;
      }
    }
    if (particleCount == 0)
    {
      int seed_pos = myRandom(GRID_WIDTH);
      crystal[xyToIndex(seed_pos, GRID_HEIGHT - 1)].active = true;
      crystal[xyToIndex(seed_pos, GRID_HEIGHT - 1)].color = getColor_Classic();
      particleCount = 1;
    }
    break;
  case 4: // Horizontal Bias Seeding
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
      if (myRandom(100) < 15)
      {
        crystal[xyToIndex(GRID_WIDTH - 1, i)].active = true;
        crystal[xyToIndex(GRID_WIDTH - 1, i)].color = getColor_Classic();
        particleCount++;
      }
    }
    if (particleCount == 0)
    {
      int seed_pos = myRandom(GRID_HEIGHT);
      crystal[xyToIndex(GRID_WIDTH - 1, seed_pos)].active = true;
      crystal[xyToIndex(GRID_WIDTH - 1, seed_pos)].color = getColor_Classic();
      particleCount = 1;
    }
    break;
  }
  spawnWalker();
}

// --- Main Display and Update Loop ---

void displayDLASim()
{
  static int lastSubmode = -1;
  int currentSubmode = state.modeSubmodeIndices[state.currentModeIndex];

  if (currentSubmode != lastSubmode)
  {
    initDLASim();
    lastSubmode = currentSubmode;
  }

  if (simulationPaused)
  {
    if (millis() - pauseStartTime > PAUSE_DURATION)
    {
      initDLASim();
    }
  }
  else if (millis() - lastArtUpdate > ART_UPDATE_INTERVAL)
  {
    lastArtUpdate = millis();

    if (availableSpawns <= 0)
    {
      endSimulation();
    }
    else
    {
      updateDLA();
    }
  }

  // --- Drawing Logic ---
  strip.clear();
  for (int i = 0; i < MAX_PARTICLES; i++)
  {
    if (crystal[i].active)
      strip.setPixelColor(i, crystal[i].color);
  }
  if (walker.active && !simulationPaused)
  {
    strip.setPixelColor(xyToIndex(walker.x, walker.y), 255, 255, 255);
  }
  strip.show();
}

// --- Helper & Logic Functions ---

void endSimulation()
{
  simulationPaused = true;
  pauseStartTime = millis();
  hue_counter = 0;
}

bool handleWalkerMove()
{
  int newX = walker.x, newY = walker.y;

  if (currentBias != NONE)
  {
    int dir = myRandom(8);
    if (currentBias == VERTICAL)
    { // Downward bias
      if (dir < 1)
        newX++;
      else if (dir < 2)
        newX--;
      else if (dir < 3)
        newY--;
      else
        newY++; // 5/8 chance down
    }
    else
    { // HORIZONTAL
      if (dir < 1)
        newY++;
      else if (dir < 2)
        newY--;
      else if (dir < 3)
        newX--;
      else
        newX++; // 5/8 chance left
    }
  }
  else
  { // No bias
    int dir = myRandom(4);
    if (dir == 0)
      newX++;
    else if (dir == 1)
      newX--;
    else if (dir == 2)
      newY++;
    else
      newY--;
  }

  if (newX < 0 || newX >= GRID_WIDTH || newY < 0 || newY >= GRID_HEIGHT)
  {
    return false; // Walker went off-grid
  }
  walker.x = newX;
  walker.y = newY;
  return true; // Walker moved successfully
}

uint32_t getColor()
{
  int submode = state.modeSubmodeIndices[state.currentModeIndex];
  if (submode == 2)
  { // Rainbow
    uint8_t r, g, b;
    hsvToRgb(hue_counter, 1.0, 1.0, r, g, b);
    hue_counter = fmod(hue_counter + 4.0, 360.0);
    return strip.Color(r, g, b);
  }
  if (submode == 1)
  { // Competitive
    for (int dx = -1; dx <= 1; dx++)
    {
      for (int dy = -1; dy <= 1; dy++)
      {
        if (dx == 0 && dy == 0)
          continue;
        int nx = walker.x + dx, ny = walker.y + dy;
        if (nx >= 0 && nx < GRID_WIDTH && ny >= 0 && ny < GRID_HEIGHT)
        {
          int neighbor_index = xyToIndex(nx, ny);
          if (crystal[neighbor_index].active)
            return crystal[neighbor_index].color;
        }
      }
    }
  }
  return getColor_Classic(); // Default for Classic and Biased modes
}

void updateDLA()
{
  if (!walker.active)
  {
    spawnWalker();
    return;
  }

  bool isAdjacent = false;
  for (int dx = -1; dx <= 1; dx++)
  {
    for (int dy = -1; dy <= 1; dy++)
    {
      if (dx == 0 && dy == 0)
        continue;
      int nx = walker.x + dx, ny = walker.y + dy;
      if (nx >= 0 && nx < GRID_WIDTH && ny >= 0 && ny < GRID_HEIGHT && crystal[xyToIndex(nx, ny)].active)
      {
        isAdjacent = true;
        break;
      }
    }
    if (isAdjacent)
      break;
  }

  if (isAdjacent)
  {
    int stick_index = xyToIndex(walker.x, walker.y);
    crystal[stick_index].active = true;
    crystal[stick_index].color = getColor();
    particleCount++;

    if (currentBias == NONE)
    {
      if (walker.y == 0 || walker.y == GRID_HEIGHT - 1 || walker.x == 0 || walker.x == GRID_WIDTH - 1)
        availableSpawns--;
    }
    else if (currentBias == VERTICAL && walker.y == 0)
    {
      availableSpawns--;
    }
    else if (currentBias == HORIZONTAL && walker.x == 0)
    {
      availableSpawns--;
    }
    spawnWalker();
  }
  else
  {
    if (!handleWalkerMove())
    {                // If walker moves off-grid...
      spawnWalker(); // ...spawn a new one.
    }
  }
}

uint32_t getColor_Classic()
{
  return strip.Color(state.customColor.r, state.customColor.g, state.customColor.b);
}

uint32_t getColor_Competitive()
{
  for (int dx = -1; dx <= 1; dx++)
  {
    for (int dy = -1; dy <= 1; dy++)
    {
      if (dx == 0 && dy == 0)
        continue;
      int nx = walker.x + dx, ny = walker.y + dy;
      if (nx >= 0 && nx < GRID_WIDTH && ny >= 0 && ny < GRID_HEIGHT)
      {
        int neighbor_index = xyToIndex(nx, ny);
        if (crystal[neighbor_index].active)
        {
          return crystal[neighbor_index].color;
        }
      }
    }
  }
  return 0; // Should not happen
}

uint32_t getColor_Rainbow()
{
  uint8_t r, g, b;
  hsvToRgb(hue_counter, 1.0, 1.0, r, g, b);
  hue_counter = fmod(hue_counter + 4.0, 360.0);
  return strip.Color(r, g, b);
}
