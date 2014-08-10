
#include "Game.hpp"
#include "Ressources/RessourceManager.hpp"

#include <iostream>

Game::Game()
{
    m_status = Game::WAITING;
    m_euCleaned = false;
    m_goCleaned = false;
    srand(time(NULL));
}

Game::~Game()
{
}

void Game::clear()
{
    clearEventUsers();
    clearGameObjects();
    Texture().FreeRessources();
    Font().FreeRessources();
    SoundBuf().FreeRessources();
}

void Game::quit()
{
    m_window.close();
}

void Game::addEventUser(EventUser& eventUser, const bool& insertBack)
{
    if(insertBack)
        m_eventUsers.push_back(&eventUser);
    else
        m_eventUsers.push_front(&eventUser);
}

void Game::clearEventUsers()
{
    m_eventUsers.clear();
    m_euCleaned = true;
}

void Game::removeEventUser(const bool& removeBack)
{
    if(removeBack)
        m_eventUsers.pop_back();
    else
        m_eventUsers.pop_front();
}

void Game::addGameObject(GameObject& gameObject, const bool& insertBack)
{
    if(insertBack)
        m_gameObjects.push_front(&gameObject);
    else
        m_gameObjects.push_back(&gameObject);
}

void Game::clearGameObjects()
{
    m_gameObjects.clear();
    m_goCleaned = true;
}

void Game::removeGameObject(const bool& removeBack)
{
    if(removeBack)
        m_gameObjects.pop_front();
    else
        m_gameObjects.pop_back();
}

Game::Status Game::getStatus()
{
    return m_status;
}

/**
    Méthode lançant le chargement initial de ressources et l'affichage du Splash screen
*/
void Game::initialise()
{
    // Chargement du splash screen
    sf::Texture texture;
    if(!texture.loadFromFile("Data/splash.jpg"))
    {
        if(!texture.create(W_WIDTH/2, W_HEIGHT/2))
        {
            exit(EXIT_FAILURE);
        }
    }
    sf::Sprite splash;
    splash.setTexture(texture);

    // Lancer le chargement des ressources
    m_loading = true;
    sf::Thread loader(&Game::loadRessources, &(*this));
    loader.launch();

    // Afficher le splash screen et attendre la fin du chargement
    bool quit = false;

    m_window.create(sf::VideoMode(W_WIDTH/2, W_HEIGHT/2), W_TITLE, sf::Style::None);

    do {

        sf::Event event;
        while (m_window.pollEvent(event))
        {
            quit = true;
        }

        m_window.draw(splash);
        m_window.display();

    } while(m_loading || !quit);

    // Reset la fenêtre à l'état utilisé par le jeu
    m_window.create(sf::VideoMode(W_WIDTH, W_HEIGHT), W_TITLE, sf::Style::Titlebar | sf::Style::Close);

}

/**
    Méthode chargeant les ressources initiales du jeu (menus / images de fond / musique)
*/
void Game::loadRessources()
{
    m_loading = false;
}

/**
    Méthode contenant la boucle principale du jeu
        Gestion des évènements
        Logique du jeu
        Affichage des divers éléments
*/
bool Game::loop()
{
    sf::Clock clock;

    // On affiche tout d'abord le menu principal
    addEventUser(m_menu);
    addGameObject(m_menu);


    do {

        /*
            Gestion des evènementts :
                Si fermeture, on ferme la fenêtre
                Les autres évènements sont passés aux différentes couches réagissant aux events
        */
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
            else
            {
                std::list<EventUser*>::iterator eventUsersIterator;
                eventUsersIterator = m_eventUsers.begin();
                while(eventUsersIterator!=m_eventUsers.end() && !(*eventUsersIterator)->handleEvent(event, m_window))
                {
                    eventUsersIterator ++;
                }
            }
        }

        /*
            Logique du jeu
        */
        sf::Time frameTime = clock.getElapsedTime();
        clock.restart();
        for(std::list<GameObject*>::iterator gameObjectIterator = m_gameObjects.begin(); gameObjectIterator != m_gameObjects.end() && !m_euCleaned; gameObjectIterator++)
        {
            (*gameObjectIterator)->update(frameTime);
        }

        if(m_euCleaned)
            m_euCleaned = false;

        m_window.clear(sf::Color(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B));

        /*
            Affichage des divers éléments
        */
        for(std::list<GameObject*>::iterator gameObjectIterator = m_gameObjects.begin(); gameObjectIterator != m_gameObjects.end() && !m_goCleaned; gameObjectIterator++)
        {
            (*gameObjectIterator)->draw(m_window);
        }

        if(m_goCleaned)
            m_goCleaned = false;

        m_window.display();

    } while(m_window.isOpen());

    return false;
}

void Game::startLocalGame(bool multi)
{
    m_ttt.reset();
    clearGameObjects();

    m_status = Game::PLAYING;
    m_ttt.setMulti(multi);
    m_menu.setActiveMenu(Menu::EnJeu);

    addGameObject(m_ttt);
    addEventUser(m_ttt, true);
}

void Game::stopGame()
{
    clearGameObjects();
    clearEventUsers();

    m_status = Game::WAITING;

    m_menu.setActiveMenu(Menu::Title);

    addEventUser(m_menu);
    addGameObject(m_menu);
}
