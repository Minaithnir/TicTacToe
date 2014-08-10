#ifndef STARTER_HPP
#define STARTER_HPP

#include "Game.hpp"

class Starter
{
    public:
        static Game game;

        Starter();
        virtual ~Starter();


        static void removeGame();
};

#endif // STARTER_HPP
