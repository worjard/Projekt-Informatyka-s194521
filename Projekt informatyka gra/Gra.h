#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;

class postac {
private:
    Vector2f position;
    Sprite bohater;
    Texture texture;
    int animFrame;
    Clock animClock;
    int col;
    int row;

public:
    postac(float x_in, float y_in);
    void przesun(float x_in, float y_in);
    Vector2f getPosition();
    Sprite getBohater();
    FloatRect getBounds();
    void animujChodzenie(int kierunek);
};

class Gra {
public:
    Gra();
    void run();
    void update();
    void init();
    RenderWindow& getWindow();


private:
    postac p1;
    postac p2;
    RenderWindow window;
    int dx;
    int dy;
    View view;
    Texture backgroundTextures[6];
    Sprite backgroundSprites[6];
    Clock zegar;
    Vector2f pozycja;
};
