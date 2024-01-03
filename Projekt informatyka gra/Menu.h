#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>

using namespace sf;

class Menu {
public:
    Menu(RenderWindow& window);
    void run();

private:
    Music muzyczkamenu;
    RenderWindow& window;
    bool mysz(const sf::Text& button);
    void init();
    void ustawTlo(const std::string& sciezkaDoObrazka);  
    Texture tloT;
    Sprite tloS;
};
