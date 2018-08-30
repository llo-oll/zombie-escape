#include <iostream>
#include "Game.h"
#include "Board.h"

Game::Game(IntVec roomSize, int numOfZombies)
    :board {Board(roomSize)},
     gameLost{false},
     roomSize {roomSize},
     gameWon {false},
     zombieIds {std::vector<int>(static_cast<unsigned long>(numOfZombies))}
{
    playerId = board.add(IntVec(0,0));
    exitId = board.add(roomSize - IntVec(1,1));
    for (int i = 0; i < numOfZombies; ++i) {
        IntVec v = IntVec(std::rand() % roomSize.x, std::rand() % roomSize.y);
        zombieIds[i] = board.add(v);
        if (zombieIds[i] == -1) {
            --i;
        }
    }
}

Game::~Game() = default;

void Game::movePlayer(IntVec move) {
    if (isGameOver()) return;

    IntVec pos = board.find(playerId);
    IntVec newPos = pos + move;
    if (board.isInBounds(newPos)) {
        int squareId = board.peak(newPos);
        if (squareId == -1) {
            board.move(playerId, newPos);
        }
        else if (squareId == exitId) {
            board.move(playerId, newPos);
            gameWon = true;
        }
    }
}

void Game::moveZombies() {
    if (isGameOver()) return;
    //for each zombie
    for (int id : zombieIds) {
    //find direction to the player
        IntVec playerPos = board.find(playerId);
        IntVec zombPos = board.find(id);
        IntVec move = (playerPos - zombPos).unitise();
        IntVec newZombPos = zombPos + move;
        int peakId = board.peak(newZombPos);

        if (peakId != -1 && peakId != playerId) continue;
        if (! board.isInBounds(newZombPos)) continue;

        board.move(id, newZombPos);
        if (playerPos == newZombPos) {
            gameLost = true;
            return;
        }
    }
}

std::string Game::toString() const {
     return board.toString();
}

bool Game::isGameOver() const {
    return gameLost || gameWon;
}

bool Game::isWon() const {
    return gameWon;
}

bool Game::isLost() const {
    return gameLost;
}
