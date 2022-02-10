#pragma once
#include <ArduinoSTL.h>
#include <deque>
#include <vector>

class Snake{
public:
    Snake(int x, int y);
    void move();
    void moveAndGrow();
    void turnLeft();
    void turnRight();
    std::vector<std::vector<int> > getMap();
    void getMapBinary(uint8_t board[]);
    std::pair<int, int> getHead();
    enum Direction{
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
private:
    std::pair<int, int> getNextPointRelToHead();
    int width = 8;
    int height = 8;
    std::deque<std::pair<int, int> > pos;
    Direction currOrient;
};
