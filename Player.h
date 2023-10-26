// Player.h
#pragma once

#include "Maze.h"
#include <algorithm>



class Player {
private:
    std::pair<int, int> currPosition;
    std::vector<std::pair<int, int>> pastPositions;
    std::vector<std::pair<int, int>> positionStack;
    int sightRange = 1;
    int walkingSpeed = 1;

public:
    Player(const std::pair<int, int>& startPos);
    std::pair<int, int> getCurrPosition() const;
    std::pair<int, int> nextMove(const std::vector<std::pair<std::pair<int,int>, int>>& visualField);
    void rangeIncrease();
    void rangeDecrease();
    int getSightRange() const;
    void speedIncrease();
    void speedDecrease();
    int getWalkingSpeed() const;
    void applyEffects(int cellType);
};
