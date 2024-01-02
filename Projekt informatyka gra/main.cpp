#include "Gra.h"
#include "Menu.h"
int main()
{
    RenderWindow window(sf::VideoMode(1920, 1080), "LAVA DUNGEON");
    Menu menu(window);

    int x =0;
    x = menu.run();
    if (x == 1) {
        Gra gra;
        gra.run();
    }

    return 0;
}