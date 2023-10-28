#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int arraySize = 10;

int main() {
    int adjacencyMatrix[arraySize][arraySize] = {
            {-1, 3, -1, 9, -1, -1, -1, -1, -1, -1},
            {-1, -1, 6, -1, -1, -1, -1, -1, -1, -1},
            {1, -1, -1, 6, -1, -1, -1, -1, 14, -1},
            {-1, -1, -1, -1, 4, 3, -1, -1, -1, -1},
            {-1, -1, 6, -1, -1, -1, 7, 3, -1, -1},
            {-1, -1, -1, -1, -1, -1, 7, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, 3},
            {-1, -1, -1, -1, -1, -1, -1, -1, 4, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, 6},
            {-1, -1, -1, -1, -1, 8, -1, -1, -1, -1}
    };

    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Visualization");

    // Define positions for the circles (vertices)
    sf::CircleShape circles[arraySize];
    sf::Vector2f positions[arraySize] = {
            {100, 100}, {300, 100}, {500, 100}, {700, 100},
            {100, 300}, {300, 300}, {500, 300}, {700, 300},
            {300, 500}, {700, 500}
    };

    for (int i = 0; i < arraySize; ++i) {
        circles[i].setRadius(20);
        circles[i].setFillColor(sf::Color::Blue);
        circles[i].setPosition(positions[i]);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Draw edges
        for (int i = 0; i < arraySize; ++i) {
            for (int j = 0; j < arraySize; ++j) {
                int weight = adjacencyMatrix[i][j];
                if (weight != -1) {
                    sf::Vertex line[] = {
                            sf::Vertex(circles[i].getPosition() + sf::Vector2f(20, 20)),
                            sf::Vertex(circles[j].getPosition() + sf::Vector2f(20, 20))
                    };
                    window.draw(line, 2, sf::Lines);
                }
            }
        }

        // Draw circles (vertices) and numbers
        for (int i = 0; i < arraySize; ++i) {
            window.draw(circles[i]);

            // Display numbers on nodes
            sf::Text numberText;
            numberText.setString(std::to_string(i + 1));
            numberText.setCharacterSize(20);
            numberText.setFillColor(sf::Color::White);
            numberText.setPosition(circles[i].getPosition() + sf::Vector2f(15, 15));
            window.draw(numberText);
        }

        window.display();
    }

    return 0;
}
