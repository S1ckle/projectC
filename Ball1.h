#pragma once
#include "Ball.h"

class Ball1 : public Ball {
private:
    sf::CircleShape ball1;
    sf::Vector2f gravity;
    float gravityStrength;
public:
    Ball1();

    void update(const sf::Vector2f& targetPosition);

    void draw(sf::RenderWindow& window);
};