
#include <SFML/Graphics.hpp>
#include "Starter.hpp"

#include <iostream>

int main()
{
    Starter::game.initialise();
    Starter::game.loop();

    //necessaire pour éviter les problème de destruction dans un ordre aléatoire
    Starter::game.clear();

    return 0;
}
