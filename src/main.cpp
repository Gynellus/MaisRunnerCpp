// main.cpp
#include "Maze.h"
#include "MazeGUI.h"
#include "Player.h"
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>  

namespace fs = std::filesystem;

int getRandomMazeNumber(int max) {
    return (rand() % max) + 1;
}

std::string getRandomMazePath(const std::string& dirPath) {
    int mazeCount = 0;
    for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            ++mazeCount;
        }
    }
    int randomMazeNumber = getRandomMazeNumber(mazeCount);
    return dirPath + "/maze" + std::to_string(randomMazeNumber) + ".txt";
}

int main() {
    srand((int) time(0));

    // Pick a random maze from the mazes/generated folder
    std::string mazePath = getRandomMazePath("mazes/generated");
    Maze maze(mazePath);
    
    Player player(maze.getStart());
    MazeGUI gui(maze, player);

    int steps = 0;
    
    while (player.getCurrPosition() != maze.getEnd()) {
        for (int i = 0; i < player.getWalkingSpeed(); i++) {
            gui.displayMaze();
            player.nextMove(maze.getVisualField(player.getCurrPosition(), player.getSightRange()));
            if (player.getCurrPosition() == maze.getEnd()) {
                break;
            }
            maze.setCell(player.getCurrPosition(), 8);
        }
        ++steps;
        // usleep(50000);
    }
    gui.displayMaze();
    std::cout << "You escaped " << mazePath << " in " << steps << " steps!" << std::endl;
    return 0;
}
