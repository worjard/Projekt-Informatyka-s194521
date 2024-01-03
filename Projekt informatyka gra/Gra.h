#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace sf;

class postac {
private:
    Vector2f position;
    Sprite bohater;
    Texture texture;
    Texture wróg;
    int animFrame;
    Clock animClock;
    int col;
    int row;

public:
    postac(float x_in, float y_in, bool isEnemy);
    void przesun(float x_in, float y_in);
    Vector2f getPosition();
    Sprite getBohater();
    FloatRect getBounds();
    void animujChodzenie(int kierunek);
    //void animujwróg(int kierunek);
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
    postac p3;
    postac p4;
    RenderWindow window;
    Music muzyczka;
    Music hit;
    int dx;
    int dy;
    View view;
    Texture backgroundTextures[6];
    Sprite backgroundSprites[6];
    Clock zegar;
    Clock zegar1;
    Clock zegar2;
    Vector2f pozycja;
};
