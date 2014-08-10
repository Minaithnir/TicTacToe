#include "MenuItem.hpp"

#include <iostream>

#define HOVER_SHADE 100

MenuItem::MenuItem(MenuOption textId, std::string text, sf::Vector2f position, sf::Font& font, int charSize)
{
    m_id = textId;

    m_text.setFont(font);
    m_text.setString(text);
    m_text.setPosition(position);
    m_text.setCharacterSize(charSize);

    m_text.setColor(sf::Color::Black);
}

MenuItem::~MenuItem()
{
    //dtor
}

sf::Text& MenuItem::getText()
{
    return m_text;
}

void MenuItem::update(const sf::Time& frameTime)
{

}

void MenuItem::draw(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(m_text);
}

void MenuItem::setId(const MenuOption& textId)
{
    m_id = textId;
}

MenuOption MenuItem::getId()
{
    return m_id;
}

void MenuItem::setText(const std::string& newText)
{
    m_text.setString(newText);
}

void MenuItem::setPosition(const sf::Vector2f& position)
{
    m_text.setPosition(position);
}

void MenuItem::setFont(const sf::Font& font)
{
    m_text.setFont(font);
}

void MenuItem::setCharSize(const int& charSize)
{
    m_text.setCharacterSize(charSize);
}

void MenuItem::setColor(const sf::Color& color)
{
    m_text.setColor(color);
}

bool MenuItem::isClicked(sf::Vector2f& mousePosition)
{
    return m_text.getGlobalBounds().contains(mousePosition);
}

void MenuItem::updateHover(sf::Vector2f& mousePosition)
{
    if(m_text.getGlobalBounds().contains(mousePosition))
        m_text.setColor(sf::Color(HOVER_SHADE, HOVER_SHADE, HOVER_SHADE));
    else
        m_text.setColor(sf::Color::Black);
}
