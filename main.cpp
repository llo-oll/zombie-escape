#include <Board.h>
#include <iostream>

int main() {
    Board board {Board(Vec(10,5))};
    board.add(Vec(2,4));
    int x2 = board.add(Vec(3,1));
    Vec v2 = board.find(x2);
    std::cout << board.toString() ;
}

