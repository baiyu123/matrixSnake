#pragma once
#include <Arduino.h>
#include <ArduinoSTL.h>

class Food{
public:
    food(){
        m_row = 0;
        m_col = 0;
    }
    void generateFood(uint8_t board[]);
    void drawLastFood(uint8_t board[]);
    bool checkEat(std::pair<int,int> head);
private:
    int m_row;
    int m_col;
};
