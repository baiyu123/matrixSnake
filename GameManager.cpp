#include "GameManager.h"

GameManager::GameManager(Adafruit_8x8matrix* matrix, uint8_t board[])
  : snake(1, 1)
{
    this->matrix = matrix;
    this->board = board;
}

void GameManager::OnGameStart()
{
    food.generateFood(board);
}

void GameManager::PressLeft()
{
    leftPressed = true;
    rightPressed = false;
}

void GameManager::PressRight()
{
    rightPressed = true;
    leftPressed = false;
}

void GameManager::ClearPress()
{
    leftPressed = false;
    rightPressed = false;
}

void GameManager::Update()
{
    if(leftPressed){
        snake.turnLeft();
    }
    if(rightPressed){
        snake.turnRight();
    }

    std::pair<int, int> head = snake.getHead();
    if(food.checkEat(head)){
        snake.moveAndGrow();
        snake.getMapBinary(board); 
        food.generateFood(board);
    }
    else{
        snake.move();
        snake.getMapBinary(board); 
    }
    food.drawLastFood(board);
    matrix->clear();
    matrix->drawBitmap(0, 0, board, 8, 8, LED_ON);
    matrix->writeDisplay();
    ClearPress();
}
