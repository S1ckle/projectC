#pragma once
#include <SFML/Graphics.hpp>

class Result {
private:
    int& counter1;
    int& counter;
    sf::RenderWindow window;
    sf::Text text;
    sf::Font font;

public:
    Result(int& c1, int& c2);


    void openResultWindow(const std::string& message, const sf::Color& backgroundColor) ;




    void update();

    bool isOpen() ;

    void close() ;
};



