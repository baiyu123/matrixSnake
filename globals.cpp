#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "GameManager.h"

unsigned long gameUpdateIntval = 500;
static const uint8_t PROGMEM
  game_board[] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100
  },
  heart_bmp[]=
    {
      B01100110,
      B11111111,
      B10011001,
      B10000001,
      B11000011,
      B01100110,
      B00111100,
      B00011000
    };
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
GameManager manager(&matrix, game_board);