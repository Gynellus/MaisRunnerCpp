// Player.h
#pragma once

#include "Maze.h"
#include "Tile.h"

class Player {
private:
    Tile currTile; // Current position as Tile
    std::vector<Tile> pastTiles; // Track past tiles visited
    std::vector<Tile> tileStack; // Stack for backtracking
    int sightRange = 1; // The player's sight range
    int walkingSpeed = 1; // The player's walking speed

public:
    Player(const Tile& startTile);
    Tile getCurrTile() const;
    Tile nextMove(const std::vector<Tile>& visualField);
    void rangeIncrease();
    void rangeDecrease();
    int getSightRange() const;
    void speedIncrease();
    void speedDecrease();
    int getWalkingSpeed() const;
    void applyEffects(int cellType);
};
