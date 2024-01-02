#include "Gra.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


postac::postac(float x_in, float y_in)
{
    position.x = x_in;
    position.y = y_in;
    texture.loadFromFile("NPC.png");
    bohater.setTexture(texture);
    bohater.setTextureRect(IntRect(0, 0, 32, 64));
    bohater.setPosition(position);
    animFrame = 0;
    animClock.restart();
    col = 0;
    row = 0;
}

void postac::przesun(float x_in, float y_in)
{
    position.x += x_in;
    position.y += y_in;
    bohater.setPosition(position);
}

Vector2f postac::getPosition()
{
    return position;
}

Sprite postac::getBohater()
{
    return bohater;
}

FloatRect postac::getBounds()
{
    return bohater.getGlobalBounds();
}

void postac::animujChodzenie(int kierunek)
{
    if (animClock.getElapsedTime().asMilliseconds() > 300.0f) {
        row = kierunek;
        bohater.setTextureRect(sf::IntRect(col * 32, row * 64, 32, 64));
        col++;
        if (col >= 4) {
            col = 0;
        }
        animClock.restart();
    }
}



Gra::Gra() : p1(2000, 600), p2(1900, 500), window(sf::VideoMode(1920, 1080), "Lawa")
{
    view.setSize(1920, 1080);
    view.setCenter(p1.getPosition());
    window.setView(view);
}

void Gra::init()
{
    for (int i = 0; i < 6; i++) {
        if (!backgroundTextures[i].loadFromFile("lawa" + to_string(i + 1) + ".png")) {
            cerr << "B³¹d ³adowania t³a " << i + 1 << "!" << endl;
            return;
        }

        backgroundSprites[i].setTexture(backgroundTextures[i]);

        if (i < 3) {
            backgroundSprites[i].setPosition(i * window.getSize().x, 0);
        }
        else {
            backgroundSprites[i].setPosition((i - 3) * window.getSize().x, window.getSize().y);
        }
    }
}


void Gra::update()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::W) {
                p1.przesun(0, -10);
                p1.animujChodzenie(2);
            }
            if (event.key.code == sf::Keyboard::S) {
                p1.przesun(0, 10);
                p1.animujChodzenie(0);
            }
            if (event.key.code == sf::Keyboard::A) {
                p1.przesun(-10, 0);
                p1.animujChodzenie(3);
            }
            if (event.key.code == sf::Keyboard::D) {
                p1.przesun(10, 0);
                p1.animujChodzenie(1);
            }

            sf::FloatRect boundingOkta = p2.getBounds();
            if (boundingOkta.intersects(p1.getBounds())) {
                std::cout << "Kolizja!\n";
            }

            sf::Vector2f pozycja = p1.getPosition();
            std::cout << "p1.x= " << pozycja.x << " p1.y= " << pozycja.y << "\n";
        }
    }

    if (zegar.getElapsedTime().asMilliseconds() > 50.0f) {
        if (p2.getPosition().x > p1.getPosition().x) {
            dx = -2;
            p2.animujChodzenie(3);
        }
        else {
            dx = 2;
            p2.animujChodzenie(1);
        }
        if (p2.getPosition().y > p1.getPosition().y) {
            dy = -2;
            p2.animujChodzenie(0);
        }
        else {
            dy = 2;
            p2.animujChodzenie(2);
        }
        p2.przesun(dx, dy);
        zegar.restart();
    }

    if (1610 > p1.getPosition().y && p1.getPosition().y > 540 && 4800 > p1.getPosition().x && p1.getPosition().x > 960) {
        view.setCenter(p1.getPosition());
    }
    else if (540 >= p1.getPosition().y && 4800 > p1.getPosition().x && p1.getPosition().x > 960) {
        view.setCenter(p1.getPosition().x, 540);
    }
    else if (p1.getPosition().y >= 1610 && 4800 > p1.getPosition().x && p1.getPosition().x > 960) {
        view.setCenter(p1.getPosition().x, 1610);
    }
    else if (1610 > p1.getPosition().y && p1.getPosition().y > 540 && p1.getPosition().x >= 4800) {
        view.setCenter(4800, p1.getPosition().y);
    }
    else if (1610 > p1.getPosition().y && p1.getPosition().y > 540 && 960 >= p1.getPosition().x) {
        view.setCenter(960, p1.getPosition().y);
    }
    window.setView(view);
}

void Gra::run()
{
    init();

    while (window.isOpen()) {
        update();

        window.clear();
        for (int i = 0; i < 6; i++) {
            window.draw(backgroundSprites[i]);
        }

        window.draw(p1.getBohater());
        window.draw(p2.getBohater());

        window.display();
    }
}
RenderWindow& Gra::getWindow()
{
    return window;
}