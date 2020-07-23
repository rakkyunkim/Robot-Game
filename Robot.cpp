#include "Robot.h"
#include "Arena.h"
#include <iostream>
using namespace std;
Robot::Robot(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A robot must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
            << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_isDamaged = false;
    m_isDead = false;
}

int Robot::row() const
{
    return m_row;
}

int Robot::col() const
{
   
    return m_col;  
}
bool Robot::Damage()
{
    m_isDamaged = true;
    return m_isDamaged;
}
bool Robot::Destroy() 
{
    m_isDead = true;
    return m_isDead;
}
bool Robot::isDamaged()
{
    return m_isDamaged;
}
bool Robot::isDead()
{
    return m_isDead;
}
void Robot::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    switch (rand() % 4)
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

bool Robot::takeDamageAndLive()
{
    if (m_isDamaged) {
        return false;
    }
    m_isDamaged = true;
    return true;
    
}
