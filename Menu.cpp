#include "Menu.hpp"
#include "Ressources/RessourceManager.hpp"

#include "Starter.hpp"

#include <iostream>

Menu::Menu()
{
    m_menuTitle.setCharacterSize(80);
    m_menuTitle.setPosition(0,0);
    m_menuTitle.setFont(Font().GetRessource("Data/Font/calibri.ttf"));
    m_menuTitle.setColor(sf::Color::Black);
    setActiveMenu(Title);
    m_menuUp = true;
}

Menu::~Menu()
{
    //dtor
}

void Menu::setActiveMenu(MenuType menu)
{
    m_activeMenu = menu;
    switch(menu)
    {
        case Menu::Title :
            m_menuTitle.setString("TicTacToe");
            m_centerTitle = true;
            m_menuUp = true;

            m_menuItems.clear();
            m_menuItems.push_back(new MenuItem(TITLE_SOLO, "Joueur Seul", sf::Vector2f(50, 150), Font().GetRessource("Data/Font/calibri.ttf"), 50));
            m_menuItems.push_back(new MenuItem(TITLE_MULTI, "Deux Joueurs", sf::Vector2f(50, 220), Font().GetRessource("Data/Font/calibri.ttf"), 50));
            //m_menuItems.push_back(new MenuItem(TITLE_MULTI_NETWORK, "Multijoueur Reseau", sf::Vector2f(50, 290), Font().GetRessource("Data/Font/calibri.ttf"), 50));
            //m_menuItems.push_back(new MenuItem(TITLE_OPTION, "Options", sf::Vector2f(50, 360), Font().GetRessource("Data/Font/calibri.ttf"), 50));
            m_menuItems.push_back(new MenuItem(QUIT, "Quitter", sf::Vector2f(50, 430), Font().GetRessource("Data/Font/calibri.ttf"), 50));
            break;
        case Menu::Options :
            m_menuTitle.setString("Ha Ha Ha");

            m_menuItems.clear();
            m_menuItems.push_back(new MenuItem(BACK_TO_TITLE, "Back Off", sf::Vector2f(50, 180), Font().GetRessource("Data/Font/calibri.ttf"), 50));
            break;
        case Menu::EnJeu :
            m_menuTitle.setString("Menu");
            m_centerTitle = true;

            m_menuItems.clear();
            m_menuItems.push_back(new MenuItem(BACK_TO_TITLE, "Quitter la partie", sf::Vector2f(50, 180), Font().GetRessource("Data/Font/calibri.ttf"), 50));
            m_menuItems.push_back(new MenuItem(BACK_TO_GAME, "Reprendre", sf::Vector2f(50, 250), Font().GetRessource("Data/Font/calibri.ttf"), 50));
            break;
        case Menu::EndGame :
            {
                std::string winner;
                switch(Starter::game.m_ttt.getWinner())
                {
                case TicTacToe::PLAYERX :
                    winner = "Bleu a gagne";
                    break;
                case TicTacToe::PLAYERO :
                    winner = "Rouge a gagne";
                    break;
                case TicTacToe::TIE:
                    winner = "Match nul";
                    break;
                default :
                    break;
                }

                m_menuTitle.setString(winner);
                m_centerTitle = true;
                Starter::game.addGameObject(*this);
                m_menuUp = true;

                m_menuItems.clear();
                m_menuItems.push_back(new MenuItem(RESTART_GAME, "Recommencer", sf::Vector2f(50, 180), Font().GetRessource("Data/Font/calibri.ttf"), 50));
                m_menuItems.push_back(new MenuItem(BACK_TO_TITLE, "Retour au menu", sf::Vector2f(50, 250), Font().GetRessource("Data/Font/calibri.ttf"), 50));
            }
            break;
        default :
            break;
    }
}

void Menu::update(const sf::Time& frameTime)
{

}

void Menu::draw(sf::RenderTarget& renderTarget)
{
    sf::RectangleShape bg(sf::Vector2f(renderTarget.getSize().x, renderTarget.getSize().y));
    bg.setFillColor(sf::Color(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, 210));
    bg.setPosition(0,0);
    renderTarget.draw(bg);
    if(m_centerTitle)
    {
        m_menuTitle.setPosition(renderTarget.getSize().x/2 - m_menuTitle.getLocalBounds().width/2, 0);
        m_centerTitle = false;
    }

    renderTarget.draw(m_menuTitle);

    for(std::vector<MenuItem*>::iterator it=m_menuItems.begin(); it != m_menuItems.end(); it++)
    {
        (*it)->draw(renderTarget);
    }
}

bool Menu::handleEvent(const sf::Event& event, const sf::Window& relativeTo)
{
    if(Starter::game.getStatus() == Game::PLAYING)
    {
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            if(m_menuUp)
            {
                // on retire le menu des object à afficher
                Starter::game.removeGameObject();
                // on le desactive
                m_menuUp = false;
            }
            else
            {
                Starter::game.addGameObject(*this);
                m_menuUp = true;
            }

            return true;
        }
    }

    if(m_menuUp)
    {
        // Actions esthetiques sur le menu (mise en évidence des option où la souris se trouve
        if(event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mousePos(sf::Mouse::getPosition(relativeTo).x, sf::Mouse::getPosition(relativeTo).y);

            for(std::vector<MenuItem*>::iterator it=m_menuItems.begin(); it != m_menuItems.end(); it++)
            {
                (*it)->updateHover(mousePos);
            }
        }
        // Action en cas de click sur une option du menu
        else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left )
        {
            sf::Vector2f mousePos(sf::Mouse::getPosition(relativeTo).x, sf::Mouse::getPosition(relativeTo).y);

            for(std::vector<MenuItem*>::iterator it=m_menuItems.begin(); it != m_menuItems.end(); it++)
            {
                if((*it)->isClicked(mousePos))
                {
                    switch((*it)->getId())
                    {
                    case BACK_TO_TITLE :
                        if(Starter::game.getStatus() == Game::PLAYING)
                            Starter::game.stopGame();
                        else
                            setActiveMenu(Menu::Title);
                        break;
                    case QUIT :
                        Starter::game.quit();
                        break;
                    case TITLE_SOLO :
                        m_menuUp = false;
                        Starter::game.startLocalGame(false);
                        break;
                    case TITLE_MULTI :
                        m_menuUp = false;
                        Starter::game.startLocalGame(true);
                        break;
                    case TITLE_MULTI_NETWORK :
                        setActiveMenu(Menu::Options);
                        break;
                    case TITLE_OPTION :
                        setActiveMenu(Menu::Options);
                        break;
                    case BACK_TO_GAME :
                        Starter::game.removeGameObject();
                        m_menuUp = false;
                        break;
                    case RESTART_GAME :
                        Starter::game.startLocalGame(Starter::game.m_ttt.isMulti());
                        m_menuUp = false;
                        break;
                    default :
                        break;
                    }

                    return true;
                }
            }
        }
        return true;
    }

    return false;
}
