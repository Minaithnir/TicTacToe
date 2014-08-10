#include "TicTacToe.hpp"
#include "Starter.hpp"
#include "Ressources/RessourceManager.hpp"

#include <iostream>

TicTacToe::TicTacToe()
{
    reset();
}

TicTacToe::~TicTacToe()
{
    //dtor
}

void TicTacToe::reset()
{
    for(unsigned int i = 0; i< GRID_SIZE; i++)
        for(unsigned int j =0; j< GRID_SIZE; j++)
            m_grid[i][j] = TicTacToe::NONE;

    m_turn = TicTacToe::PLAYERX;
    m_winner = TicTacToe::NONE;
}

void TicTacToe::setMulti(bool multi)
{
    m_multi = multi;
    if(!m_multi)
    {
        int turn = rand()%2;
        m_iaColor = (turn == 0 ? TicTacToe::PLAYERX : TicTacToe::PLAYERO);
    }
}

bool TicTacToe::isMulti()
{
    return m_multi;
}

TicTacToe::Player TicTacToe::getWinner()
{
    return m_winner;
}

bool TicTacToe::handleEvent(const sf::Event& event, const sf::Window& relativeTo)
{
    if(event.type == sf::Event::MouseMoved)
        m_lastPointerLoc = sf::Vector2f(sf::Mouse::getPosition(relativeTo).x, sf::Mouse::getPosition(relativeTo).y);

    if(m_multi || (!m_multi && m_turn != m_iaColor))
    {
        if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left )
        {
            sf::Vector2f mousePos(sf::Mouse::getPosition(relativeTo).x, sf::Mouse::getPosition(relativeTo).y);
            if(mousePos.x > OFFSET_X && mousePos.x < OFFSET_X + GRID_SIZE*CASE_SIZE
               && mousePos.y > OFFSET_Y && mousePos.y < OFFSET_Y + GRID_SIZE*CASE_SIZE)
            {
                int caseX = (mousePos.x - OFFSET_X) / CASE_SIZE;
                int caseY = (mousePos.y - OFFSET_Y) / CASE_SIZE;

                if(m_grid[caseY][caseX] == NONE)
                {
                    m_grid[caseY][caseX] = m_turn;
                    switchTurn();
                }
            }
        }
    }


    return false;
}

void TicTacToe::update(const sf::Time& frameTime)
{
    if(m_winner == TicTacToe::NONE)
    {
        //test s'il y a un vainqueur
        for(unsigned int i=0; i<GRID_SIZE && m_winner == TicTacToe::NONE; i++)
        {
            //test horizontal
            if(m_grid[i][0] != TicTacToe::NONE && m_grid[i][0] == m_grid[i][1] && m_grid[i][1] == m_grid[i][2])
                m_winner = m_grid[i][0];

            //test vertical
            if(m_grid[0][i] != TicTacToe::NONE && m_grid[0][i] == m_grid[1][i] && m_grid[1][i] == m_grid[2][i])
                m_winner = m_grid[0][i];

            //test des diagonales
            if(m_grid[1][1] != TicTacToe::NONE && m_grid[0][0] == m_grid[1][1] && m_grid[1][1] == m_grid[2][2])
                m_winner = m_grid[1][1];

            if(m_grid[1][1] != TicTacToe::NONE && m_grid[0][2] == m_grid[1][1] && m_grid[1][1] == m_grid[2][0])
                m_winner = m_grid[1][1];
        }

        if(m_winner == TicTacToe::NONE)
        {
            //test s'il reste des coup possibles
            bool full = true;

            for(unsigned int i = 0; i< GRID_SIZE; i++)
                for(unsigned int j =0; j< GRID_SIZE; j++)
                    if(m_grid[i][j] == TicTacToe::NONE)
                        full = false;
            if(full)
            {
                m_winner = TicTacToe::TIE;
                Starter::game.m_menu.setActiveMenu(Menu::EndGame);
            }
            else if(m_winner == TicTacToe::NONE && !m_multi && m_turn == m_iaColor)
            {
                int x, y;
                do {
                    x=rand()%GRID_SIZE;
                    y=rand()%GRID_SIZE;
                } while(m_grid[y][x] != TicTacToe::NONE);
                m_grid[y][x] = m_iaColor;
                switchTurn();
            }
        }
        else
        {
            Starter::game.m_menu.setActiveMenu(Menu::EndGame);
        }

    }
}

void TicTacToe::draw(sf::RenderTarget& renderTarget)
{
    sf::RectangleShape gridLine(sf::Vector2f(3*CASE_SIZE, 4));
    gridLine.setTexture(&Texture().GetRessource("Data/Image/border.png"));
    Texture().GetRessource("Data/Image/border.png").setRepeated(true);
    gridLine.setTextureRect(sf::IntRect(0,0,0,4));

    gridLine.setRotation(90);

    //draw verticales lines
    for(unsigned int i =0; i< GRID_SIZE+1; i++)
    {
        gridLine.setPosition(i*CASE_SIZE + OFFSET_X, OFFSET_Y);
        renderTarget.draw(gridLine);
    }

    gridLine.setRotation(0);

    //draw horizontal lines
    for(unsigned int i =0; i< GRID_SIZE+1; i++)
    {
        gridLine.setPosition(OFFSET_X, i*CASE_SIZE + OFFSET_Y);
        renderTarget.draw(gridLine);
    }

    sf::Sprite spriteX, spriteO;
    spriteX.setTexture(Texture().GetRessource("Data/Image/x.png"));
    spriteO.setTexture(Texture().GetRessource("Data/Image/o.png"));

    for(unsigned int i = 0; i< GRID_SIZE; i++)
    {
        for(unsigned int j =0; j< GRID_SIZE; j++)
        {
            //x_and_o.setPosition(OFFSET_X*2 + j*CASE_SIZE, OFFSET_Y*2 + i*CASE_SIZE);
            switch(m_grid[i][j])
            {
                case TicTacToe::PLAYERX :
                    spriteX.setPosition(OFFSET_X*2 + j*CASE_SIZE, OFFSET_Y*2 + i*CASE_SIZE);
                    renderTarget.draw(spriteX);
                    break;
                case TicTacToe::PLAYERO :
                    spriteO.setPosition(OFFSET_X*2 + j*CASE_SIZE, OFFSET_Y*2 + i*CASE_SIZE);
                    renderTarget.draw(spriteO);
                    break;
                default:
                    break;
            }
        }
    }

    if(m_turn == TicTacToe::PLAYERX)
    {
        spriteX.setPosition(m_lastPointerLoc);
        spriteX.setScale(0.3, 0.3);
        renderTarget.draw(spriteX);
    }
    else
    {
        spriteO.setPosition(m_lastPointerLoc);
        spriteO.setScale(0.3, 0.3);
        renderTarget.draw(spriteO);
    }
}

void TicTacToe::switchTurn()
{
    m_turn = (m_turn == TicTacToe::PLAYERX ? PLAYERO : PLAYERX);
}
