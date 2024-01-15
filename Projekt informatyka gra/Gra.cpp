#include "Gra.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp >
#include <random>
#include <vector>


using namespace std;
using namespace sf;

int Gra::g³oœnoœægra = 50;
string Gra::nick;
wrog::wrog(float x_in, float y_in) : liczbaTrafien(0) {
    position.x = x_in;
    position.y = y_in;
    chodzenie.loadFromFile("chodzenie.png");
    œmieræ.loadFromFile("œmieræ.png");
    bohater.setTexture(chodzenie);
    bohater.setTextureRect(IntRect(0, 0, 73, 110));
    bohater.setPosition(position);
    animFrame = 2;
    animClock.restart();
    col = 0;
    row = 2;
    umiera = 0;
}

postac::postac(float x_in, float y_in) {
    position.x = x_in;
    position.y = y_in;
    chodzenie.loadFromFile("wojownik1.png");
    bohater.setTexture(chodzenie);
    bohater.setTextureRect(IntRect(0, 0, 66, 110));
    bohater.setPosition(position);
    animFrame = 2;
    animClock.restart();
    col = 0;
    row = 0;

}
bool wrog::czyZniszczony() const {
    return liczbaTrafien >= 2;  // Zniszcz wroga, jeœli zosta³ trafiony dwukrotnie
}
postac::postac() : animFrame(0), col(0), row(0) {

}


void postac::przesun(float x_in, float y_in)
{
    if (position.x + x_in >= 0 && position.x + x_in <= 5710) {
        position.x += x_in;
    }

    if (position.y + y_in >= 0 && position.y + y_in <= 2100) {
        position.y += y_in;
    }
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
    if (animClock.getElapsedTime().asMilliseconds() > 100.0f) {
        row = kierunek;
        bohater.setTextureRect(IntRect(col * 66, row * 110, 66, 110));
        col++;
        if (col >= 8) {
            col = 0;
        }
        animClock.restart();
    }
}

bool wrog::animuj(String& akcja)
{
    if (akcja == "œmieræ") {
        bohater.setTexture(œmieræ);
        if (animClock.getElapsedTime().asMilliseconds() > 100.0f) {
            bohater.setTextureRect(IntRect(col * 113, 0, 113, 110));
            col++;
            if (col > 15) {
                return true;
                col = 0;
            }
            animClock.restart();
        }
    }
  
    else if (akcja == "chodzenie") {
        bohater.setTexture(chodzenie);
        if (animClock.getElapsedTime().asMilliseconds() > 100.0f) {
            bohater.setTextureRect(IntRect(col * 73, 0, 73, 110));
            col++;
            if (col >= 13) {
                col = 0;
            }
            animClock.restart();
        }
    }
}
Kula::Kula(float x, float y, float dx, float dy) : position(x, y), velocity(dx, dy), trafiona(false) {
    fireball.loadFromFile("fire-ball.png");
    pocisk.setTexture(fireball);
    pocisk.setTextureRect(IntRect(0, 0, 60, 58));
}

void Kula::przesun() {
    position += velocity; // Przesuñ kulê na podstawie jej prêdkoœci
    pocisk.setPosition(position); // Ustaw now¹ pozycjê kuli
}

FloatRect Kula::getBounds(){
    return pocisk.getGlobalBounds(); // Pobierz prostok¹t kolizji kuli
}
bool Kula::czyTrafi³a() const {
    return trafiona;
}

void Kula::oznacz¿etrafi³a() {
    trafiona = true;
}

Gra::Gra() : p1(2000, 600), window(VideoMode(1920, 1080), "Lawa")
{
    view.setSize(1920, 1080);
    view.setCenter(p1.getPosition());
    window.setView(view);
    dx = 0;
    dy = 0;
}

