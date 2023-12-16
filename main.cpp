#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <chrono>
#include <thread>
float platformSpeed = 0.0;


class Menu {
public:
    bool showMenu(sf::RenderWindow& window) {
        sf::RectangleShape button(sf::Vector2f(300, 100));
        button.setFillColor(sf::Color::Yellow);
        button.setPosition(250, 250);

        sf::Font font;
        font.loadFromFile("C:/Fonts/arial.ttf");
        sf::Text text("Start Game", font, 40);
        text.setFillColor(sf::Color::Red);
        text.setPosition(300, 275);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (button.getGlobalBounds().contains(mousePos)) {
                        return true;
                    }
                }
            }

            window.clear();
            window.draw(text);
            window.draw(button);
            window.draw(text);
            window.display();
        }

        return false;
    }
};


class Result {
private:
    int& counter1;
    int& counter;
    sf::RenderWindow window;
    sf::Text text;
    sf::Font font;

public:
    Result(int& c1, int& c2) : counter1(c1), counter(c2) {
        if (!font.loadFromFile("Fonts/arial.ttf")) {
        }
        text.setFont(font);
        text.setCharacterSize(48);
        text.setPosition(200, 200);
    }


    void openResultWindow(const std::string& message, const sf::Color& backgroundColor) {
        window.create(sf::VideoMode(800, 600), "RES");
        window.clear(backgroundColor);
        text.setString(message);
        window.draw(text);
        window.display();

        std::this_thread::sleep_for(std::chrono::seconds(2));
        window.close();
    }




    void update() {
        if (counter1 >= 5) {
            sf::Color blue(0, 0, 255);
            openResultWindow("Player 1 Win!", blue);
        }

        if (counter >= 5) {
            sf::Color red(255, 0, 0);
            openResultWindow("Player 2 Win!", red);
        }
    }

    bool isOpen() {
        return window.isOpen();
    }

    void close() {
        window.close();
    }
};

class Ball {
private:
    //sf::CircleShape ball;
    sf::Vector2f velocity;

public:

    sf::CircleShape ball;

    Ball() {
        ball.setRadius(10);
        ball.setFillColor(sf::Color::White);
        ball.setPosition(395, 295);
        velocity = sf::Vector2f(0.2, 0.2);
    }

    sf::Vector2f getPosition() const {
        return ball.getPosition();
    }

    void move() {
        ball.move(velocity);
    }
    void speedLimit() {
        if (velocity.x + velocity.y > 0.8) {velocity.x = 0.2; velocity.y = 0.2;}
        if (velocity.y > 0.4) {velocity.y -= 0.2; velocity.x += 0.2;}
    }

    void reset() {
        ball.setPosition(395, 295);

        float randomX = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.2f)) - 0.05f;
        float randomY = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.2f)) - 0.05f;
        velocity=(sf::Vector2f(randomX, randomY));
    }

    void handleCollision(sf::RenderWindow& window, sf::RectangleShape& player, sf::RectangleShape& player1, sf::RectangleShape& gates, sf::RectangleShape& gates2, int& counter, int& counter1) {
        if (ball.getPosition().x <= 0 || ball.getPosition().x >= 790)
            velocity.x = -velocity.x;
        if (ball.getPosition().y <= 0 || ball.getPosition().y >= 590)
            velocity.y = -velocity.y;

        if (ball.getGlobalBounds().intersects(player.getGlobalBounds()))
        {
            velocity.x = -velocity.x;

            if (platformSpeed != 0.0)
            {
                velocity.y += 0.2*platformSpeed;
            }
        }



        if (ball.getGlobalBounds().intersects(player1.getGlobalBounds()))
        {
            velocity.x = -velocity.x;

            if (platformSpeed != 0.0)
            {
                velocity.y += 0.02*platformSpeed;
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

    void draw(sf::RenderWindow& window) {
        window.draw(ball);
    }
};


class Ball1 : public Ball {
private:
    sf::CircleShape ball1;
    sf::Vector2f gravity;
    float gravityStrength;
public:
    Ball1() {
        ball1.setRadius(4);
        ball1.setFillColor(sf::Color::Red);
        ball1.setPosition(400, 300);
        // gravity = sf::Vector2f(0, 0);
        gravityStrength = 1;
    }
    void update(const sf::Vector2f& targetPosition) {
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

    void draw(sf::RenderWindow& window) {
        window.draw(ball1);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

    Menu menu;
    if (menu.showMenu(window)) {
        window.close();
        sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
        int counter = 0;
        int counter1 = 0;
        int i = 4;




        sf::Texture texture;
        if (!texture.loadFromFile("Fonts/56.PNG")) {
// Обработка ошибки загрузки текстуры
        }
        sf::Sprite sprite(texture);
        sprite.setPosition(0, 0);


        // Поле
        sf::RectangleShape field(sf::Vector2f(800, 600));
       // field.setFillColor(sf::Color::Black);
        field.setTexture(&texture);

        sf::RectangleShape count[6];
        for (int i = 0; i < 6; i++) {
            count[i] = sf::RectangleShape(sf::Vector2f(5, 20));
            count[i].setFillColor(sf::Color::Red);
            count[i].setPosition(10 + (i * 10), 20);
        }

        sf::RectangleShape count1[6];
        for (int i = 0; i < 6; i++) {
            count1[i] = sf::RectangleShape(sf::Vector2f(5, 20));
            count1[i].setFillColor(sf::Color::Red);
            count1[i].setPosition(785 - (i * 10), 20);
        }

        sf::RectangleShape gates(sf::Vector2f(10, 300));
        gates.setFillColor(sf::Color::White);
        gates.setPosition(5, 140);

        sf::RectangleShape gates2(sf::Vector2f(10, 300));
        gates2.setFillColor(sf::Color::White);
        gates2.setPosition(790, 140);

        sf::RectangleShape player(sf::Vector2f(5, 100));
        player.setFillColor(sf::Color::Green);
        player.setPosition(735, 240);

        sf::RectangleShape player1(sf::Vector2f(5, 100));
        player1.setFillColor(sf::Color::Red);
        player1.setPosition(50, 240);

        Ball ball;
        Ball1 ball1;
        // sf::Vector2f position = ball.getPosition();

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player1.getPosition().y > 10)
            {
                platformSpeed = -0.2;
                player1.move(0, platformSpeed);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player1.getPosition().y + player1.getSize().y < 590)
            {
                platformSpeed = 0.2;
                player1.move(0, platformSpeed);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.getPosition().y > 10)
            {
                platformSpeed = -0.2;
                player.move(0, platformSpeed);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.getPosition().y + player.getSize().y < 590)
            {
                platformSpeed = 0.2;
                player.move(0, platformSpeed);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) )
            {
                ball.reset();

            }


            ball.move();
            ball.speedLimit();
            ball.handleCollision(window, player, player1, gates, gates2, counter, counter1);

            ball1.update(ball.getPosition());
            window.clear();

            window.draw(field);
            window.draw(gates);
            window.draw(gates2);
            window.draw(player);
            window.draw(player1);
            ball1.draw(window);
            ball.draw(window);

            Result result(counter1, counter);
            result.update();

             if ( counter == 5 or counter1 == 5 ) {std::this_thread::sleep_for(std::chrono::seconds(2)); window.close();}
            for (int i = 0; i < counter; i++) {
                window.draw(count[i]);
            }
            for (int i = 0; i < counter1; i++) {
                window.draw(count1[i]);
            }

            window.display();
        }

    }

    return 0;
}