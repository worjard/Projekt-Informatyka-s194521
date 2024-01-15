#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include "gra.h"
#include <string>

using namespace sf;

class Menu {
public:
    Menu(RenderWindow& window);
    void run();
    string getNickname();
    int wybierzpostac();
private:
    void wyswietlWynikiTabelka();
    Text Tytu³, przyciskGraj, przyciskWyniki, przyciskOpcje, przyciskWyjscie, przyciskWroc, przyciskG³os, przyciskG³os2, przyciskzmniejsz, przyciskzmniejsz2, przyciskzwieksz, przyciskzwieksz2, przyciskZatwierdz;
    static int g³oœnoœæmenu;
    Music muzyczkamenu;
    RenderWindow& window;
    bool mysz(const sf::Text& button);
    bool mysz2(const sf::RectangleShape& button);
    void init();
    void ustawTlo(const std::string& sciezkaDoObrazka);  
    Texture tloT;
    Sprite tloS;
    bool enteringNickname;
    bool mainmenu;
    bool wynikiWidoczne;
    bool opcjeWidoczne;
};
