#include "Player.h"
#include <iostream>
#include "Arena.h"
#include "Robot.h"
using namespace std;
///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
            << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    
    return m_row;  
}

int Player::col() const
{
    
    return m_col;  
}

int Player::age() const
{
    
    return m_age;  
}

string Player::takeComputerChosenTurn()
{
    // WHEN robots are in the shooting range and at least two units away from the player.



    int up = m_arena->nRobotsAt(m_row - 1, m_col);
    int down = m_arena->nRobotsAt(m_row + 1, m_col);
    int left = m_arena->nRobotsAt(m_row, m_col - 1);
    int right = m_arena->nRobotsAt(m_row, m_col + 1);

    int downRight = m_arena->nRobotsAt(m_row + 1, m_col + 1);
    int downLeft = m_arena->nRobotsAt(m_row + 1, m_col - 1);
    int upRight = m_arena->nRobotsAt(m_row - 1, m_col + 1);
    int upLeft = m_arena->nRobotsAt(m_row - 1, m_col - 1);

    int robotCounter = 0;
    if (up > 0)
        robotCounter++;
    if (down > 0)
        robotCounter++;
    if (left > 0)
        robotCounter++;
    if (right > 0)
        robotCounter++;
    
    switch (robotCounter)
    {
    case 0:
        if (downRight > 0 && downLeft > 0 && upRight > 0 && upLeft > 0) {
            stand();
            return "Stood.";
        }
        if (downRight > 0) {
            if (m_row == 1) {
                if (m_col == 1) {
                    stand();
                    return "Stood.";
                }
            }
            if (downLeft > 0) {
                move(0);
                return "Moved.";
            }
            if (upRight > 0) {
                move(2);
                return "Moved.";
            }
            if (upLeft > 0) {
                stand();
                return "Stood.";
            }
            move(0);
            return "Moved.";
        }
        if (upRight > 0) {
            if (m_col == 1) {
                if (m_row == m_arena->rows()) {
                    stand();
                    return "Stood.";
                }
            }
            if (upLeft > 0) {
                move(1);
                return "Moved.";
            }
            if (downLeft > 0) {
                stand();
                return "Stood.";
            }
            move(2);
            return "Moved.";

        }
        if (upLeft > 0) {
            if (m_row == m_arena->rows()) {
                if (m_col == m_arena->cols()) {
                    stand();
                    return "Stood.";
                }
            }
            if (downLeft > 0) {
                move(3);
                return "Moved.";
            }
            move(1);
            return "Moved.";
        }
    case 1: // when 1 robots are around the player.
        if (down > 0) {
            if (upRight > 0) {
                move(2);
                return "Moved.";
            }
            if (upLeft > 0) {
                move(3);
                return "Moved.";
            }
            if (m_row == 1) { //if cornered.
                if (m_col == 1) {
                    move(3);
                    return "Moved.";
                }
                if (m_col == m_arena->cols()) {
                    move(2);
                    return "Moved.";
                }

                move(2);
                return "Moved.";
            }
            move(0);
            return "Moved.";
        }
        else if (up > 0) {
            if (downRight > 0 || upRight > 0) {
                move(2);
                return "Moved.";
            }
            if (downLeft > 0 || upLeft > 0) {
                move(3);
                return "Moved.";
            }
            if (m_row == m_arena->rows()) {//if cornered.
                if (m_col == 1) {
                    move(3);
                    return "Moved.";
                }
                if (m_col == m_arena->cols()) {
                    move(2);
                    return "Moved.";
                }
                move(2);
                return "Moved.";
            }//..
                
            move(1);
            return "Moved.";
        }
        else if (right > 0) {
            if (upLeft > 0 || upRight > 0) {
                move(1);
                return "Moved.";
            }
            if (downLeft > 0 || downRight > 0) {
                move(0);
                return "Moved.";
            }
            if (m_col == 1){ //if cornered.
                if (m_row == 1) {
                    move(1);
                    return "Moved.";
                }
                if (m_row == m_arena->rows()) {
                    move(0);
                    return "Moved.";
                }
                move(0);
                return "Moved.";
            }//..
            move(2);
            return "Moved.";
        }
        else if (left > 0) {
            if (upRight > 0 || upLeft > 0) {
                move(1);
                return "Moved.";
            }
            if (downRight > 0 || downLeft > 0) {
                move(0);
                return "Moved.";
            }
            if (m_col == m_arena->cols()) {
                if (m_row == 1) {
                    move(1);
                    return "Moved.";
                }
                if (m_row == m_arena->rows()) {
                    move(0);
                    return "Moved.";
                }
                if (down > 0) {
                    move(0);
                    return "Moved";
                }
                if (up > 0) {
                    move(1);
                    return "Moved";
                }
                move(0);
                return "Moved";
            }
            move(3);
            return "Moved.";
        }
    case 2: // when 2 robots are around the player.
        if (up > 0 && down > 0) {
            if (upRight > 0 || downRight > 0) {
                move(2);
                return "Moved.";
            }
            if (upLeft > 0 || downLeft > 0) {
                move(3);
                return "Moved.";
            }
            if (m_col == 1) {
                move(3);
                return "Moved.";
            }
            else {
                move(2);
                return "Moved.";
            }
        }
        if (up > 0 && right > 0) {
            if (upLeft > 0) {
                move(1);
                return "Moved.";
            }
            if (downRight > 0) {
                move(2);
                return "Moved.";
            }
            if (m_row == m_arena->rows()) {
                move(2);
                return "Moved.";
            }
            else {
                move(1);
                return "Moved.";
            }
        }
        if (up > 0 && left > 0) {
            if (upRight > 0) {
                move(1);
                return "Moved.";
            }
            if (downLeft > 0) {
                move(3);
                return "Moved.";
            }
            if (m_row == m_arena->cols()) {
                move(3);
                return "Moved.";
            }
            else {
                move(1);
                return "Moved.";
            }
        }
        if (down > 0 && left > 0) {
            if (upLeft > 0) {
                move(3);
                return "Moved.";
            }
            if (downRight > 0) {
                move(0);
                return "Moved.";
            }
            if (m_col == m_arena->cols()) {
                move(0);
                return "Moved.";
            } 
            else {
                move(3);
                return "Moved.";
            }
        }
        if (down > 0 && right > 0) {
            if (upRight > 0) {
                move(2);
                return "Moved.";
            }
            if (downLeft > 0) {
                move(0);
                return "Moved.";
            }
            if (m_col == 1) {
                move(0);
                return "Moved.";
            }
            else {
                move(2);
                return "Moved.";
            }

        }
        if (right > 0 && left > 0) {
            if (upLeft > 0 || upRight > 0) {
                move(1);
                return "Moved.";
            }
            if (downRight > 0 || downLeft > 0) {
                move(0);
                return "Moved.";
            }
            if (m_row == m_arena->rows()) {
                move(0);
                return "Moved.";
            }
            else {
                move(1);
                return "Moved.";
            }
        }
    case 3: // when 3 robots are around the player.
        if (up > 0 && down > 0 && right > 0) {
            move(2);
            return "Moved.";
        }
        if (up > 0 && down > 0 && left > 0) {
            move(3);
            return "Moved.";
        }
        if (down > 0 && left > 0 && right > 0) {
            move(0);
            return "Moved.";
        }
        if (up > 0 && left > 0 && right > 0) {
            move(1);
            return "Moved.";
        }
                
    }
    if (downRight > 0) {
        if (m_row == 1) {
            if (m_col == 1) {
                stand();
                return "Stood.";
            }
        }
        if (downLeft > 0) {
            move(0);
            return "Moved.";
        }
        if (upRight > 0) {
            move(2);
            return "Moved.";
        }
        move(0);
        return "Moved.";
    }
    if (upRight > 0) {
        if (m_col == 1) {
            if (m_row = m_arena->rows()) {
                stand();
                return "Stood";
            }
        }
        if (upLeft > 0) {
            move(1);
            return "Moved.";
        }
        move(2);
        return "Moved.";
    }
    if (upLeft > 0) {
        if (downLeft > 0) {
            move(3);
            return "Moved.";
        }
        move(1);
        return "Moved.";
    }

    
    //shooting when no robots are near.
    for (int i = 2; i <= 5; i++) {
        if (m_arena->nRobotsAt(m_row + i, m_col) > 0) {
           
            if (shoot(1))
                return "Shot and hit!";
            else
                return "Shot and missed!";
        }
        else if (m_arena->nRobotsAt(m_row - i, m_col) > 0) {
           
            if (shoot(0))
                return "Shot and hit!";
            else
                return "Shot and missed!";
        }
        else if (m_arena->nRobotsAt(m_row, m_col + i) > 0) {
            
            if (shoot(3))
                return "Shot and hit!";
            else
                return "Shot and missed!";
        }
        else if (m_arena->nRobotsAt(m_row, m_col - i) > 0) {
            
            if (shoot(2))
                return "Shot and hit!";
            else
                return "Shot and missed!";
        }
    }
    
    move(rand() % 4);
    return "Moved.";


   
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;
    switch (dir)
    {
    case UP:
        
        if (m_row - 1 > 0)
            m_row--;
        break;
    case DOWN:
        if (m_row + 1 <= m_arena->rows())
            m_row++;
        break;
    case LEFT:
        if (m_col - 1 > 0)
            m_col--;
        break;
    case RIGHT:
        if (m_col + 1 <= m_arena->cols())
            m_col++;
        
        break;
    }
}

