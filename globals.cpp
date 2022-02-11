#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "GameManager.h"
#include <ArduinoSTL.h>

unsigned long gameUpdateIntval = 500;
unsigned long inputUpdateIntval = 500;

const uint8_t PROGMEM
  game_board[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
GameManager manager(&matrix, game_board);

