#include "Starter.hpp"

Starter::Starter()
{
}

Starter::~Starter()
{
}

Game Starter::game;

void Starter::removeGame()
{
    game.~Game();
}