void Gra::init()
{ 

    Tak.setFont(arial);
    Tak.setString("Tak");
    Tak.setCharacterSize(32);
    Tak.setFillColor(Color::White);
    Nie.setFont(arial);
    Nie.setString("Nie");
    Nie.setCharacterSize(32);
    Nie.setFillColor(Color::White);
    pomoc.loadFromFile("help.jpg");
    prostokatPomocy.setTexture(pomoc);
    prostokatPomocy.setTextureRect(IntRect(0, 0, 1000, 900));
          
    end.loadFromFile("end.jpg");
    przegryw.setTexture(end);
    przegryw.setTextureRect(IntRect(0, 0, 1000, 966));

    wyjscie.loadFromFile("wyjscie.jpg");
    exit.setTexture(wyjscie);
    exit.setTextureRect(IntRect(0, 0, 369, 128));

    lvlup.loadFromFile("lvlup.jpg");
    lvl.setTexture(wyjscie);
    lvl.setTextureRect(IntRect(0, 0, 634, 853));

    for (int i = 0; i < 6; i++) {
        if (!backgroundTextures[i].loadFromFile("lawa" + to_string(i + 1) + ".png")) {
            cerr << "B³¹d ³adowania t³a " << i + 1 << "!" << endl;
            return;
        }
        backgroundSprites[i].setTexture(backgroundTextures[i]);
        if (i < 3) {
            backgroundSprites[i].setPosition(i * window.getSize().x, 0.0f);
        }
        else {
            backgroundSprites[i].setPosition((i - 3) * window.getSize().x, window.getSize().y);
        }
    }

    if (!muzyczka.openFromFile("Muzyczka.ogg")) {
           cerr << "B³¹d ³adowania pliku dŸwiêkowego!" << std::endl;
           return;
    }
    if (!hit.openFromFile("hit.ogg")) {
        cerr << "B³¹d ³adowania pliku dŸwiêkowego!" << std::endl;
        return;
    }
    muzyczka.setLoop(true);
    muzyczka.setVolume(g³oœnoœægra);
    hit.setLoop(false);
    hit.setVolume(g³oœnoœægra);
}
void Gra::dodajwroga() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> x(0, 2100);
    uniform_int_distribution<int> y(0, 5710);
    wrogowie.push_back(new wrog(x(gen), y(gen)));
}
void Gra::kolizjeKulaWrog() {
    for (auto& w : wrogowie) {
        for (auto& kula : kule) {
            FloatRect boundingWrog = w->getBounds();
            FloatRect boundingKula = kula->getBounds();

            if (boundingWrog.intersects(boundingKula) && !kula->czyTrafi³a()) {
                w->liczbaTrafien++;  // Zwiêksz liczbê trafieñ wroga
                kula->oznacz¿etrafi³a();
            }
        }
    }
}
void Gra::updateWrogowie() {
    for (auto& w1 : wrogowie) {
        for (auto& w2 : wrogowie) {
            if (w1 != w2 && !w1->czyZniszczony() && !w2->czyZniszczony()) {
                FloatRect boundingW1 = w1->getBounds();
                FloatRect boundingW2 = w2->getBounds();
                if (boundingW1.intersects(boundingW2)) {
                    Vector2f collisionVector = w1->getPosition() - w2->getPosition();
                    float length = sqrt(collisionVector.x * collisionVector.x + collisionVector.y * collisionVector.y);
                    collisionVector /= length;
                    w1->przesun(collisionVector.x * 5, collisionVector.y * 5);
                    w2->przesun(-collisionVector.x * 5, -collisionVector.y * 5);
                }
            }
        }
    }
}
void Gra::usunZniszczoneWrogi() {
    wrogowie.erase(remove_if(wrogowie.begin(), wrogowie.end(), [this](wrog* w) {
        String smierc = "œmieræ";
        bool czyZniszczony = w->czyZniszczony();
        if (czyZniszczony) {
            w->umiera = 1;
          if(  w->animuj(smierc)== true){
                this->kill++;
                this->hit.play();
                delete w;
                return true;
          }
        }
        return false;
        }), wrogowie.end());
    wrogowie.shrink_to_fit();
}
void Gra::usunZnioszczoneKule() {
    kule.erase(std::remove_if(kule.begin(), kule.end(), [this](Kula* kula) {
        return kula->czyTrafi³a();
        }), kule.end());
    kule.shrink_to_fit();
}
void Gra::levelup(){
    if (kill >= exp) {
        lv++;
        exp = 2 * exp + 2;
        window.draw(lvl);
        window.display();
    }
}

