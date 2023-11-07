// Player.h
#pragma once

#include "Maze.h"
#include "Tile.h"

class Player {
private:
    Tile currTile; // Current position as Tile
    std::vector<Tile> tileStack; // Stack for backtracking
    int sightRange = 1; // The player's sight range
    int walkingSpeed = 1; // The player's walking speed
    
    void applyEffects(int cellType); // Method to apply effects of a cell
    Tile getStepTowards(const Tile& target); // Method to get a step towards a target tile
    void speedIncrease();
    void speedDecrease();
    void rangeIncrease();
    void rangeDecrease();

public:
    Player(const Tile& startTile);
    Tile getCurrTile() const;
    Tile nextMove(const std::vector<Tile>& visualField);
    int getSightRange() const;
    int getWalkingSpeed() const;
};
