#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
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
    Vector2f getPosition() { return position; }
    Sprite getBohater() { return bohater; }
    FloatRect getBounds() { return bohater.getGlobalBounds(); }
    void animujChodzenie(int kierunek);
};

postac::postac(float x_in, float y_in)
{
    position.x = x_in;
    position.y = y_in;
    texture.loadFromFile("C:\\Users\\worjard\\Documents\\projektinformatykagra\\NPC.png");
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

int main()
{
    RenderWindow window(VideoMode(1920, 1080), "Lawa");
    int dx = 10, dy = 10;
    View view;
    Texture backgroundTextures[6];
    Sprite backgroundSprites[6];
    Clock zegar;
    Vector2f pozycja;
    for (int i = 0; i < 6; i++) {
        if (!backgroundTextures[i].loadFromFile("C:\\Users\\worjard\\Documents\\projektinformatykagra\\lawa" + to_string(i + 1) + ".png")) {
            cerr << "Błąd ładowania tła " << i + 1 << "!" << endl;
            return 1;
        }

        backgroundSprites[i].setTexture(backgroundTextures[i]);

        if (i < 3) {
            // Umieść obrazy u góry
            backgroundSprites[i].setPosition(i * window.getSize().x, 0);
        }
        else {
            // Umieść obrazy na dole
            backgroundSprites[i].setPosition((i - 3) * window.getSize().x, window.getSize().y);
        }
    }
    postac p1(2000, 600);
    postac p2(1900, 500);
    view.setSize(1920, 1080);
    view.setCenter(p1.getPosition());
    window.setView(view);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    p1.przesun(0, -10);
                    p1.animujChodzenie(2);
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    p1.przesun(0, 10);
                    p1.animujChodzenie(0);
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    p1.przesun(-10, 0);
                    p1.animujChodzenie(3);
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    p1.przesun(10, 0);
                    p1.animujChodzenie(1);
                }

                sf::FloatRect boundingOkta = p2.getBounds();
                if (boundingOkta.intersects(p1.getBounds()))
                {
                    std::cout << "Kolizja!\n";
                }

                pozycja = p1.getPosition();
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
        if (540 >= p1.getPosition().y && 4800 > p1.getPosition().x && p1.getPosition().x > 960) {
            view.setCenter(p1.getPosition().x, 540);
        }
        if (p1.getPosition().y >= 1610 && 4800 > p1.getPosition().x && p1.getPosition().x > 960) {
            view.setCenter(p1.getPosition().x, 1610);
        }
        if (1610 > p1.getPosition().y && p1.getPosition().y > 540 && p1.getPosition().x >= 4800) {
            view.setCenter(4800, p1.getPosition().y);
        }
        if (1610 > p1.getPosition().y && p1.getPosition().y > 540 && 960 >= p1.getPosition().x) {
            view.setCenter(4800, p1.getPosition().y);
        }

        window.setView(view);
        //1610>y>540
        //4800>x>960
        window.clear();
        for (int i = 0; i < 6; i++) {
            window.draw(backgroundSprites[i]);
        }
        window.draw(p1.getBohater());
        window.draw(p2.getBohater());
        window.display();
    }

    return 0;
}
