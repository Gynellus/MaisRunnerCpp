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

int findLatestSerialNumber() {
    int num = 1;
    while (true) {
        std::ifstream testFile("./mazes/generated/maze" + std::to_string(num) + ".txt");
        if (!testFile) { // Use the stream itself to check the state.
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
    int startX = 2 * (rand() % ((WIDTH - 1) / 2)) + 1;
    int startY = 2 * (rand() % ((HEIGHT - 1) / 2)) + 1;

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

    // Set a random edge cell as the exit, but not on the outermost row/column
    Position exitPos(0,0);
    switch (rand() % 4) {
    case 0: 
        exitPos = Position(rand() % (WIDTH - 2) + 1, 1); 
        break;
    case 1: 
        exitPos = Position(rand() % (WIDTH - 2) + 1, HEIGHT - 2); 
        break;
    case 2: 
        exitPos = Position(1, rand() % (HEIGHT - 2) + 1); 
        break;
    case 3: 
        exitPos = Position(WIDTH - 2, rand() % (HEIGHT - 2) + 1); 
        break;
    }
    maze[exitPos.y][exitPos.x] = END;

    // Add items (you can adjust frequencies as you like)
    for (int i = 0; i < WIDTH * HEIGHT / 50; ++i) {
        int x, y;
        do {
            x = rand() % WIDTH;
            y = rand() % HEIGHT;
        } while (maze[y][x] != EMPTY);
        switch (rand() % 4) {
        case 0: maze[y][x] = GOGGLES; break;
        case 1: maze[y][x] = SPEED_POTION; break;
        case 2: maze[y][x] = FOG; break;
        case 3: maze[y][x] = SLOW_POTION; break;
        }
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

