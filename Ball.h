#pragma once
#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::Vector2f velocity;
public:
    sf::CircleShape ball;

    Ball();

    sf::Vector2f getPosition() const;

    void move();

    void speedLimit();

    void reset();

    void handleCollision(sf::RenderWindow& window, sf::RectangleShape& player, sf::RectangleShape& player1, sf::RectangleShape& gates, sf::RectangleShape& gates2, int& counter, int& counter1, float& platformSpeed);

    void draw(sf::RenderWindow& window);
};
