
#include <SFML/Graphics.hpp>
#include "Starter.hpp"

#include <iostream>

int main()
{
    Starter::game.initialise();
    Starter::game.loop();

    //necessaire pour �viter les probl�me de destruction dans un ordre al�atoire
    Starter::game.clear();

    return 0;
}
