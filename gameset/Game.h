

#ifndef ZOMBIE_ESCAPE_GAME_H
#define ZOMBIE_ESCAPE_GAME_H


#include <vector>
#include "IntVec.h"
#include "Board.h"

class Game {
public:
    Game(IntVec roomSize, int numOfZombies);

    ~Game();

    void movePlayer(IntVec direction);

    void moveZombies();

    std::string toString() const;

    bool isGameOver() const;

    bool isLost() const;

    bool isWon() const;

private:
    Board board;
    int exitId;
    bool gameLost;
    int playerId;
    IntVec roomSize;
    std::vector<int> zombieIds;
    bool gameWon;
};


#endif //ZOMBIE_ESCAPE_GAME_H
