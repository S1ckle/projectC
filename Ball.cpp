#include "Ball.h"


Ball::Ball() {
    ball.setRadius(10);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(395, 295);
    velocity = sf::Vector2f(0.2, 0.2);
}

sf::Vector2f Ball::getPosition() const {
    return ball.getPosition();
}

void Ball::move() {
    ball.move(velocity);
}

void Ball::speedLimit() {
    if (velocity.x + velocity.y > 0.8) {
        velocity.x = 0.2;
        velocity.y = 0.2;
    }
    if (velocity.y > 0.4) {
        velocity.y -= 0.2;
        velocity.x += 0.2;
    }
}

void Ball::reset() {
    ball.setPosition(395, 295);

    float randomX = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.2f)) - 0.05f;
    float randomY = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.2f)) - 0.05f;
    velocity=(sf::Vector2f(randomX, randomY));
}

void Ball::handleCollision(sf::RenderWindow& window, sf::RectangleShape& player, sf::RectangleShape& player1,
                           sf::RectangleShape& gates, sf::RectangleShape& gates2, int& counter, int& counter1, float& platformSpeed) {
    if (ball.getPosition().x <= 0 || ball.getPosition().x >= 790)
        velocity.x = -velocity.x;
    if (ball.getPosition().y <= 0 || ball.getPosition().y >= 590)
        velocity.y = -velocity.y;

    if (ball.getGlobalBounds().intersects(player.getGlobalBounds())) {
        velocity.x = -velocity.x;

        if (platformSpeed != 0.0) {
            velocity.y += 0.2 * platformSpeed;
        }
    }

    if (ball.getGlobalBounds().intersects(player1.getGlobalBounds())) {
        velocity.x = -velocity.x;

        if (platformSpeed != 0.0) {
            velocity.y += 0.02 * platformSpeed;
        }
    }

    if (ball.getGlobalBounds().intersects(gates.getGlobalBounds())) {
        counter += 1;
        sf::RectangleShape whiteBackground(sf::Vector2f(800, 600));
        whiteBackground.setFillColor(sf::Color::White);
        window.draw(whiteBackground);
        window.display();
        sf::sleep(sf::seconds(0.5));
        ball.setPosition(395, 295);
        velocity.x = -velocity.x;
        velocity.y = -velocity.y;
    }

    if (ball.getGlobalBounds().intersects(gates2.getGlobalBounds())) {
        counter1 += 1;
        sf::RectangleShape whiteBackground(sf::Vector2f(800, 600));
        whiteBackground.setFillColor(sf::Color::White);
        window.draw(whiteBackground);
        window.display();
        sf::sleep(sf::seconds(0.5));
        ball.setPosition(395, 295);
        velocity.x = -velocity.x;
        velocity.y = -velocity.y;
    }
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(ball);
}