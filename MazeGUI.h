// MazeGUI.h

#pragma once

#include "Maze.h"
#include "Player.h"
#include <iostream>

class MazeGUI {
private:
    const Maze& maze; 
    const Player& player;

public:
    MazeGUI(const Maze& m, const Player& p);  
    void displayMaze();
};
