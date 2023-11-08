// Maze.h
#pragma once

#include <vector>
#include <string>
#include <utility>
#include "Tile.h"

class Maze {

private:
    std::vector<std::vector<int>> mazeData;  // 2D vector to store maze data
    void loadFromFile(const std::string& filePath);  // Helper method to load maze from a file


public:
    Maze(const std::string& filePath);  // Constructor to load maze from a file
    Maze(const std::vector<std::vector<int>>& mazeData); // Constructor to load maze from a 2D vector
    const std::vector<std::vector<int>>& getData() const;  // Method to get maze data
    
    Tile getStart() const;   // Returns the start position as a Tile
    Tile getEnd() const;     // Returns the end position as a Tile
    std::vector<Tile> getVisualField(const Tile& pos, int sightRange) const;  // Method to get the visual field as Tiles

    int getCell(const Tile& pos) const;     // Method to get the value of a cell
    void setCell(const Tile& pos, int value);   // Method to set the value of a cell
};
