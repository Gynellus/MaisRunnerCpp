#include "Player.h"
#include <iostream>
#include <algorithm>

// Constructor implementation
Player::Player(const Tile &startTile) 
    : currTile(startTile) {
    tileStack.push_back(startTile);
}

// getCurrTile method implementation
Tile Player::getCurrTile() const {
    return currTile;
}

// nextMove method implementation
Tile Player::nextMove(const std::vector<Tile>& visualField) {
    std::vector<Tile> possibleMoves;
    std::vector<Tile> lastResortMoves; // Moves that lead to powerdowns

    for (const auto& tile : visualField) {  // In this for loop we evaluate each tile in the visual field for potential moves

        // Check if the tile is within one step of the current position (therefore a valid move)
        if(std::abs(tile.x - currTile.x) + std::abs(tile.y - currTile.y) == 1) {
            // if the tile is the end, return the position
            if (tile.value == 3) {
                currTile = tile;
                return currTile;
            }

            // if the tile is not a wall, and has not been visited before, add it to possibleMoves
            if (tile.value != 1 && tile.value != 2 && tile.value != 8) {
                possibleMoves.push_back(tile);
            }
        } else {    // if the tile is not within one step of the current position, it is not a potential move but can inform movement decision
            if (tile.value == 3) { // if the tile is the end, we can move towards it
                currTile = getStepTowards(tile);
                // Apply potential new effects
                applyEffects(currTile.value);
                return currTile;
            } else if (tile.value == 4 || tile.value == 5) {
                // if the tile is a powerup, boost the chances of moving to the tile that leads to it by adding it (potentially twice) to possibleMoves
                Tile step = getStepTowards(tile);
                possibleMoves.push_back(step);
            } else if (tile.value == 6 || tile.value == 7) {
                Tile step = getStepTowards(tile);
                // if the tile is a powerdown, remove it from possibleMoves and add it to lastResortMoves
                possibleMoves.erase(std::remove(possibleMoves.begin(), possibleMoves.end(), step), possibleMoves.end());                
                lastResortMoves.push_back(step);
            }

        }
        
    }
  
    if (possibleMoves.empty() && lastResortMoves.empty()) { // No new moves, need to backtrack
        if(backtrack == false) {    // Waste the first backtracking turn (half a turn each step, can't turn 180 degrees)
            backtrack = true;
            return currTile;
        }
        if(!tileStack.empty()) {
            currTile = tileStack.back();
            tileStack.pop_back();
            return currTile;
        } else {
            // If there are no tiles in the tileStack, return the current tile
            return currTile;
        }
    } else if (!possibleMoves.empty()) {    // if there are possible moves, pick one
        backtrack = false;
        tileStack.push_back(currTile);
        std::vector<Tile> temp;

        for (const auto& tile : possibleMoves) {
            if (tile.value == 4 || tile.value == 5) {
                temp.push_back(tile);   // if the tile is a powerup, add it to temp
            }
        }
        
        if (!temp.empty()) {    // if there are powerups in temp, pick one of them
            int randIndex = rand() % temp.size();
            currTile = temp[randIndex];
            // apply effects based on current tile type;
            applyEffects(temp[randIndex].value);
            return currTile;
        } else {    // if there are no powerups in temp, pick a random tile from possibleMoves
            int randIndex = rand() % possibleMoves.size();
            currTile = possibleMoves[randIndex];
            return currTile;
        }
    } else {    // if there are no possible moves, but there are lastResortMoves, choose a random move from lastResortMoves
        backtrack = false;
        tileStack.push_back(currTile);
        int randIndex = rand() % lastResortMoves.size();
        currTile = lastResortMoves[randIndex];
        // apply effects based on current tile type;
        applyEffects(lastResortMoves[randIndex].value);
        return currTile;
    }
}

Tile Player::getStepTowards(const Tile& target) {  // Step towards a tile that is not immediatly reachable
    Tile step = currTile; // Start with the current tile
    int dx = target.x - currTile.x;
    int dy = target.y - currTile.y;

    if (dx > 0) {
        step.x += 1; // Move right
    } else if (dx < 0) {
        step.x -= 1; // Move left
    } else if (dy > 0) {
        step.y += 1; // Move down
    } else if (dy < 0) {
        step.y -= 1; // Move up
    }

    return step;
}


void Player::applyEffects(int cellType) {
    switch (cellType) {
        case 4: this->rangeIncrease(); break;
        case 5: this->speedIncrease(); break;
        case 6: this->rangeDecrease(); break;
        case 7: this->speedDecrease(); break;
        default: break;
    }
}

// range methods
void Player::rangeIncrease() {
    sightRange++;
}

void Player::rangeDecrease() {
    sightRange--;
    if (sightRange < 1) {
        sightRange = 1;
    }
}

// getSightRange method implementation
int Player::getSightRange() const {
    return sightRange;
}

// speed methods
void Player::speedIncrease() {
    walkingSpeed++;
    if (walkingSpeed > 3) { // Limit speed to 3
        walkingSpeed = 3;
    }
}

void Player::speedDecrease() {
    walkingSpeed--;
    if (walkingSpeed < 1) {
        walkingSpeed = 1;
    }
}

// getWalkingSpeed method implementation
int Player::getWalkingSpeed() const {
    return walkingSpeed;
}