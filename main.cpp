#include <IntVec.h>
#include <Game.h>
#include <iostream>
#include <thread>
#include <ncurses.h>


IntVec decodeInput(char c) {
    switch (c) {
        case 'k': return IntVec( 0,-1);
        case 'u': return IntVec( 1,-1);
        case 'l': return IntVec( 1, 0);
        case 'm': return IntVec( 1, 1);
        case 'j': return IntVec( 0, 1);
        case 'n': return IntVec(-1, 1);
        case 'h': return IntVec(-1, 0);
        case 'y': return IntVec(-1,-1);
        default: return IntVec(0,0);
    }
}

void display(Game& game) {
    std::cout << game.toString() << std::endl;
}

void playerMove(Game& game) {
    char c = getchar();
    do {
        game.movePlayer(decodeInput(c));
        c = getchar();
    } while(c != '\n');
}

int main() {
    Game game {Game(IntVec(10,10), 4)};
    while (!game.isGameOver()) {
        display(game);
        playerMove(game);
        display(game);
        playerMove(game);
        game.moveZombies();
    }
    display(game);
}

