#include "Player.h"
#include <iostream>
#include <algorithm>
// #include <cstdlib> // for rand()

// Constructor implementation
Player::Player(const Tile &startTile) 
    : currTile(startTile) {
    pastTiles.push_back(startTile);
    tileStack.push_back(startTile);
}

// getCurrTile method implementation
Tile Player::getCurrTile() const {
    return currTile;
}

// nextMove method implementation
Tile Player::nextMove(const std::vector<Tile>& visualField) {
    std::vector<Tile> possibleMoves;

    for (const auto& tile : visualField) {
        // Check if the tile is within one step of the current position
        if(std::abs(tile.x - currTile.x) + std::abs(tile.y - currTile.y) == 1) {
            // if the tile is the end, return the position
            if (tile.value == 3) {
                currTile = tile;
                return currTile;
            }

            // if the tile is empty, and not in pastTiles, add it to possibleMoves
            if (tile.value != 1 && std::find_if(pastTiles.begin(), pastTiles.end(), 
                [tile](const Tile& t) { return t.x == tile.x && t.y == tile.y; }) == pastTiles.end()) {
                possibleMoves.push_back(tile);
            }
        }
    }
    
    // if there are no possible moves, pop the tileStack and return the top
    if (possibleMoves.empty()) {
        if(!tileStack.empty()) {
            currTile = tileStack.back();
            tileStack.pop_back();
            return currTile;
        } else {
            // if there are no tiles in the tileStack, return the current tile
            return currTile;
        }
    } else {
        // if there are possible moves, push the current tile to the tileStack
        tileStack.push_back(currTile);
        // choose a random move from possibleMoves
        int randIndex = rand() % possibleMoves.size();
        currTile = possibleMoves[randIndex];
        // apply effects based on current tile type;
        applyEffects(possibleMoves[randIndex].value);
        // add the current tile to pastTiles
        pastTiles.push_back(currTile);
        return currTile;
    }
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
    if (sightRange > 3) {
        sightRange = 3;
    }
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
    if (walkingSpeed > 3) {
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

