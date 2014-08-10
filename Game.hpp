#ifndef GAME_HPP
#define GAME_HPP

#include "TicTacToe.hpp"
#include "Menu.hpp"
#include "Event/EventUser.hpp"
#include "GameObject.hpp"
#include "define.hpp"

#include <SFML/Graphics.hpp>

#include <list>

class TicTacToe;

class Game
{
        friend Menu;
        friend TicTacToe;

    public:
        Game();
        virtual ~Game();

        void initialise();
        void clear();

        bool loop();

        void quit();

        // gestion des eventHandlers
        void addEventUser(EventUser& eventUser, const bool& insertBack = false);
        void clearEventUsers();
        void removeEventUser(const bool& removeBack = false);

        // gestion des gameObjects
        void addGameObject(GameObject& gameObject, const bool& insertBack = false);
        void clearGameObjects();
        void removeGameObject(const bool& removeBack = false);

        enum Status
        {
            WAITING,
            PLAYING
        };

        Status getStatus();

    protected:

        sf::RenderWindow m_window;
        Status m_status;

        void startLocalGame(bool multi = false);
        void stopGame();

    private:

        Menu m_menu;
        TicTacToe m_ttt;

        void loadRessources();

        bool m_loading;
        std::list<EventUser*> m_eventUsers;
        bool m_euCleaned;

        std::list<GameObject*> m_gameObjects;
        bool m_goCleaned;

};

#endif // GAME_HPP
