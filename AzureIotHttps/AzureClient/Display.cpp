#include "Display.h"
#include "libraries/LedMatrix/LedMatrix.h"
#include "libraries/LedMatrix/cp437font.h"


#define NUMBER_OF_DEVICES 1
#define CS_PIN 2
#define DISPLAY_SIZE 8
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

enum Side { LEFT, RIGHT, TOP, BOTTOM };

int shift = 0;

void DrawArrow(LedMatrix &led, int shift, Side side)
{
  int defaultStep = DISPLAY_SIZE / 2 - 1;
  int step = defaultStep;
  
  for (int x = -shift; x < DISPLAY_SIZE; x++)
  {
    if (x >= 0)
    {
      for (int y = step; y < DISPLAY_SIZE - step; y++)
      {
        switch(side)
        {
            case LEFT   : led.setPixel(x, y); break;
            case RIGHT  : led.setPixel(DISPLAY_SIZE - x - 1, y); break;
            case TOP    : led.setPixel(y, x); break;
            case BOTTOM : led.setPixel(y, DISPLAY_SIZE - x - 1); break;
        }
      }
    }
    if (--step < 0)
    {
      step = defaultStep;
    }
  }
}

void displaySetup() {
  Serial.begin(115200); // For debugging output
  ledMatrix.init();
  ledMatrix.setIntensity(1); // range is 0-15
}

void displayClear()
{
  ledMatrix.clear();
}

void displayShow()
{
  shift = (shift + 1) % 8;
  DrawArrow(ledMatrix, shift, LEFT);
  ledMatrix.commit(); // commit transfers the byte buffer to the displays
}

