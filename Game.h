class Arena;
#ifndef GAME_H
#define GAME_H
class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();

    // Mutators
    void play();

private:
    Arena* m_arena;
};
#endif
