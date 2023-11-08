//MazeGenerator.h
#pragma once

#include <vector>
#include <stack>

class MazeGenerator {
public:
    MazeGenerator(int width, int height);
    std::vector<std::vector<int>> generateMaze();

private:
    const int WIDTH;
    const int HEIGHT;

    struct Position {
        int x, y;
        Position(int x, int y) : x(x), y(y) {}
    };

    std::vector<Position> directions = {
        Position(0, -2),
        Position(2, 0),
        Position(0, 2),
        Position(-2, 0)
    };

    bool isValid(int x, int y, std::vector<std::vector<int>>& maze);
};

