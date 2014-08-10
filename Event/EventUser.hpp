#ifndef EVENTUSER_HPP
#define EVENTUSER_HPP

#include <SFML/Window.hpp>

class EventUser
{
    public:
        EventUser();
        virtual ~EventUser();

        virtual bool handleEvent(const sf::Event& event, const sf::Window& relativeTo);

    protected:
    private:
};

#endif // EVENTSUSER_HPP
