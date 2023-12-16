#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <chrono>
#include <thread>
#include "Ball.h"
#include "Ball.cpp"
#include "Ball1.h"
#include "Ball1.cpp"
#include "Menu.h"
#include "Menu.cpp"
#include "Result.h"
#include "Result.cpp"
float platformSpeed = 0.0;






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
        if (!texture.loadFromFile("C:/Users/areme/CLionProjects/untitled1/Fonts/56.PNG")) {
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
            ball.handleCollision(window, player, player1, gates, gates2, counter, counter1, platformSpeed);

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