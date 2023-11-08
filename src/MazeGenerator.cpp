#include "MazeGenerator.h"
#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>

MazeGenerator::MazeGenerator(int width, int height) 
    : WIDTH(width), HEIGHT(height) {}

std::vector<std::vector<int>> MazeGenerator::generateMaze() {
    std::vector<std::vector<int>> maze(HEIGHT, std::vector<int>(WIDTH, 1)); // 1 represents WALL
    std::stack<Position> stack;
    int startX = 1;
    int startY = 1;

    maze[startY][startX] = 2; // 2 represents START
    Position start(startX, startY);

    stack.push(start);

    while (!stack.empty()) {
        Position current = stack.top();
        std::vector<Position> unvisited;

        for (auto dir : directions) {
            if (isValid(current.x + dir.x, current.y + dir.y, maze)) {
                int betweenX = current.x + dir.x / 2;
                int betweenY = current.y + dir.y / 2;
                if (maze[betweenY][betweenX] == 1) {
                    unvisited.push_back(Position(current.x + dir.x, current.y + dir.y));
                }
            }
        }

        if (!unvisited.empty()) {
            Position chosen = unvisited[rand() % unvisited.size()];
            maze[chosen.y][chosen.x] = 0;
            maze[(chosen.y + current.y) / 2][(chosen.x + current.x) / 2] = 0;
            stack.push(chosen);
        } else {
            stack.pop();
        }
    }

    // Add end
    int exitX = WIDTH - 2;
    int exitY = HEIGHT - 2;
    maze[exitY][exitX] = 3; 

    // Add items
    for (int i = 0; i < WIDTH * HEIGHT / 50; ++i) {
        int x, y;
        do {
            x = rand() % (WIDTH - 2) + 1;
            y = rand() % (HEIGHT - 2) + 1;
        } while (maze[y][x] == 1 || maze[y][x] == 2 || maze[y][x] == 3);
        switch (rand() % 4) {
        case 0: maze[y][x] = 4; break;  // 4 are goggles
        case 1: maze[y][x] = 5; break;  // 5 are speed potions
        case 2: maze[y][x] = 6; break;  // 6 are fog
        case 3: maze[y][x] = 7; break;  // 7 are slow potions
        }
    }

    // Add gaps in the walls
    for (int i = 0; i < WIDTH * HEIGHT / 25; ++i) {
        int x, y;
        do {
            x = rand() % (WIDTH - 2) + 1;
            y = rand() % (HEIGHT - 2) + 1;
        } while (maze[y][x] != 1 || (x + y) % 2 == 0);  // Only gaps on the grid with even sum of coordinates are "safe to remove" with no further checks
        maze[y][x] = 0;       
        std::cout << "x: " << x << " y: " << y << std::endl; 
    }

    return maze;
}

bool MazeGenerator::isValid(int x, int y, std::vector<std::vector<int>>& maze) {
    if (x < 1 || x >= WIDTH - 1 || y < 1 || y >= HEIGHT - 1) return false;
    if (maze[y][x] != 1) return false; // 1 represents WALL
    return true;
}
