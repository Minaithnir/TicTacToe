#ifndef MENU_HPP
#define MENU_HPP

#include "Event/EventUser.hpp"
#include "GameObject.hpp"
#include "MenuItem.hpp"

#include <vector>

class Menu : public EventUser, public GameObject
{
    public:
        Menu();
        virtual ~Menu();

        virtual bool handleEvent(const sf::Event& event, const sf::Window& relativeTo);

        virtual void update(const sf::Time& frameTime);
        virtual void draw(sf::RenderTarget& renderTarget);

        enum MenuType
        {
            Title,
            Options,
            EnJeu,
            EndGame
        };

        void setActiveMenu(MenuType menu);

    protected:
        MenuType m_activeMenu;

        // mettre à true pour centrer le titre au prochain affichage
        bool m_centerTitle;

        sf::Text m_menuTitle;
        std::vector<MenuItem*> m_menuItems;

        // savoir si le menu est up ou pas pendant une partie
        bool m_menuUp;

};

#endif // MENU_HPP
