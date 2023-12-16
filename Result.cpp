#pragma "Result.h"


Result::Result(int& c1, int& c2) : counter1(c1), counter(c2) {
        if (!font.loadFromFile("Fonts/arial.ttf")) {
        }
    //C:/Users/areme/CLionProjects/untitled1/Fonts/arial.ttf
        text.setFont(font);
        text.setCharacterSize(48);
        text.setPosition(200, 200);
    }


    void Result::openResultWindow(const std::string& message, const sf::Color& backgroundColor) {
        window.create(sf::VideoMode(800, 600), "RES");
        window.clear(backgroundColor);
        text.setString(message);
        window.draw(text);
        window.display();

        std::this_thread::sleep_for(std::chrono::seconds(2));
        window.close();
    }




    void Result::update() {
        if (counter1 >= 5) {
            sf::Color blue(0, 0, 255);
            openResultWindow("Player 1 Win!", blue);
        }

        if (counter >= 5) {
            sf::Color red(255, 0, 0);
            openResultWindow("Player 2 Win!", red);
        }
    }

    bool Result::isOpen() {
        return window.isOpen();
    }

    void Result::close() {
        window.close();
    }



