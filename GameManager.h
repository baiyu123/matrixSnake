#pragma once
#include "snake.h"
#include "food.h"
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

class GameManager{
    public:
        GameManager();
        GameManager(Adafruit_8x8matrix* matrix, uint8_t board[]);
        void OnGameStart();
        void Update(unsigned long);
        void PressLeft();
        void PressRight();
        void ClearPress();
    private:
        Snake snake;
        Food food;
        Adafruit_8x8matrix* matrix;
        uint8_t* board;
        enum GameState{
            GAME_START,
            GAME_END
        };
        GameState gameState;
        bool leftPressed;
        bool rightPressed;
        unsigned long lastUpdate;
};
