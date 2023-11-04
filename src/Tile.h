#pragma once

// Tile struct definition
struct Tile {
    int x, y; // Location of the tile within the maze
    int value; // What's in the tile: wall, path, start, end, etc.

    Tile(int x = 0, int y = 0, int value = 0) : x(x), y(y), value(value) {}

    // Define the equality operator. Two tiles are equal if they are located at the same position 
    bool operator==(const Tile& other) const {
        return x == other.x && y == other.y;
    }

    // Define the inequality operator. Two tiles are not equal if they are not located at the same position
    bool operator!=(const Tile& other) const {
        return x != other.x || y != other.y;
    }

    
};
