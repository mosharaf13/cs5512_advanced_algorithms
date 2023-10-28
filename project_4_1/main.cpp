#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int size = 9;
const int nodeRadius = 20;

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

int main() {
    int graph[size][size];
    bool visited[size] = {false};

    generateRandomGraph(graph);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Visualization");

    // Calculate positions for nodes
    sf::Vector2f nodePositions[size];
    for (int i = 0; i < size; ++i) {
        float angle = 2 * 3.14159265 * i / size;
        float x = 400 + 200 * std::cos(angle);
        float y = 300 + 200 * std::sin(angle);
        nodePositions[i] = sf::Vector2f(x, y);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Draw nodes and edges only if they are connected
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (graph[i][j] == 1) {
                    sf::CircleShape node(nodeRadius);
                    node.setFillColor(sf::Color::Blue);
                    node.setPosition(nodePositions[i]);
                    window.draw(node);

                    // Draw edges
                    sf::Vertex line[] = {
                            sf::Vertex(nodePositions[i] + sf::Vector2f(nodeRadius, nodeRadius)),
                            sf::Vertex(nodePositions[j] + sf::Vector2f(nodeRadius, nodeRadius))
                    };
                    window.draw(line, 2, sf::Lines);
                }
            }
        }

        window.display();
    }

    return 0;
}
