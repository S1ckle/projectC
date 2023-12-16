#pragma once

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(sf::RenderWindow& window);

    void show();
    bool playButtonPressed() const;

private:
    sf::RenderWindow& window;
    bool isPlayButtonPressed = false;

