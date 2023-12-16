#include "Menu.h"



    bool Menu::showMenu(sf::RenderWindow& window) {
        sf::RectangleShape button(sf::Vector2f(300, 100));
        button.setFillColor(sf::Color::Yellow);
        button.setPosition(250, 250);

        sf::Font font;
        font.loadFromFile("C:/Users/areme/CLionProjects/untitled1/Fonts/arial.ttf");
        //C:/Users/areme/CLionProjects/untitled1/Fonts/arial.ttf
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