void Gra::zapiszWynikiDoPliku() {
    ofstream plik("wyniki.txt", ios::app);

    if (plik.is_open()) {
        plik << Gra::nick << "\t";
        plik << kill << "\t";
        plik << lv << "\n\n";
        plik.close();
        cout << "Wyniki zapisano do pliku wyniki.txt\n";
    }
    else {
        cerr << "B³¹d otwarcia pliku wyniki.txt!\n";
    }
}
void Gra::update()
{
    kolizjeKulaWrog();
    usunZniszczoneWrogi();
    usunZnioszczoneKule();
    updateWrogowie();
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            zapiszWynikiDoPliku();
            window.close();
        }
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            if (mysz(Tak)) {
                zapiszWynikiDoPliku();
                window.close();
                muzyczka.stop();
            }
            else if (mysz(Nie)) {
                wyj = -wyj;
            }
        }
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::F1) {
                pauza = -pauza;
                cout << "wcisnieto f1\n";
            }
            if (event.key.code == Keyboard::Escape) {
                wyj = -wyj;
                cout << "wcisnieto esc\n";
            }
        }
        if (pauza == 1 && wyj == 1 && endd == 0) {
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::W) {
                    p1.animujChodzenie(1);
                }
                else if (event.key.code == Keyboard::A) {
                    p1.animujChodzenie(3);
                }
                else if (event.key.code == Keyboard::S) {
                    p1.animujChodzenie(0);
                }
                else if (event.key.code == Keyboard::D) {
                    p1.animujChodzenie(2);
                }
                if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A)) {
                    p1.przesun(-10, -10);
                }
                else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) {
                    p1.przesun(10, -10);
                }
                else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A)) {
                    p1.przesun(-10, 10);
                }
                else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) {
                    p1.przesun(10, 10);
                }
                else {
                    if (event.key.code == Keyboard::W) {
                        p1.przesun(0, -10);
                    }
                    else if (event.key.code == Keyboard::A) {
                        p1.przesun(-10, 0);
                    }
                    else if (event.key.code == Keyboard::S) {
                        p1.przesun(0, 10);
                    }
                    else if (event.key.code == Keyboard::D) {
                        p1.przesun(10, 0);
                    }
                }
                prostokatPomocy.setPosition(view.getCenter().x - 500, view.getCenter().y - 450);
                przegryw.setPosition(view.getCenter().x - 500, view.getCenter().y - 475);
                lvl.setPosition(view.getCenter().x - 500, view.getCenter().y - 450);
                exit.setPosition(view.getCenter().x - 150, view.getCenter().y - 175);
                Tak.setPosition(view.getCenter().x - 78, view.getCenter().y - 95);
                Nie.setPosition(view.getCenter().x + 95, view.getCenter().y - 95);
                sf::Vector2f pozycja = p1.getPosition();
                cout << "p1.x= " << pozycja.x << " p1.y= " << pozycja.y << "\n";
            }
            //dodaje wroga
            if (zegarwroga.getElapsedTime().asMilliseconds() > resp) {
                dodajwroga();
                resp = resp / 1.01;
                zegarwroga.restart();
            }
        }
    }

    if (pauza == 1 && wyj == 1 && endd == 0) {
                // Ruch wrogów
                for (auto& w : wrogowie) {
                    if (w->umiera == 0) {
                        String chodzenie = "chodzenie";
                        if (w->zegar.getElapsedTime().asMilliseconds() > 50.0f) {
                            if (w->getPosition().x > p1.getPosition().x) {
                                w->dx = -2;
                                w->animuj(chodzenie);
                            }
                            else {
                                w->dx = 2;
                                w->animuj(chodzenie);
                            }
                            if (w->getPosition().y > p1.getPosition().y) {
                                w->dy = -2;
                                w->animuj(chodzenie);
                            }
                            else {
                                w->dy = 2;
                                w->animuj(chodzenie);
                            }
                            w->przesun(w->dx, w->dy);
                            w->zegar.restart();
                        }
                    }
                }
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    // Pobierz pozycjê myszy wzglêdem widoku (view)
                    if (kulet.getElapsedTime().asMilliseconds() > 20.0f) {
                    Vector2i mousePosition = Mouse::getPosition(window);
                    Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition, view);

                    // Pobierz pozycjê gracza
                    Vector2f playerPosition = p1.getPosition();

                    // Oblicz wektor kierunku dla kuli
                    Vector2f direction = worldMousePosition - playerPosition;

                    // Znormalizuj wektor kierunku, aby uzyskaæ jednostkowy wektor
                    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                    direction /= length;

                    // Dodaj now¹ kulê do kontenera kule
                    kule.push_back(new Kula(playerPosition.x, playerPosition.y, direction.x * 5, direction.y * 5));

                    }
                    kulet.restart();
                }
    }
        // Kolizje
        for (auto& w : wrogowie) {
            FloatRect boundingP1 = p1.getBounds();
            FloatRect boundingP2 = w->getBounds();
            if (boundingP1.intersects(boundingP2)) {
                if (zegarkolizji.getElapsedTime().asMilliseconds() > 20.0f) {
                cout << "Kolizja!\n";
                hp=hp-30;
                hit.play();
                }
                zegarkolizji.restart();
            }

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
        if (0 >= hp) {
            hp = 0;
            endd = 1;          
        }
        levelup();

    window.setView(view);
    info.Hp = hp;
    info.Kill = kill;
    info.Level = lv;

    for (auto& kula : kule) {
        kula->przesun();
    }
}
void Gra::rysujinterfejs() {
    if (!arial.loadFromFile("arial.ttf")) {
        cerr << "B³¹d ³adowania czcionki!" << endl;
        return;
    }
    Text inter;
    inter.setFont(arial);
    inter.setString("HP: " + to_string(info.Hp) +
        " | Zabojstwa: " + to_string(info.Kill) +
        " | Level: " + to_string(info.Level) + "| Nick: " + Gra::nick);
    inter.setCharacterSize(48);
    inter.setFillColor(Color::White);
    inter.setPosition(view.getCenter().x - 950, view.getCenter().y - 530);
    window.draw(inter);
}
void Gra::run()
{
    init();

    muzyczka.play();
    while (window.isOpen()) {
        
        update();

        window.clear();
        for (int i = 0; i < 6; i++) {
            window.draw(backgroundSprites[i]);
        }
        for (auto& kula : kule) {
            window.draw(kula->pocisk);
        }
        window.draw(p1.getBohater());
        for (auto& w : wrogowie) {
         window.draw(w->getBohater());
        }
        rysujinterfejs();
        if (pauza == -1) {
            window.draw(prostokatPomocy);
            muzyczka.stop();
        }
        if (endd == 1) {
            window.draw(przegryw);
            window.display();
            sleep(seconds(10));
            zapiszWynikiDoPliku();
            window.close();
            muzyczka.stop();
        }
        if (wyj == -1) {
            window.draw(exit);
            window.draw(Tak);
            window.draw(Nie);
        }
        window.display();
    }
    muzyczka.stop();
}
RenderWindow& Gra::getWindow()
{
    return window;
}

bool Gra::mysz(const Text& button) {
    Vector2i mousePosition = Mouse::getPosition(window);
    FloatRect buttonBounds = button.getGlobalBounds();
    // Przeliczenie wspó³rzêdnych myszy na wspó³rzêdne wzglêdem centrum widoku
    Vector2f viewCenter = view.getCenter();
    mousePosition.x += static_cast<int>(viewCenter.x - window.getSize().x / 2);
    mousePosition.y += static_cast<int>(viewCenter.y - window.getSize().y / 2);

    return buttonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}