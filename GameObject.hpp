#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();

        virtual void update(const sf::Time& frameTime);
        virtual void draw(sf::RenderTarget& renderTarget);

    protected:
    private:
};

#endif // GAMEOBJECT_HPP
