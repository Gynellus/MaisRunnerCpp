#include "Player.h"

// Constructor implementation
Player::Player(const std::pair<int, int> &startPos) 
    : currPosition(startPos) {
    pastPositions.push_back(startPos);
    positionStack.push_back(startPos);
}

// getCurrPosition method implementation
std::pair<int, int> Player::getCurrPosition() const {
    return currPosition;
}

// nextMove method implementation
std::pair<int, int> Player::nextMove(const std::vector<std::pair<std::pair<int,int>, int>>& visualField) {
    std::vector<std::pair<std::pair<int, int>, int>> possibleMoves;

    for (const auto& cell : visualField) {
        std::pair<int, int> position = cell.first;
        int cellType = cell.second;
        
        // Check if the position is within one step of the current position
        if(std::abs(position.first - currPosition.first) + std::abs(position.second - currPosition.second) == 1) {
            // if the cell is the end, return the position
            if (cellType == 3) {
                currPosition = position;
                return currPosition;
            }

            // if the cell is empty, and not in pastPositions, add it to possibleMoves
            if (cellType != 1 && std::find(pastPositions.begin(), pastPositions.end(), position) == pastPositions.end()) {
                possibleMoves.push_back(std::make_pair(position, cellType));
            }
        }
    }
    
    // if there are no possible moves, pop the positionStack and return the top
    if (possibleMoves.size() == 0) {
        if(positionStack.size() > 0) {
            positionStack.pop_back();
            currPosition = positionStack.back();
            return currPosition;
        } else {
            // if there are no positions in the positionStack, return the current position
            return currPosition;
        }
    } else {
        // if there are possible moves, push the current position to the positionStack
        positionStack.push_back(currPosition);
        // choose a random move from possibleMoves
        int randIndex = rand() % possibleMoves.size();
        currPosition = possibleMoves[randIndex].first;
        // apply effects based on current cell type;
        applyEffects(possibleMoves[randIndex].second);
        // add the current position to pastPositions
        pastPositions.push_back(currPosition);
        return currPosition;
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

