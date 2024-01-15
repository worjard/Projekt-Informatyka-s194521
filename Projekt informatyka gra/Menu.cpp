#include "menu.h"
#include "Gra.h"
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>

using namespace std;
using namespace sf;

int Menu::g³oœnoœæmenu;

void Menu::ustawTlo(const std::string& sciezkaDoObrazka) {
    if (!tloT.loadFromFile(sciezkaDoObrazka)) {
        cerr << "B³¹d ³adowania obrazka t³a!" << endl;
    }

    tloS.setTexture(tloT);
    tloS.setPosition(0, 0);
    tloS.setScale(window.getSize().x / tloT.getSize().x, window.getSize().y / tloT.getSize().y);
}

Menu::Menu(RenderWindow& window) : window(window) {
    g³oœnoœæmenu = 50;
    ustawTlo("Menu.jpg");
}

string Menu::getNickname() {
    enteringNickname = true;
    Gra::nick = "";

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "B³¹d ³adowania czcionki!" << endl;
        return "";
    }

    Text text;
    text.setFont(font);
    text.setCharacterSize(64);
    text.setFillColor(sf::Color::White);
    text.setString("WPISZ SWOJ NICK:");
    text.setPosition(50, 600);

    wstring input;  // Zmiana na std::wstring
    Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(64);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(730, 600);

    Text przyciskZatwierdz;
    przyciskZatwierdz.setFont(font);
    przyciskZatwierdz.setString("ZATWIERDZ");
    przyciskZatwierdz.setCharacterSize(64);
    przyciskZatwierdz.setFillColor(Color::White);
    przyciskZatwierdz.setPosition(767, 820);

    Event event;
    while (enteringNickname && window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b' && !input.empty()) {
                        input.pop_back();
                    }
                    else if (event.text.unicode != '\b') {
                        input += event.text.unicode;
                    }
                    inputText.setString(wstring(input.begin(), input.end()));
                }
            }
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Enter) {
                    enteringNickname = false;
                    if (!input.empty()) {
                        Gra::nick = string(input.begin(), input.end());
                        return Gra::nick;
                    }
                }
            }
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (mysz(przyciskWroc)) {
                    enteringNickname = false;
                    return "";
                }
                if (mysz(przyciskZatwierdz)) {
                    enteringNickname = false;
                    if (!input.empty()) {
                        Gra::nick = string(input.begin(), input.end());
                        return Gra::nick;
                    }
                }
            }
        }

        window.clear();
        window.draw(tloS);
        window.draw(Tytu³);
        window.draw(text);
        window.draw(inputText);
        window.draw(przyciskWroc);
        window.draw(przyciskZatwierdz);
        window.display();
    }

    return "";
}
void Menu::wyswietlWynikiTabelka() {
    std::ifstream plik("wyniki.txt");

    if (plik.is_open()) {
        // Wczytaj wyniki z pliku i wyœwietl je w formie tabeli
        std::string linia;
        int yPos = 300; // Pocz¹tkowa pozycja Y dla tekstu
        int fontSize = 64; // Rozmiar czcionki

        // Nag³ówki tabeli
        Text naglowek;
        Font font;
        if (font.loadFromFile("arial.ttf")) {
            naglowek.setFont(font);
            naglowek.setCharacterSize(fontSize);
            naglowek.setFillColor(sf::Color::White);
            naglowek.setString("Nick\tKill\tLVL\n\n");
            naglowek.setPosition(500, yPos);
            yPos += fontSize;
            window.draw(naglowek);
        }

        while (std::getline(plik, linia)) {
            Text wynik;
            wynik.setFont(font);
            wynik.setCharacterSize(fontSize);
            wynik.setFillColor(sf::Color::White);
            wynik.setString(linia);
            wynik.setPosition(500, yPos);
            yPos += fontSize;
            window.draw(wynik);
        }

        plik.close();
    }
    else {
        std::cerr << "B³¹d otwarcia pliku wyniki.txt!\n";
    }
}

