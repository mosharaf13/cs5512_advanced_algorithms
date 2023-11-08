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

// Define arrow characters
const char ARROW_UP = '^';
const char ARROW_DOWN = 'v';
const char ARROW_LEFT = '<';
const char ARROW_RIGHT = '>';

struct Cell {
    int x, y;
};

const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};

vector<Cell> path;  // Store the path from 'S' to 'E'

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

bool IsWall(int x, int y) {
    return maze[y][x] == '#';
}

bool CanCarve(int x, int y) {
    return IsValid(x, y) && maze[y][x] == '#';
}

bool FindPath(int x, int y) {
    if (!IsValid(x, y) || !CanCarve(x, y)) {
        return false;
    }

    if (x == MAZE_WIDTH - 2 && y == MAZE_HEIGHT - 2) {
        maze[y][x] = 'E'; // Mark the end cell.
        Cell end_cell;
        end_cell.x = x;
        end_cell.y = y;
        path.push_back(end_cell);  // Record the end cell in the path.
        return true; // Reached the end cell.
    }

    maze[y][x] = ' '; // Mark the path with an empty space.

    // Explore neighboring cells in all directions.
    if (FindPath(x + 1, y) || FindPath(x, y + 1) || FindPath(x - 1, y) || FindPath(x, y - 1)) {
        Cell current_cell;
        current_cell.x = x;
        current_cell.y = y;
        path.push_back(current_cell);  // Record the current cell in the path.
        return true;
    }

    // If no path is found, backtrack.
    maze[y][x] = '#'; // Reset the cell to a wall.
    return false;
}

void GenerateMaze() {
    InitializeMaze();
    maze[1][0] = 'S'; // Mark the start cell.
    maze[MAZE_HEIGHT - 2][MAZE_WIDTH - 1] = 'E'; // Mark the end cell.
    while (!FindPath(1, 1)) {
        // If no path is found, clear the path vector and regenerate the maze.
        path.clear();
        InitializeMaze();
        maze[1][0] = 'S';
        maze[MAZE_HEIGHT - 2][MAZE_WIDTH - 1] = 'E';
    }
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

    // Display the path from 'S' to 'E'
    if (!path.empty()) {
        for (int i = 1; i < path.size() - 1; i++) {
            maze[path[i].y][path[i].x] = 'O'; // 'O' represents the path
        }
        DisplayMaze();
    }

    return 0;
}
