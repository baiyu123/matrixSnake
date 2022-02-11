#include "snake.h"
#include "matrixUtility.h"
#include <vector>
#include <iostream>
#include <SoftwareSerial.h>

using namespace std;

Snake::Snake(int x, int y){
    currOrient = Direction::RIGHT;
    auto nextPos = Snake::getNextPointRelToHead();
    pair<int, int> s1(x,y);
    pair<int, int> s2(x-nextPos.first,y-nextPos.second);
    pos.push_back(s1);
    pos.push_back(s2);
}

std::pair<int, int> Snake::getNextPointRelToHead(){
    switch(currOrient)
    {
        case Direction::UP:
            return make_pair<int, int>(-1,0);
        case Direction::RIGHT:
            return make_pair<int, int>(0,1);
        case Direction::DOWN:
            return make_pair<int, int>(1,0);
        case Direction::LEFT:
            return make_pair<int, int>(0,-1);
        default:
          return make_pair<int, int>(0,-1);
    }
}

void Snake::move(){
    moveAndGrow();
    pos.pop_back();
}

void Snake::moveAndGrow(){
    auto nextPos = getNextPointRelToHead();
    int nextX = pos[0].first + nextPos.first;
    int nextY = pos[0].second + nextPos.second;
    if(nextX >= width){
        nextX = 0;
    }
    if(nextX < 0){
        nextX = width-1;
    }
    if(nextY >= height){
        nextY = 0;
    }
    if(nextY < 0){
        nextY = width-1;
    }
    bool intersect = false;
    for(int i = 0; i < pos.size(); i++){
      if(nextX == pos[i].first && nextY == pos[i].second) {
        intersect = true;
      } 
    }
    if(!intersect){
      pair<int, int> nextStep(nextX, nextY);
      pos.push_front(nextStep);
    }
}

void Snake::turnLeft(){
    currOrient = (currOrient+3)%4;
}

void Snake::turnRight(){
    currOrient = (currOrient+1)%4;
}

void Snake::getMapBinary(uint8_t board[]){
    for(int i = 0; i < width; i++){
        board[i] = 0;
    }
    for(int i = 0; i < pos.size(); i++){
        uint8_t row = 1;
        int shift = (uint8_t)(width-1-pos[i].second);
        row <<= shift;
        board[pos[i].first] |= row;
    }
}

vector<vector<int> > Snake::getMap(){
    vector<vector<int> > board=  {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    for(int i = 0; i < pos.size(); i++){
        board[pos[i].first][pos[i].second] = 1;
    }
    return board;
}

//get the head of snake
pair<int, int> Snake::getHead(){
    return pos[0];
}
