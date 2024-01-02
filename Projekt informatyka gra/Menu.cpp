#include "menu.h"

using namespace std;
using namespace sf;

void Menu::ustawTlo(const std::string& sciezkaDoObrazka) {
    if (!tloT.loadFromFile(sciezkaDoObrazka)) {
        cerr << "B��d �adowania obrazka t�a!" << endl;
        // Dodaj obs�ug� b��du, na przyk�ad u�ywaj�c domy�lnego t�a lub wyrzucaj�c wyj�tek
    }
    tloS.setTexture(tloT);
    tloS.setPosition(0, 0);
    tloS.setScale(window.getSize().x / tloT.getSize().x, window.getSize().y / tloT.getSize().y);
}

Menu::Menu(RenderWindow& window) : window(window) {
    // Tu mo�na umie�ci� ewentualne operacje konstrukcyjne, je�li s� potrzebne
    ustawTlo("Menu.jpg");  // Dodaj t� lini�, podaj�c w�a�ciw� �cie�k� do obrazka t�a
}

int Menu::init() {
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "B��d �adowania czcionki!" << endl;
        return 0;
    }

    Text Tytu�, przyciskGraj, przyciskWyniki, przyciskOpcje, przyciskWyjscie;

    Tytu�.setFont(font);
    Tytu�.setString("LAVA DUNGEON");
    Tytu�.setCharacterSize(154);
    Tytu�.setFillColor(Color::White);
    Tytu�.setPosition(400,200);

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

    int x = 0;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if (mysz(przyciskGraj)) {
                    x = 1;
                    window.close();
                    cout << "Klikni�to przycisk GRAJ!" << endl;
                }
                else if (mysz(przyciskWyniki)) {
                    x = 2;
                    cout << "Klikni�to przycisk WYNIKI!" << endl;
                }
                else if (mysz(przyciskOpcje)) {
                    x = 3;
                    cout << "Klikni�to przycisk OPCJE!" << endl;
                }
                else if (mysz(przyciskWyjscie)) {
                    cout << "Klikni�to przycisk WYJSCIE!" << endl;
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(tloS);
        window.draw(Tytu�);
        window.draw(przyciskGraj);
        window.draw(przyciskWyniki);
        window.draw(przyciskOpcje);
        window.draw(przyciskWyjscie);
        window.display();
    }
    return x;
}

int Menu::run() {
    return init();
}

bool Menu::mysz(const Text& button) {
    Vector2i mousePosition = Mouse::getPosition(window);
    FloatRect buttonBounds = button.getGlobalBounds();

    return buttonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}
