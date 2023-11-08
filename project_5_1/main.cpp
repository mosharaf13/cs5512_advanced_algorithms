#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

const int MAZE_WIDTH = 20;
const int MAZE_HEIGHT = 10;
char maze[MAZE_HEIGHT][MAZE_WIDTH];

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

struct Cell {
    int x, y;
};

const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};

void InitializeMaze() {
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            maze[y][x] = '#'; // Initialize all cells as walls.
        }
    }
}

bool IsValid(int x, int y) {
    return x >= 0 && x < MAZE_WIDTH && y >= 0 && y < MAZE_HEIGHT;
}

bool IsVisited(int x, int y) {
    return maze[y][x] == ' ';
}

bool IsWall(int x, int y) {
    return maze[y][x] == '#';
}

bool CanCarve(int x, int y) {
    return IsValid(x, y) && !IsVisited(x, y);
}

void CarvePath(int x, int y) {
    maze[y][x] = ' ';

    // Create a random number generator.
    std::random_device rd;
    std::mt19937 gen(rd());

    // Randomize the order in which we explore the directions.
    vector<Direction> directions;
    directions.push_back(UP);
    directions.push_back(DOWN);
    directions.push_back(LEFT);
    directions.push_back(RIGHT);
    std::shuffle(directions.begin(), directions.end(), gen);

    for (Direction dir : directions) {
        int nx = x + dx[dir] * 2;
        int ny = y + dy[dir] * 2;

        if (CanCarve(nx, ny)) {
            maze[y + dy[dir]][x + dx[dir]] = ' ';
            CarvePath(nx, ny);
        }
    }
}

void GenerateMaze() {
    InitializeMaze();

    // Start generating the maze from a random position.
    int startX = 1;
    int startY = 1;

    CarvePath(startX, startY);
}

void DisplayMaze() {
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            cout << maze[y][x];
        }
        cout << endl;
    }
}

int main() {
    GenerateMaze();
    DisplayMaze();

    return 0;
}
