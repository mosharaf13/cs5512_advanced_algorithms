//
// Created by Md Mosharaf Hossan on 10/27/23.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>

const int size = 9;

// Function to generate a random 9x9 array with 30% of cells set to 1
void generateRandomGraph(int graph[size][size]) {
    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (std::rand() % 100 < 30) {
                graph[i][j] = 1;
            } else {
                graph[i][j] = -1;
            }
        }
    }
}

// Function to display the graph
void displayGraph(int graph[size][size]) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (graph[i][j] == 1) {
                std::cout << "o ";  // "o" represents a node (circle)
            } else if (graph[i][j] == -1) {
                std::cout << "- ";  // "-" represents the absence of an edge (line)
            } else {
                std::cout << "  ";  // Blank space
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    int graph[size][size];
    bool visited[size] = {false};

    generateRandomGraph(graph);

    // Display the generated graph
    displayGraph(graph);

    return 0;
}
