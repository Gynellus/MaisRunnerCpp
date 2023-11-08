#include "Maze.h"
#include "MazeGUI.h"
#include "Player.h"
#include "MazeGenerator.h"
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

// Function to get a random number within a given range (1 to max).
int getRandomMazeNumber(int max) {
    return (rand() % max) + 1;
}

// Function to get a random maze file path from a specified directory.
std::string getRandomMazePath(const std::string& dirPath) {
    int mazeCount = 0;
    // Count the number of maze files in the directory.
    for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            ++mazeCount;
        }
    }

    // Check if there are any maze files in the directory.
    if (mazeCount == 0) {
        throw std::runtime_error("No maze files found in the directory.");
    }

    // Choose a random maze file.
    int randomMazeNumber = getRandomMazeNumber(mazeCount);
    return dirPath + "/maze" + std::to_string(randomMazeNumber) + ".txt";
}

int main(int argc, char *argv[]) {
    srand((int) time(0));

    bool useRandomMaze = false;

    // Loop through command-line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-r") {
            useRandomMaze = true;
            break;
        }
    }

    Maze maze("mazes/maze1.txt"); // Initialize with a maze from file.
    if (useRandomMaze) {
        maze = MazeGenerator(23,23).generateMaze(); // Generate a random maze.
    }

    Player player(maze.getStart());
    MazeGUI gui(maze, player);


    int steps = 0;

    // Main game loop that continues until the player reaches the end of the maze.
    while (player.getCurrTile() != maze.getEnd()) {
        for (int i = 0; i < player.getWalkingSpeed(); i++) {    // The player moves multiple steps per iteration, if speed > 1.
            gui.displayMaze();
            player.nextMove(maze.getVisualField(player.getCurrTile(), player.getSightRange()));
            // Break if the player reaches the end.
            if (player.getCurrTile() == maze.getEnd()) {
                break;
            }
            // Mark the current tile as explored.
            maze.setCell(player.getCurrTile(), 8); // 8 is the value assigned to previously explored tiles.
        }
        ++steps;
        usleep(50000); // adds a delay in visualization (default 50 milliseconds).
    }

    // Display the final state of the maze and the number of steps taken.
    gui.displayMaze();
    std::cout << "You escaped the maze in " << steps << " steps!" << std::endl;

    return 0;
}