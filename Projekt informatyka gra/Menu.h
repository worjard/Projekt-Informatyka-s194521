#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Menu {
public:
    Menu(RenderWindow& window);
    int run();

private:
    RenderWindow& window;
    bool mysz(const sf::Text& button);
    int init();
    void ustawTlo(const std::string& sciezkaDoObrazka);  
    Texture tloT;
    Sprite tloS;
};
