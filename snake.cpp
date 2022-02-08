#include "snake.h"
#include "matrixUtility.h"
#include <vector>
#include <iostream>

using namespace std;

snake::snake(int x, int y, int vX, int vY){
    pair<int, int> s1(x,y);
    pair<int, int> s2(x-vX,y-vY);
    pos.push_back(s1);
    pos.push_back(s2);
    currOrient.first = vX;
    currOrient.second = vY;
}

void snake::move(){
    moveAndGrow();
    pos.pop_back();
}

void snake::moveAndGrow(){
    int nextX = pos[0].first + currOrient.first;
    int nextY = pos[0].second + currOrient.second;
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

void snake::turnLeft(){
    vector<vector<int> > mat1 = {{0, -1},
        {1, 0}};
    multiplyOrient(mat1);
}

void snake::turnRight(){
    vector<vector<int> > mat1 = {{0, 1},
        {-1, 0}};
    multiplyOrient(mat1);
}

void snake::multiplyOrient(vector<std::vector<int> > mat1){
    vector<vector<int> > mat2 = {{currOrient.first},
        {currOrient.second}};
    vector<vector<int> > mat3 = {{0},
        {0}};
    multiplyMat(mat1, mat2, mat3);
    currOrient.first = mat3[0][0];
    currOrient.second = mat3[1][0];
}

void snake::getMapBinary(uint8_t board[]){
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

vector<vector<int> > snake::getMap(){
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
pair<int, int> snake::getHead(){
    return pos[0];
}
