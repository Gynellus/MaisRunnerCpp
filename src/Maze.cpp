// Maze.cpp
#include "Maze.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>


// Constructor implementations
Maze::Maze(const std::string& filePath) {
    loadFromFile(filePath);
}

Maze::Maze(const std::vector<std::vector<int>>& data) {
    mazeData = data;
}

void Maze::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        // Clear existing maze data
        mazeData.clear();

        std::vector<std::vector<int>> tempMazeData; // Temporary storage for the original maze data

        // Read and parse the maze data
        std::string line;
        while (std::getline(file, line)) {
            // Skip lines that are not row data
            if (line.find('[') == std::string::npos || line.find(']') == std::string::npos)
                continue;

            std::vector<int> row;

            // Remove '[' and ']' from the line
            line.erase(std::remove(line.begin(), line.end(), '['), line.end());
            line.erase(std::remove(line.begin(), line.end(), ']'), line.end());

            size_t pos = 0;
            while ((pos = line.find(',')) != std::string::npos) {
                try {
                    row.push_back(std::stoi(line.substr(0, pos)));
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid integer value: " << line.substr(0, pos) << " in file: " << filePath << std::endl;
                    throw;
                }
                line.erase(0, pos + 1);
            }
            // For the last number in the line
            if (!line.empty()) {
                try {
                    row.push_back(std::stoi(line));
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid integer value: " << line << " in file: " << filePath << std::endl;
                    throw;
                }
            }

            tempMazeData.push_back(row);
        }
        file.close();  // close the file once after reading all the data

        // Now that we have read the maze data into tempMazeData,
        // we will modify mazeData to encase the maze in walls

        // Add a top wall
        mazeData.push_back(std::vector<int>(tempMazeData[0].size() + 2, 1));

        // Add walls to the sides of the maze
        for (const auto& row : tempMazeData) {
            std::vector<int> newRow = {1};  // Start with a left wall
            newRow.insert(newRow.end(), row.begin(), row.end());
            newRow.push_back(1);  // Add a right wall
            mazeData.push_back(newRow);
        }

        // Add a bottom wall
        mazeData.push_back(std::vector<int>(tempMazeData[0].size() + 2, 1));

    } else {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        exit(1);
    }
}

// getData method implementation
const std::vector<std::vector<int>>& Maze::getData() const {
    return mazeData;
}

Tile Maze::getStart() const {
    for (int i = 0; i < mazeData.size(); ++i) {
        for (int j = 0; j < mazeData[i].size(); ++j) {
            if (mazeData[i][j] == 2)    // Find 2 in the maze 
                return Tile(i, j, mazeData[i][j]);
        }
    }
    return Tile(-1, -1, -1); // Indicating an invalid tile if no start is found
}

Tile Maze::getEnd() const {
    for (int i = 0; i < mazeData.size(); ++i) {
        for (int j = 0; j < mazeData[i].size(); ++j) {
            if (mazeData[i][j] == 3)    // Find 3 in the maze
                return Tile(i, j, mazeData[i][j]);
        }
    }
    return Tile(-1, -1, -1); // Indicating an invalid tile if no end is found
}

std::vector<Tile> Maze::getVisualField(const Tile& pos, const int sightRange) const {
    std::vector<Tile> visualField;

    int dx[] = {0, 0, -1, 1};   // Horizontal directions
    int dy[] = {-1, 1, 0, 0};   // Vertical directions

    for (int dir = 0; dir < 4; dir++) {
        int x = pos.x;
        int y = pos.y;
        for (int dist = 1; dist <= sightRange; dist++) {    // Look in each direction as much as the sightRange allows
            x += dx[dir];   // From current position add the appropriate offset, horizontal
            y += dy[dir];   // and vertical
            if (x < 0 || x >= mazeData.size() || y < 0 || y >= mazeData[x].size() || mazeData[x][y] == 1) { 
                visualField.push_back(Tile(x, y, mazeData[x][y]));
                break; // If there's a wall or we're somehow looking out of the boundaries of the maze, break
            }
            visualField.push_back(Tile(x, y, mazeData[x][y])); // Add tile to the visual field
        }
    }
    return visualField;
}

int Maze::getCell(const Tile& pos) const {
    return mazeData[pos.x][pos.y];
}

void Maze::setCell(const Tile& pos, const int value) {
    mazeData[pos.x][pos.y] = value;
}

