#pragma once
#include <arduino.h>


class food{
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

bool food::checkEat(std::pair<int,int> head){
    if(head.second == m_col && head.first == m_row){
        return true;
    }
    return false;
}

void food::drawLastFood(uint8_t board[]){
    int width = 8;
    uint8_t row_8 = 1;
    row_8 <<= (width - 1 - m_col);
    board[m_row] |= row_8;
}

void food::generateFood(uint8_t board[]){
    int width = 8;
    for(int i = 0; i < 1000; i++){
        int row = random(8);
        int col = random(8);
        uint8_t row_8 = 1;
        row_8 <<= (width-1-col);
        m_col = col;
        m_row = row;
        //check if generated food is on snake
        uint8_t result = row_8 & board[row];
        // no conflict
        if(result == 0){
            // board[row] |= row_8;
            break;
        }
    }

}