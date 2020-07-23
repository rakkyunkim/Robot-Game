#include "Arena.h"
#include "Player.h"
#include "Robot.h"
#include <iostream>
using namespace std;
///////////////////////////////////////////////////////////////////////////
//  Arena implementations
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
            << nCols << "!" << endl;
        exit(1);
    }

    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRobots = 0;
}

Arena::~Arena()
{
    for (int i = 0; i < m_nRobots; i++)
        delete m_robots[i];
    delete m_player;
    
}

int Arena::rows() const
{
   
    return m_rows;  
}

int Arena::cols() const
{
    
    return m_cols; 
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::robotCount() const
{
    return m_nRobots;
}

int Arena::nRobotsAt(int r, int c) const
{
    int counter = 0;
    
    for (int i = 0; i < m_nRobots; i++) {
        if (m_robots[i]->row() == r && m_robots[i]->col() == c)
            counter++;
    }
    
    return counter;  
}

void Arena::display(string msg) const
{
   
    char grid[MAXROWS][MAXCOLS];
    int r, c;
  

    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    for (int i = 0; i < m_nRobots; i++) 
    {
        int counter = 0;        
        char& posRobot = grid[m_robots[i]->row() - 1][m_robots[i]->col() - 1]; // ith robot's current position
        if (posRobot == '.') {
            for (int j = i; j < m_nRobots; j++)
            {
                if (m_robots[i]->row() == m_robots[j]->row() && m_robots[i]->col() == m_robots[j]->col())
                    counter++;
            }
            if (counter == 1)
                posRobot = 'R';
            else if (counter == 2)
                posRobot = '2';
            else if (counter == 3)
                posRobot = '3';
            else if (counter == 4)
                posRobot = '4';
            else if (counter == 5)
                posRobot = '5';
            else if (counter == 6)
                posRobot = '6';
            else if (counter == 7)
                posRobot = '7';
            else if (counter == 8)
                posRobot = '8';
            else if (counter >= 9)
                posRobot = '9';

          
        }
            
    }

    // Indicate player's position
    if (m_player != nullptr)
    {
        // Set the char to '@', unless there's also a robot there,
        // in which case set it to '*'.
        char& gridChar = grid[m_player->row() - 1][m_player->col() - 1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

    // Write message, robot, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << robotCount() << " robots remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Arena::addRobot(int r, int c)
{
    
    if (m_nRobots < MAXROBOTS) {
        m_robots[m_nRobots] = new Robot(this, r, c);
        m_nRobots++;
        return true;
    }
    
    return false;  
}

bool Arena::addPlayer(int r, int c)
{
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

    // Dynamically allocate a new Player and add it to the arena
    m_player = new Player(this, r, c);
    return true;
}

void Arena::damageRobotAt(int r, int c)
{
    
    
        for (int i = 0; i < m_nRobots; i++) {
            if (m_robots[i]->row() == r && m_robots[i]->col() == c && !m_robots[i]->isDamaged()) {
                m_robots[i]->Damage();
                return;
            }
            else if (m_robots[i]->row() == r && m_robots[i]->col() == c && m_robots[i]->isDamaged()) {
                m_robots[i]->Destroy();
                delete m_robots[i];
                for (int j = i; j < m_nRobots - 1; j++) {
                    m_robots[j] = m_robots[j + 1];
                }
                m_nRobots--;
                return;
            }
        }
}

bool Arena::moveRobots()
{
    for (int k = 0; k < m_nRobots; k++)
    {
        
        m_robots[k]->move();
        if (m_robots[k]->row() == m_player->row() && m_robots[k]->col() == m_player->col())
            m_player->setDead();
    }

    // return true if the player is still alive, false otherwise
    return m_player->isDead();
}
