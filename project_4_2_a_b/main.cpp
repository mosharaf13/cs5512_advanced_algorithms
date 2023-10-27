#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

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

// Function to perform Depth-First Search
bool depthFirstSearch(int graph[size][size], int currentVertex, int targetVertex, bool visited[size], std::vector<int>& path) {
    if (currentVertex == targetVertex) {
        path.push_back(currentVertex);
        return true;
    }

    visited[currentVertex] = true;

    for (int i = 0; i < size; ++i) {
        if (graph[currentVertex][i] == 1 && !visited[i]) {
            if (depthFirstSearch(graph, i, targetVertex, visited, path)) {
                path.push_back(currentVertex);  // Append the current vertex only after the target is found
                return true;
            }
        }
    }

    return false;
}


int main() {
    int graph[size][size];
    bool visited[size] = {false};

    generateRandomGraph(graph);

    int startVertex = 0;
    int targetVertex = 8;

    std::vector<int> path;
    path.reserve(size);

    std::cout << "Starting DFS from vertex " << startVertex << " to find vertex " << targetVertex << std::endl;

    if (depthFirstSearch(graph, startVertex, targetVertex, visited, path)) {
        std::cout << "Vertex " << targetVertex << " found in the graph." << std::endl;
        std::cout << "Path from vertex " << startVertex << " to vertex " << targetVertex << ": ";
        for (int i = path.size() - 1; i >= 0; --i) {
            std::cout << path[i];
            if (i > 0) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;

        // Calculate and display the length of the path
        int pathLength = path.size();
        std::cout << "Length of the path: " << pathLength << std::endl;
    } else {
        std::cout << "Vertex " << targetVertex << " not found in the graph." << std::endl;
    }

    return 0;
}
