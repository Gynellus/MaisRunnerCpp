#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <fstream>

const int WIDTH = 23;
const int HEIGHT = 23;

enum Cell {
    EMPTY = 0,
    WALL = 1,
    START = 2,
    END = 3,
    GOGGLES = 4,
    SPEED_POTION = 5,
    FOG = 6,
    SLOW_POTION = 7,
    VISITED = 8
};

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

bool isValid(int x, int y, std::vector<std::vector<Cell>>& maze) {
    if (x < 1 || x >= WIDTH - 1 || y < 1 || y >= HEIGHT - 1) return false;
    if (maze[y][x] != WALL) return false;
    return true;
}

int findLatestSerialNumber() { // Finds the latest number to save the file appropriately    
    int num = 1;
    while (true) {
        std::ifstream testFile("./mazes/generated/maze" + std::to_string(num) + ".txt");
        if (!testFile) { // Use the stream to check if the file exists.
            break;
        }
        ++num;
        testFile.close();
    }
    return num;
}

std::vector<std::vector<Cell>> generateMaze() {
    std::vector<std::vector<Cell>> maze(HEIGHT, std::vector<Cell>(WIDTH, WALL));
    std::stack<Position> stack;
    int startX = 1;
    int startY = 1;

    Position start(startX, startY);
    maze[start.y][start.x] = START;

    stack.push(start);

    while (!stack.empty()) {
        Position current = stack.top();
        std::vector<Position> unvisited;

        for (auto dir : directions) {
            if (isValid(current.x + dir.x, current.y + dir.y, maze)) {
                int betweenX = current.x + dir.x / 2;
                int betweenY = current.y + dir.y / 2;
                if (maze[betweenY][betweenX] == WALL) {
                    unvisited.push_back(Position(current.x + dir.x, current.y + dir.y));
                }
            }
        }

        if (!unvisited.empty()) {
            Position chosen = unvisited[rand() % unvisited.size()];
            maze[chosen.y][chosen.x] = EMPTY;
            maze[(chosen.y + current.y) / 2][(chosen.x + current.x) / 2] = EMPTY;
            stack.push(chosen);
        } else {
            stack.pop();
        }
    }

    // Add end
    int exitX = WIDTH - 2;
    int exitY = HEIGHT - 2;
    maze[exitY][exitX] = END; 

    // Add items
    for (int i = 0; i < WIDTH * HEIGHT / 50; ++i) {
        int x, y;
        do {
            x = rand() % WIDTH;
            y = rand() % HEIGHT;
        } while (maze[y][x] == START || maze[y][x] == END );
        switch (rand() % 4) {
        case 0: maze[y][x] = GOGGLES; break;
        case 1: maze[y][x] = SPEED_POTION; break;
        case 2: maze[y][x] = FOG; break;
        case 3: maze[y][x] = SLOW_POTION; break;
        }
    }

    // Add gaps in the walls
    for (int i = 0; i < WIDTH * HEIGHT / 25; ++i) {
        int x, y;
        do {
            x = rand() % (WIDTH - 2) + 1;
            y = rand() % (HEIGHT - 2) + 1;
        } while (maze[y][x] != 1 || (x + y) % 2 == 0);  // Only gaps on the grid with even sum of coordinates are "safe to remove" with no further checks
        maze[y][x] = EMPTY;       
        std::cout << "x: " << x << " y: " << y << std::endl; 
    }

    return maze;
}

int main() {
    srand((unsigned int)time(0));
    std::vector<std::vector<Cell>> maze = generateMaze();

    int serialNum = findLatestSerialNumber();

    for (int i = 0; i < 100; i++)
    {
        std::string fileName = "./mazes/generated/maze" + std::to_string(serialNum) + ".txt";
        std::ofstream outFile(fileName);

        outFile << "[\n";
        for (int y = 1; y < HEIGHT - 1; y++) {  // Skip the first and last row
            outFile << "[";
            for (int x = 1; x < WIDTH - 1; x++) {  // Skip the first and last column
                outFile << maze[y][x];
                if (x != WIDTH - 2) outFile << ", ";
            }
            outFile << "]";
            if (y != HEIGHT - 2) outFile << ",\n";
        }
        outFile << "\n]";
        outFile.close();

        std::cout << "Maze saved to " << fileName << "!" << std::endl;
        serialNum++;
    }
    
    return 0;
}