bool Player::shoot(int dir)
{
    m_age++;

    
    switch (dir)
    {
    case UP:
        for (int i = 1; i <= 5; i++) {
            if (m_arena->nRobotsAt(m_row + i, m_col) > 0) {

                if (rand() % 3 == 0)
                    return false;
                else {
                    m_arena->damageRobotAt(m_row + i, m_col);
                    return true;
                }
            }
        }
    case DOWN:
        for (int i = 1; i <= 5; i++) {
            if (m_arena->nRobotsAt(m_row - i, m_col) > 0) {
                if (rand() % 3 == 0)
                    return false;
                else {
                    m_arena->damageRobotAt(m_row - i, m_col);
                    return true;
                }
            }
        }
    case LEFT:
        for (int i = 1; i <= 5; i++) {
            if (m_arena->nRobotsAt(m_row, m_col - i) > 0) {
                if (rand() % 3 == 0)
                    return false;
                else {
                    m_arena->damageRobotAt(m_row, m_col - i);
                    return true;
                }
            }
        }
    case RIGHT:
        for (int i = 1; i <= 5; i++) {
            if (m_arena->nRobotsAt(m_row, m_col + i) > 0) {
                if (rand() % 3 == 0)
                    return false;
                else {
                    m_arena->damageRobotAt(m_row, m_col + i);
                    return true;
                }
            }
        }
     default: return false;
    }
     
}

bool Player::isDead() const
{
    
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}
