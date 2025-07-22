#include "CAMode.h"
#include "Display.h"
#include "State.h"
#include <Arduino.h>
#include "Utils.h"

// --- Configuration ---
const int SIM_WIDTH = 16;
const int SIM_HEIGHT = 8;
const int INJECTION_CHANCE = 15;
const int MUTATION_CHANCE = 2;
const int INITIAL_DENSITY_PERCENT = 10;

// --- Data Structures ---
struct Color
{
  uint8_t r, g, b;
};
union GridData
{
  struct
  {
    byte gridR[SIM_WIDTH][SIM_HEIGHT];
    byte gridG[SIM_WIDTH][SIM_HEIGHT];
    byte gridB[SIM_WIDTH][SIM_HEIGHT];
  } standard;
  struct
  {
    byte lifeGrid[SIM_WIDTH][SIM_HEIGHT];
    Color colorGrid[SIM_WIDTH][SIM_HEIGHT];
  } colorLife;
};

GridData currentGrid;
GridData nextGrid;
unsigned long lastUpdateTime = 0;

// --- Custom Pseudo-Random Number Generator (PRNG) ---
// (This section is now in Utils.h/Utils.cpp, so it should be removed from here if it was present)
/*
static unsigned long s_custom_random_seed = 1;
void myRandomSeed(unsigned long seed) { ... }
long myRandom(long howBig) { ... }
long myRandom(long howSmall, long howBig) { ... }
*/
// --- END Custom PRNG (should not be in this file) ---

// --- Initialization Functions ---
void seedStandardGrids()
{
  Serial.println("DEBUG CA: Seeding Standard Grids...");
  for (int x = 0; x < SIM_WIDTH; x++)
  {
    for (int y = 0; y < SIM_HEIGHT; y++)
    {
      currentGrid.standard.gridR[x][y] = myRandom(2);
      currentGrid.standard.gridG[x][y] = myRandom(2);
      currentGrid.standard.gridB[x][y] = myRandom(2);
      // DEBUG: Print some blue initial values
      // if (y == 0 && (x == 0 || x == 1 || x == 2)) {
      //   Serial.print("Initial Blue["); Serial.print(x); Serial.print("][0]: "); Serial.println(currentGrid.standard.gridB[x][y]);
      // }
    }
  }
}

void seedColorLifeGrid()
{
  const int INITIAL_DENSITY_PERCENT = 10;
  for (int x = 0; x < SIM_WIDTH; x++)
  {
    for (int y = 0; y < SIM_HEIGHT; y++)
    {
      currentGrid.colorLife.lifeGrid[x][y] = (myRandom(100) < INITIAL_DENSITY_PERCENT) ? 1 : 0;
      if (currentGrid.colorLife.lifeGrid[x][y] == 1)
      {
        int colorChoice = myRandom(3);
        if (colorChoice == 0)
        {
          currentGrid.colorLife.colorGrid[x][y] = {255, 0, 0};
        }
        else if (colorChoice == 1)
        {
          currentGrid.colorLife.colorGrid[x][y] = {0, 255, 0};
        }
        else
        {
          currentGrid.colorLife.colorGrid[x][y] = {0, 0, 255};
        }
      }
      else
      {
        currentGrid.colorLife.colorGrid[x][y] = {0, 0, 0};
      }
    }
  }
}

void initCellularAutomata()
{
  myRandomSeed(millis());

  int submode = state.modeSubmodeIndices[state.currentModeIndex];
  if (submode <= 2)
  {
    seedStandardGrids();
  }
  else
  {
    seedColorLifeGrid();
  }
  lastUpdateTime = millis();
}

