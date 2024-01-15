#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

class postac {
protected:
    Vector2f position;
    Sprite bohater;
    Texture chodzenie;
    Texture œmieræ;
    int animFrame;
    Clock animClock;
    int col;
    int row;

public:
    postac();
    postac(float x_in, float y_in);
    void przesun(float x_in, float y_in);
    Vector2f getPosition();
    Sprite getBohater();
    FloatRect getBounds();
    void animujChodzenie(int kierunek);
    //void animujwróg(int kierunek);
};

class wrog : public postac {
public:
    wrog(float x_in, float y_in);
    Clock zegar; 
    float dx;     
    float dy;
    bool czyZniszczony() const;
    int liczbaTrafien;
    int umiera;
    bool animuj(String& akcja);
    int i;
};

struct GraczInfo {
    int Hp;
    int Kill;
    int Level;
};

class Kula {
public:
    Kula(float x, float y, float dx, float dy);
    void przesun();
    FloatRect getBounds();
    bool czyTrafi³a() const;
    void oznacz¿etrafi³a();
    Texture fireball;
    Sprite pocisk;

protected:
    bool trafiona;
    Vector2f position;
    Vector2f velocity;


};

class Gra {
public:
    Gra();
    void run();
    void update();
    void init();
    void zapiszWynikiDoPliku();
    RenderWindow& getWindow();
    void dodajwroga();
    void rysujinterfejs();
    Sprite prostokatPomocy;
    Texture pomoc;
    Sprite przegryw;
    Texture end;
    Sprite exit;
    Texture wyjscie;
    Texture lvlup;
    Sprite lvl;
    static int g³oœnoœægra;
    static string nick;


protected:
    void updateWrogowie();
    void levelup();
    void kolizjeKulaWrog();
    void usunZniszczoneWrogi();
    void usunZnioszczoneKule();
    Font arial;
    Text Tak, Nie;
    bool mysz(const Text& button);
    int kill = 0, lv = 1, hp = 100, exp = 10, l =1;
    GraczInfo info;
    postac p1;
    int pauza = 1;
    int wyj = 1;
    int endd = 0;
    float dx, dy;
    double resp = 500.00;
    RenderWindow window;
    Music muzyczka;
    Music hit;
    View view;
    Texture backgroundTextures[6];
    Sprite backgroundSprites[6];
    Clock zegarwroga;
    Clock zegarkolizji;
    Clock koniec;
    Clock kulet;
    Clock czas;
    Vector2f pozycja;
    vector<wrog*> wrogowie;
    vector<Kula*> kule;
};