// Dodaj wywo³anie tej funkcji w odpowiednim miejscu w kodzie

void Menu::init() {
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "B³¹d ³adowania czcionki!" << endl;
        return;
    }
    if (!muzyczkamenu.openFromFile("Muzyczkamenu.ogg")) {
        cerr << "B³¹d ³adowania pliku dŸwiêkowego!" << std::endl;
        return;
    }

    Tytu³.setFont(font);
    Tytu³.setString("LAVA DUNGEON");
    Tytu³.setCharacterSize(154);
    Tytu³.setFillColor(Color::White);
    Tytu³.setPosition(390, 200);

    przyciskGraj.setFont(font);
    przyciskGraj.setString("GRAJ");
    przyciskGraj.setCharacterSize(64);
    przyciskGraj.setFillColor(Color::White);
    przyciskGraj.setPosition(10, 650);

    przyciskWyniki.setFont(font);
    przyciskWyniki.setString("WYNIKI");
    przyciskWyniki.setCharacterSize(64);
    przyciskWyniki.setFillColor(Color::White);
    przyciskWyniki.setPosition(10, 750);

    przyciskOpcje.setFont(font);
    przyciskOpcje.setString("OPCJE");
    przyciskOpcje.setCharacterSize(64);
    przyciskOpcje.setFillColor(Color::White);
    przyciskOpcje.setPosition(10, 850);

    przyciskWyjscie.setFont(font);
    przyciskWyjscie.setString("WYJSCIE");
    przyciskWyjscie.setCharacterSize(64);
    przyciskWyjscie.setFillColor(Color::White);
    przyciskWyjscie.setPosition(10, 950);

    przyciskWroc.setFont(font);
    przyciskWroc.setString("WROC");
    przyciskWroc.setCharacterSize(64);
    przyciskWroc.setFillColor(Color::White);
    przyciskWroc.setPosition(850, 950);

    przyciskG³os.setFont(font);

    przyciskG³os.setCharacterSize(64);
    przyciskG³os.setFillColor(Color::White);
    przyciskG³os.setPosition(50, 450);

    przyciskG³os2.setFont(font);

    przyciskG³os2.setCharacterSize(64);
    przyciskG³os2.setFillColor(Color::White);
    przyciskG³os2.setPosition(50, 650);

    przyciskzmniejsz.setFont(font);
    przyciskzmniejsz.setString("ZMNIEJSZ");
    przyciskzmniejsz.setCharacterSize(64);
    przyciskzmniejsz.setFillColor(Color::White);
    przyciskzmniejsz.setPosition(1000, 450);

    przyciskzmniejsz2.setFont(font);
    przyciskzmniejsz2.setString("ZMNIEJSZ");
    przyciskzmniejsz2.setCharacterSize(64);
    przyciskzmniejsz2.setFillColor(Color::White);
    przyciskzmniejsz2.setPosition(1000, 650);

    przyciskzwieksz.setFont(font);
    przyciskzwieksz.setString("ZWIEKSZ");
    przyciskzwieksz.setCharacterSize(64);
    przyciskzwieksz.setFillColor(Color::White);
    przyciskzwieksz.setPosition(1400, 450);
    przyciskzwieksz2.setFont(font);

    przyciskzwieksz2.setString("ZWIEKSZ");
    przyciskzwieksz2.setCharacterSize(64);
    przyciskzwieksz2.setFillColor(Color::White);
    przyciskzwieksz2.setPosition(1400, 650);

    muzyczkamenu.play();
    muzyczkamenu.setVolume(g³oœnoœæmenu);
    bool opcjeWidoczne = false;
    bool wynikiWidoczne = false;
    bool mainmenu = true;

    while (window.isOpen()) {
        przyciskG³os.setString("Glosnosc Muzyki w Menu:    " + to_string(g³oœnoœæmenu));
        przyciskG³os2.setString("Glosnosc Muzyki w Grze:      " + to_string(Gra::g³oœnoœægra));
        muzyczkamenu.setVolume(g³oœnoœæmenu);
        if (mainmenu) {
            window.clear();
            window.draw(tloS);
            window.draw(Tytu³);
            window.draw(przyciskGraj);
            window.draw(przyciskWyniki);
            window.draw(przyciskOpcje);
            window.draw(przyciskWyjscie);
            window.display();

            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }

                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (mysz(przyciskGraj)) {
                        Gra::nick = getNickname();
                        if (Gra::nick != "") {
                            window.close();
                            muzyczkamenu.stop();
                            Gra gra;
                            gra.run();

                        }
                        cout << "Klikniêto przycisk GRAJ!" << endl;
                    }
                    else if (mysz(przyciskWyniki)) {
                        wynikiWidoczne = true;
                        mainmenu = false;
                    }
                    else if (mysz(przyciskOpcje)) {
                        opcjeWidoczne = true;
                        mainmenu = false;
                    }
                    else if (mysz(przyciskWyjscie)) {
                        window.close();
                        muzyczkamenu.stop();
                    }
                }
            }
        }
        if (opcjeWidoczne) {
            // Wyœwietlanie ekranu opcji
            window.clear();
            window.draw(Tytu³);
            window.draw(tloS);
            window.draw(przyciskWroc);
            window.draw(przyciskzwieksz);
            window.draw(przyciskzwieksz2);
            window.draw(przyciskzmniejsz);
            window.draw(przyciskzmniejsz2);
            window.draw(przyciskG³os);
            window.draw(przyciskG³os2);
            window.display();
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (mysz(przyciskWroc)) {
                    mainmenu = true;
                    opcjeWidoczne = false;
                    cout << "Klikniêto przycisk WRÓÆ!" << endl;
                }
                else if (mysz(przyciskzmniejsz)) {
                    if (g³oœnoœæmenu >= 10) {
                        sleep(seconds(0.1));
                        g³oœnoœæmenu = g³oœnoœæmenu - 10;
                    }
                    cout << "Klikniêto przycisk ZMNIEJSZ! " << g³oœnoœæmenu << endl;
                }
                else if (mysz(przyciskzwieksz)) {
                    if (90 >= g³oœnoœæmenu) {
                        sleep(seconds(0.1));
                        g³oœnoœæmenu = g³oœnoœæmenu + 10;
                        cout << "Klikniêto przycisk ZWIEKSZ! " << g³oœnoœæmenu << endl;
                    }
                }
                else if (mysz(przyciskzmniejsz2)) {
                    cout << "Klikniêto przycisk ZMNIEJSZ2! " << endl;
                    if (Gra::g³oœnoœægra >= 10) {
                        sleep(seconds(0.1));
                        Gra::g³oœnoœægra = Gra::g³oœnoœægra - 10;
                    }
                    cout << "Klikniêto przycisk ZMNIEJSZ2! " << Gra::g³oœnoœægra << endl;
                }
                else if (mysz(przyciskzwieksz2)) {
                    cout << "Klikniêto przycisk ZWIEKSZ2! " << endl;
                    if (90 >= Gra::g³oœnoœægra) {
                        sleep(seconds(0.1));
                        Gra::g³oœnoœægra = Gra::g³oœnoœægra + 10;
                    }
                    cout << "Klikniêto przycisk ZWIEKSZ2! " << Gra::g³oœnoœægra << endl;
                }
            }
        }
        else if (wynikiWidoczne) {

            window.clear();
            window.draw(Tytu³);
            window.draw(tloS);
            window.draw(przyciskWroc);
            wyswietlWynikiTabelka();
            window.display();
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (mysz(przyciskWroc)) {
                    mainmenu = true;
                    wynikiWidoczne = false;
                    cout << "Klikniêto przycisk WRÓÆ!" << endl;
                }
            }
        }
    }

}

void Menu::run() {
  init();
}

bool Menu::mysz(const Text& button) {
    Vector2i mousePosition = Mouse::getPosition(window);
    FloatRect buttonBounds = button.getGlobalBounds();

    return buttonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}