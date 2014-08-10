#ifndef MENUITEM_HPP
#define MENUITEM_HPP

#include "GameObject.hpp"
#include "MenuEnum.hpp"


class MenuItem : public GameObject
{
    public:
        MenuItem(MenuOption textId, std::string text, sf::Vector2f position, sf::Font& font, int charSize);
        virtual ~MenuItem();

        virtual void update(const sf::Time& frameTime);
        virtual void draw(sf::RenderTarget& renderTarget);

        sf::Text& getText();

        void setId(const MenuOption& textId);
        MenuOption getId();

        void setText(const std::string& newText);
        void setPosition(const sf::Vector2f& position);
        void setFont(const sf::Font& font);
        void setCharSize(const int& charSize);
        void setColor(const sf::Color& color);

        bool isClicked(sf::Vector2f& mousePosition);
        void updateHover(sf::Vector2f& mousePosition);

    protected:

        MenuOption m_id;
        sf::Text m_text;
};

#endif // MENUITEM_HPP
