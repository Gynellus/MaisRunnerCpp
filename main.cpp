// main.cpp
#include "Maze.h"
#include "MazeGUI.h"
#include "Player.h"
#include <unistd.h>

int main() {
    Maze maze("maze1.txt");
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
        usleep(50000);
    }
    gui.displayMaze();
    std::cout << "You escaped the maze in " << steps << " steps!" << std::endl;
    return 0;
}