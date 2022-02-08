#pragma once
#include <deque>
#include <vector>

class snake{
public:
    snake(int x, int y, int vX, int vY);
    void move();
    void moveAndGrow();
    void turnLeft();
    void turnRight();
    std::vector<std::vector<int> > getMap();
    void getMapBinary(uint8_t board[]);
    std::pair<int, int> getHead();
private:
    void multiplyOrient(std::vector<std::vector<int> > v);
    int width = 8;
    int height = 8;
    std::deque<std::pair<int, int> > pos;
    std::pair<int, int> currOrient;
};