// --- Simulation Logic ---
void calculateNextGenStandard(byte grid[SIM_WIDTH][SIM_HEIGHT], byte nextGrid[SIM_WIDTH][SIM_HEIGHT])
{
  // Array of the 8 neighbor coordinate offsets
  const int8_t neighbors_offset[8][2] = {
      {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

  for (int x = 0; x < SIM_WIDTH; x++)
  {
    for (int y = 0; y < SIM_HEIGHT; y++)
    {
      int neighbors = 0;
      for (int i = 0; i < 8; i++)
      {
        int nx = (x + neighbors_offset[i][0] + SIM_WIDTH) % SIM_WIDTH;
        int ny = (y + neighbors_offset[i][1] + SIM_HEIGHT) % SIM_HEIGHT;
        neighbors += grid[nx][ny];
      }

      // Game of Life rules (this logic remains the same)
      if (grid[x][y] == 1 && (neighbors < 2 || neighbors > 3))
      {
        nextGrid[x][y] = 0;
      }
      else if (grid[x][y] == 0 && neighbors == 3)
      {
        nextGrid[x][y] = 1;
      }
      else
      {
        nextGrid[x][y] = grid[x][y];
      }
      if (nextGrid[x][y] == 0 && myRandom(100) < MUTATION_CHANCE)
      {
        nextGrid[x][y] = 1;
      }
    }
  }
}

void calculateNextGenColor()
{
  // --- INJECTION LOGIC (no changes here) ---
  if (myRandom(100) < INJECTION_CHANCE)
  {
    int x_inject = myRandom(SIM_WIDTH);
    int y_inject = myRandom(SIM_HEIGHT);
    Color c;
    int colorChoice = myRandom(3);
    if (colorChoice == 0)
    {
      c = {255, 0, 0};
    }
    else if (colorChoice == 1)
    {
      c = {0, 255, 0};
    }
    else
    {
      c = {0, 0, 255};
    }

    int patternChoice = myRandom(3);

    int clear_width = 5;
    int clear_height = 4;
    for (int cx = 0; cx < clear_width; cx++)
    {
      for (int cy = 0; cy < clear_height; cy++)
      {
        int targetX = (x_inject + cx + SIM_WIDTH) % SIM_WIDTH;
        int targetY = (y_inject + cy + SIM_HEIGHT) % SIM_HEIGHT;
        currentGrid.colorLife.lifeGrid[targetX][targetY] = 0;
        currentGrid.colorLife.colorGrid[targetX][targetY] = {0, 0, 0};
      }
    }

    switch (patternChoice)
    {
    case 0: // Glider
      currentGrid.colorLife.lifeGrid[(x_inject + 1) % SIM_WIDTH][y_inject] = 1;
      currentGrid.colorLife.colorGrid[(x_inject + 1) % SIM_WIDTH][y_inject] = c;
      currentGrid.colorLife.lifeGrid[(x_inject + 2) % SIM_WIDTH][(y_inject + 1) % SIM_HEIGHT] = 1;
      currentGrid.colorLife.colorGrid[(x_inject + 2) % SIM_WIDTH][(y_inject + 1) % SIM_HEIGHT] = c;
      currentGrid.colorLife.lifeGrid[x_inject][(y_inject + 2) % SIM_HEIGHT] = 1;
      currentGrid.colorLife.colorGrid[x_inject][(y_inject + 2) % SIM_HEIGHT] = c;
      currentGrid.colorLife.lifeGrid[(x_inject + 1) % SIM_WIDTH][(y_inject + 2) % SIM_HEIGHT] = 1;
      currentGrid.colorLife.colorGrid[(x_inject + 1) % SIM_WIDTH][(y_inject + 2) % SIM_HEIGHT] = c;
      currentGrid.colorLife.lifeGrid[(x_inject + 2) % SIM_WIDTH][(y_inject + 2) % SIM_HEIGHT] = 1;
      currentGrid.colorLife.colorGrid[(x_inject + 2) % SIM_WIDTH][(y_inject + 2) % SIM_HEIGHT] = c;
      break;
    case 1: // Blinker
      currentGrid.colorLife.lifeGrid[x_inject][y_inject] = 1;
      currentGrid.colorLife.colorGrid[x_inject][y_inject] = c;
      currentGrid.colorLife.lifeGrid[(x_inject + 1) % SIM_WIDTH][y_inject] = 1;
      currentGrid.colorLife.colorGrid[(x_inject + 1) % SIM_WIDTH][y_inject] = c;
      currentGrid.colorLife.lifeGrid[(x_inject + 2) % SIM_WIDTH][y_inject] = 1;
      currentGrid.colorLife.colorGrid[(x_inject + 2) % SIM_WIDTH][y_inject] = c;
      break;
    case 2: // Toad
      currentGrid.colorLife.lifeGrid[(x_inject + 1) % SIM_WIDTH][y_inject] = 1;
      currentGrid.colorLife.colorGrid[(x_inject + 1) % SIM_WIDTH][y_inject] = c;
      currentGrid.colorLife.lifeGrid[(x_inject + 2) % SIM_WIDTH][y_inject] = 1;
      currentGrid.colorLife.colorGrid[(x_inject + 2) % SIM_WIDTH][y_inject] = c;
      currentGrid.colorLife.lifeGrid[(x_inject + 3) % SIM_WIDTH][y_inject] = 1;
      currentGrid.colorLife.colorGrid[(x_inject + 3) % SIM_WIDTH][y_inject] = c;
      currentGrid.colorLife.lifeGrid[x_inject][(y_inject + 1) % SIM_HEIGHT] = 1;
      currentGrid.colorLife.colorGrid[x_inject][(y_inject + 1) % SIM_HEIGHT] = c;
      currentGrid.colorLife.lifeGrid[(x_inject + 1) % SIM_WIDTH][(y_inject + 1) % SIM_HEIGHT] = 1;
      currentGrid.colorLife.colorGrid[(x_inject + 1) % SIM_WIDTH][(y_inject + 1) % SIM_HEIGHT] = c;
      currentGrid.colorLife.lifeGrid[(x_inject + 2) % SIM_WIDTH][(y_inject + 1) % SIM_HEIGHT] = 1;
      currentGrid.colorLife.colorGrid[(x_inject + 2) % SIM_WIDTH][(y_inject + 1) % SIM_HEIGHT] = c;
      break;
    }
  }

  memset(&nextGrid.colorLife, 0, sizeof(nextGrid.colorLife));

  // --- OPTIMIZED CALCULATION LOGIC ---
  const int8_t neighbors_offset[8][2] = {
      {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

  for (int x = 0; x < SIM_WIDTH; x++)
  {
    for (int y = 0; y < SIM_HEIGHT; y++)
    {
      int neighbors = 0;
      int sumR = 0, sumG = 0, sumB = 0;

      for (int i = 0; i < 8; i++)
      {
        int nx = (x + neighbors_offset[i][0] + SIM_WIDTH) % SIM_WIDTH;
        int ny = (y + neighbors_offset[i][1] + SIM_HEIGHT) % SIM_HEIGHT;
        if (currentGrid.colorLife.lifeGrid[nx][ny] == 1)
        {
          neighbors++;
          sumR += currentGrid.colorLife.colorGrid[nx][ny].r;
          sumG += currentGrid.colorLife.colorGrid[nx][ny].g;
          sumB += currentGrid.colorLife.colorGrid[nx][ny].b;
        }
      }

      if (currentGrid.colorLife.lifeGrid[x][y] == 1 && (neighbors < 2 || neighbors > 3))
      {
        nextGrid.colorLife.lifeGrid[x][y] = 0;
        // colorGrid is already {0,0,0} from memset
      }
      else if (currentGrid.colorLife.lifeGrid[x][y] == 0 && neighbors == 3)
      {
        nextGrid.colorLife.lifeGrid[x][y] = 1;

        uint8_t avgR = sumR / 3;
        uint8_t avgG = sumG / 3;
        uint8_t avgB = sumB / 3;

        if (avgR > 0 && avgR >= avgG && avgR >= avgB)
        {
          avgG = (uint16_t)avgG * 255 / avgR;
          avgB = (uint16_t)avgB * 255 / avgR;
          avgR = 255;
        }
        else if (avgG > 0 && avgG >= avgR && avgG >= avgB)
        {
          avgR = (uint16_t)avgR * 255 / avgG;
          avgB = (uint16_t)avgB * 255 / avgG;
          avgG = 255;
        }
        else if (avgB > 0)
        {
          avgR = (uint16_t)avgR * 255 / avgB;
          avgG = (uint16_t)avgG * 255 / avgB;
          avgB = 255;
        }
        nextGrid.colorLife.colorGrid[x][y] = {avgR, avgG, avgB};
      }
      else
      {
        nextGrid.colorLife.lifeGrid[x][y] = currentGrid.colorLife.lifeGrid[x][y];
        nextGrid.colorLife.colorGrid[x][y] = currentGrid.colorLife.colorGrid[x][y];
      }
    }
  }

  memcpy(&currentGrid.colorLife, &nextGrid.colorLife, sizeof(currentGrid.colorLife));
}

// This is the main display function for the Cellular Automata mode.
void displayCellularAutomata()
{
  static int lastModeType = -1;
  int currentSubmode = state.modeSubmodeIndices[state.currentModeIndex];
  int currentModeType = (currentSubmode <= 2) ? 0 : 1;

  if (currentModeType != lastModeType)
  {
    initCellularAutomata();
    lastModeType = currentModeType;
  }

  long currentUpdateInterval;
  switch (currentSubmode)
  {
  case 0:
  case 3:
    currentUpdateInterval = 33;
    break;
  case 1:
  case 4:
    currentUpdateInterval = 120;
    break;
  case 2:
  case 5:
    currentUpdateInterval = 500;
    break;
  default:
    currentUpdateInterval = 120;
    break;
  }

  if (millis() - lastUpdateTime > currentUpdateInterval)
  {
    lastUpdateTime = millis();
    memset(&nextGrid, 0, sizeof(GridData));

    if (currentModeType == 0)
    {
      calculateNextGenStandard(currentGrid.standard.gridR, nextGrid.standard.gridR);
      calculateNextGenStandard(currentGrid.standard.gridG, nextGrid.standard.gridG);
      calculateNextGenStandard(currentGrid.standard.gridB, nextGrid.standard.gridB);
      memcpy(&currentGrid.standard, &nextGrid.standard, sizeof(currentGrid.standard));
    }
    else
    {
      calculateNextGenColor();
    }
  }

  strip.clear();
  for (int x = 0; x < SIM_WIDTH; x++)
  {
    for (int y = 0; y < SIM_HEIGHT; y++)
    {
      uint8_t r = 0, g = 0, b = 0;
      if (currentModeType == 0)
      {
        r = currentGrid.standard.gridR[x][y] * 255;
        g = currentGrid.standard.gridG[x][y] * 255;
        b = currentGrid.standard.gridB[x][y] * 255;
      }
      else
      {
        if (currentGrid.colorLife.lifeGrid[x][y] == 1)
        {
          Color c = currentGrid.colorLife.colorGrid[x][y];
          r = c.r;
          g = c.g;
          b = c.b;
        }
      }
      if (r > 0 || g > 0 || b > 0)
      {
        strip.setPixelColor(xyToIndex(x, y), r, g, b);
      }
    }
  }
  strip.show();
}