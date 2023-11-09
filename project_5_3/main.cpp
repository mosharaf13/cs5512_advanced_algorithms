#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

using namespace std;

const int MAZE_WIDTH = 20;
const int MAZE_HEIGHT = 10;
char maze[MAZE_HEIGHT][MAZE_WIDTH];

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

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

void CarvePath(int x1, int y1, int x2, int y2) {
    while (x1 != x2 || y1 != y2) {
        maze[y1][x1] = ' ';
        vector<int> directions;
        directions.push_back(UP);
        directions.push_back(DOWN);
        directions.push_back(LEFT);
        directions.push_back(RIGHT);
        shuffle(directions.begin(), directions.end(), default_random_engine(time(0)));

        bool carved = false;
        for (int direction : directions) {
            int x_new = x1 + dx[direction];
            int y_new = y1 + dy[direction];
            if (IsValid(x_new, y_new) && IsWall(x_new, y_new)) {
                maze[y_new][x_new] = ' ';
                x1 = x_new;
                y1 = y_new;
                carved = true;
                break;
            }
        }

        // If no valid direction is found, break out of the loop
        if (!carved) {
            break;
        }
    }
}

void GenerateMaze() {
    InitializeMaze();
    maze[1][0] = 'S'; // Mark the start cell.
    maze[MAZE_HEIGHT - 2][MAZE_WIDTH - 1] = 'E'; // Mark the end cell.

    // Create paths between cells to ensure connectivity
    for (int y = 1; y < MAZE_HEIGHT - 1; y += 2) {
        for (int x = 1; x < MAZE_WIDTH - 1; x += 2) {
            if (IsWall(x, y)) {
                int neighbor_x, neighbor_y;
                do {
                    int direction = rand() % 4;
                    neighbor_x = x + dx[direction];
                    neighbor_y = y + dy[direction];
                } while (IsWall(neighbor_x, neighbor_y));
                CarvePath(x, y, neighbor_x, neighbor_y);
            }
        }
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

    return 0;
}
