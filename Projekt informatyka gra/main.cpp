#include "Gra.h"
#include "Menu.h"
int main()
{
    RenderWindow window(sf::VideoMode(1920, 1080), "LAVA DUNGEON");
    Menu menu(window);
    menu.run();
    return 0;
}