// Maze.h
#pragma once

#include <vector>
#include <string>

class Maze {
private:
    std::vector<std::vector<int>> mazeData;

public:
    // Constructor declaration
    Maze(const std::string& filePath);

    // Method declarations
    void loadFromFile(const std::string& filePath);
    const std::vector<std::vector<int>>& getData() const;
    std::pair<int, int> getStart() const;
    std::pair<int, int> getEnd() const;
    std::vector<std::pair<std::pair<int,int>, int>> getVisualField(const std::pair<int, int>& pos, const int sightRange) const;
    int getCell(const std::pair<int, int>& pos) const;
    void setCell(const std::pair<int, int>& pos, const int value);
};
