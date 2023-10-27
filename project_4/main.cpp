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

// Function to perform Depth-First Search
bool depthFirstSearch(int graph[size][size], int currentVertex, int targetVertex, bool visited[size], std::vector<int>& path) {
    if (currentVertex == targetVertex) {
        path.push_back(currentVertex);
        return true;
    }

    visited[currentVertex] = true;

    for (int i = 0; i < size; ++i) {
        if (graph[currentVertex][i] == 1 && !visited[i]) {
            path.push_back(currentVertex);
            if (depthFirstSearch(graph, i, targetVertex, visited, path)) {
                return true;
            }
        }
    }

    return false;
}

// Function to perform Breadth-First Search
bool breadthFirstSearch(int graph[size][size], int startVertex, int targetVertex) {
    bool visited[size] = {false};
    std::queue<int> bfsQueue;

    visited[startVertex] = true;
    bfsQueue.push(startVertex);

    while (!bfsQueue.empty()) {
        int currentVertex = bfsQueue.front();
        bfsQueue.pop();

        if (currentVertex == targetVertex) {
            std::cout << "Vertex " << targetVertex << " found." << std::endl;
            return true;
        }

        for (int i = 0; i < size; ++i) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                bfsQueue.push(i);
            }
        }
    }

    std::cout << "Vertex " << targetVertex << " not found." << std::endl;
    return false;
}

int main() {
    int graph[size][size];
    bool visited[size] = {false};

    generateRandomGraph(graph);

    // Display the generated graph
    displayGraph(graph);

    int startVertex = 0;
    int targetVertex = 8;

    std::vector<int> path;
    path.reserve(size);

    std::cout << "Starting DFS from vertex " << startVertex << " to find vertex " << targetVertex << std::endl;

    if (depthFirstSearch(graph, startVertex, targetVertex, visited, path)) {
        std::cout << "Vertex " << targetVertex << " found in the graph." << std::endl;
        std::cout << "Path from vertex " << startVertex << " to vertex " << targetVertex << ": ";
        for (int vertex : path) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Vertex " << targetVertex << " not found in the graph." << std::endl;
    }

    return 0;
}
