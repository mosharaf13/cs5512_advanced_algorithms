#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <vector>

const int size = 9;  // Adjust this based on the size of your graph

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

// Function to perform Breadth-First Search and build the BFS tree
void breadthFirstSearch(int graph[size][size], int startVertex, std::vector<std::vector<int> >& bfsTree) {
    bool visited[size] = {false};
    std::queue<int> bfsQueue;

    visited[startVertex] = true;
    bfsQueue.push(startVertex);

    while (!bfsQueue.empty()) {
        int currentVertex = bfsQueue.front();
        bfsQueue.pop();

        for (int i = 0; i < size; ++i) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                bfsQueue.push(i);
                bfsTree[currentVertex].push_back(i);
            }
        }
    }
}

int main() {
    int graph[size][size];

    generateRandomGraph(graph);

    int startVertex = 0;

    std::vector<std::vector<int> > bfsTree(size);

    std::cout << "Starting BFS from vertex " << startVertex << std::endl;

    breadthFirstSearch(graph, startVertex, bfsTree);

    // Display the BFS tree with node 0 as the root
    std::cout << "BFS tree with node 0 as the root:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << "Node " << i << " -> ";
        for (int child : bfsTree[i]) {
            std::cout << child << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
