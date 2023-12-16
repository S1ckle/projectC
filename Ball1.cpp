#include "Ball1.h"
#include <math.h>
Ball1::Ball1() {
        ball1.setRadius(4);
        ball1.setFillColor(sf::Color::Red);
        ball1.setPosition(400, 300);
        // gravity = sf::Vector2f(0, 0);
        gravityStrength = 1;
    }
    void Ball1::update(const sf::Vector2f& targetPosition) {
        sf::Vector2f ballPos = getPosition();
        sf::Vector2f direction = targetPosition - ballPos;
        float distanceSquared = direction.x * direction.x + direction.y * direction.y;

        if (distanceSquared > 0) {
            float distance = std::sqrt(distanceSquared);
            direction /= distance;

            float gravityMagnitude = gravityStrength; // (distanceSquared);
            sf::Vector2f gravityForce = direction * distance  ; // * gravityMagnitude ;
            gravityForce.x /= 6000;
            gravityForce.y /= 6000;
            if (ball1.getPosition().x <= 0 || ball1.getPosition().x >= 790)
            {ball1.setPosition(targetPosition); gravityForce.x = 0;
            }
            if (ball1.getPosition().y <= 0 || ball1.getPosition().y >= 590)
            {ball1.setPosition(targetPosition); gravityForce.y = 0; }
            ball1.move(gravityForce);
        }

    }
void Ball1::draw(sf::RenderWindow& window){
    window.draw(ball1);
}