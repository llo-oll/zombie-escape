#include <IntVec.h>
#include <Game.h>
#include <iostream>
#include <thread>
#include <ncurses.h>


IntVec decodeInput(int c) {
    switch (c) {
        case 'k':
        case 'w':
            return IntVec(0, -1);
        case 'u':
        case 'e':
            return IntVec(1, -1);
        case 'l':
        case 'd':
            return IntVec(1, 0);
        case 'n':
        case 'c':
            return IntVec(1, 1);
        case 'j':
        case 'x':
        case 's':
            return IntVec(0, 1);
        case 'b':
        case 'z':
            return IntVec(-1, 1);
        case 'h':
        case 'a':
            return IntVec(-1, 0);
        case 'y':
        case 'q':
            return IntVec(-1, -1);
        default:
            return IntVec(0, 0);
    }
}

void display(Game &game) {
    clear();
    refresh();
    move(0, 0);
    printw(game.toString().c_str());
    refresh();
}


void initCurses() {
    //init curses
    initscr();
    //switch terminal to unbuffered mode i.e. reads characters as soon as they are typed.
    raw();
    //Don't echo typed characters
    noecho();
}

void sleep(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

bool playLevel(const IntVec &size, int numzombies) {
    //TODO tidy up this logic
    Game game{Game(size, numzombies)};
    while (!game.isGameOver()) {
        for (int i = 0; i <= 2; ++i) {
            display(game);
            int c = getch();
            game.movePlayer(decodeInput(c));
            if (game.isWon()) break;
        }
        if (game.isWon()) break;
        game.moveZombies();
    }
    display(game);
    sleep(1);
    return game.isLost();
}


int main() {
    initCurses();

    int maxZombies = 10;
    for (int numZs = 5; numZs <= maxZombies; ++numZs) {
        bool isLost = playLevel(IntVec(10, 10), numZs);
        if (isLost) {
            clear();
            move(0, 0);
            printw(").: L O S E R :.(");
            refresh();
            sleep(2);
            break;
        }
        if (numZs == maxZombies) {
            clear();
            move(0, 0);
            printw("(; W.I.N.N.E.R ;)");
            refresh();
            sleep(2);
        }
    }

    //exit curses
    endwin();
}

