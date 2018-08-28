#include <IntVec.h>
#include <Game.h>
#include <iostream>
#include <thread>
#include <ncurses.h>


IntVec decodeInput(int c) {
    switch (c) {
        case 'w': return IntVec( 0,-1);
        case 'e': return IntVec( 1,-1);
        case 'd': return IntVec( 1, 0);
        case 'x':
        case 'c': return IntVec( 1, 1);
        case 's': return IntVec( 0, 1);
        case 'z': return IntVec(-1, 1);
        case 'a': return IntVec(-1, 0);
        case 'q': return IntVec(-1,-1);
        default: return IntVec(0,0);
    }
}

void display(Game& game) {
    clear();
    refresh();
    move(0, 0);
    printw(game.toString().c_str());
    refresh();
}

void playerMove(Game& game) {
    int c = getch();
    game.movePlayer(decodeInput(c));
}

void initCurses() {
    //init curses
    initscr();
    //switch terminal to unbuffered mode i.e. reads characters as soon as they are typed.
    raw();
    //Don't echo typed characters
    noecho();
}


int main() {
    initCurses();

    Game game {Game(IntVec(10,10), 4)};
    while (!game.isGameOver()) {
        display(game);
        playerMove(game);
        display(game);
        playerMove(game);
        display(game);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        game.moveZombies();
    }
    display(game);
    std::this_thread::sleep_for(std::chrono::seconds(4));

    //exit curses
    endwin();
}

