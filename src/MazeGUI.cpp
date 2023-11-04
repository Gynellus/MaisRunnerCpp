// MazeGUI.cpp

#include "MazeGUI.h"

// Constructor implementation
MazeGUI::MazeGUI(const Maze& m, const Player& p) : maze(m), player(p) {}

// displayMaze method implementation
void MazeGUI::displayMaze() {
    const auto& data = maze.getData();
    Tile playerPos = player.getCurrTile();
    std::vector<Tile> visualField = maze.getVisualField(playerPos, player.getSightRange());

    for (int i = 0; i < data.size(); ++i) {
        const auto& row = data[i];
        for (int j = 0; j < row.size(); ++j) {
            int cell = row[j];

            // Check if the current cell is within the visual field
            bool isInVisualField = false;
            for (const auto& cell : visualField) {
                if (cell.x == i && cell.y == j) {
                    isInVisualField = true;
                    break;
                }
            }
            
            if (isInVisualField) {
                std::cout << "\033[32m";  // Set text color to green
            }

            if (i == playerPos.x && j == playerPos.y) {
                std::cout << "\033[32m";  // Set text color to green
                std::cout << "PP";  // Player
                std::cout << "\033[0m"; // Reset text color to default
            } else {

                switch (cell) {
                    case 0: std::cout << "  "; break; // empty space
                    case 1: std::cout << "##"; break; // wall
                    case 2: std::cout << "ST"; break; // start
                    case 3: std::cout << "EN"; break; // end
                    case 4: std::cout << "GG"; break; // goggles
                    case 5: std::cout << "SP"; break; // speed potion
                    case 6: std::cout << "FO"; break; // fog
                    case 7: std::cout << "SL"; break; // slow potion
                    case 8: std::cout << ".."; break; // visited
                    default: std::cout << "??"; break; // unknown
                }
            }
            
            if (isInVisualField) {
                std::cout << "\033[0m";  // Reset text color to default
            }
        }
        std::cout << std::endl;
    }
}

