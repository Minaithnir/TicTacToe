#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "GameObject.hpp"
#include "Event/EventUser.hpp"
#include "define.hpp"

class TicTacToe : public GameObject, public EventUser
{
    public:
        TicTacToe();
        virtual ~TicTacToe();

        void reset();

        virtual bool handleEvent(const sf::Event& event, const sf::Window& relativeTo);

        virtual void update(const sf::Time& frameTime);
        virtual void draw(sf::RenderTarget& renderTarget);

        void setMulti(bool multi=true);
        bool isMulti();

        enum Player
        {
            NONE,
            PLAYERX,
            PLAYERO,
            TIE
        };

        Player getWinner();

    protected:

        Player m_grid[GRID_SIZE][GRID_SIZE];
        bool m_multi;
        Player m_turn;
        Player m_iaColor;

        Player m_winner;

        sf::Vector2f m_lastPointerLoc;

        void switchTurn();
};

#endif // TICTACTOE_HPP
