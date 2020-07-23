#ifndef ROBOT_H
#define ROBOT_H
class Robot
{
public:
    // Constructor
    Robot(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDamaged();
    bool isDead();

    // Mutators
    void move();
    bool takeDamageAndLive();
    bool Damage();
    bool Destroy();
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_isDamaged;
    bool   m_isDead;
    
};
#endif

