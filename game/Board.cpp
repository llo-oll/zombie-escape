#include <iosfwd>
#include <sstream>
#include <iostream>
#include "Board.h"

Board::Board(Vec size)
    //TODO add deconstructor.
    :idRecycleList {nullptr},
    maxPieces {size.x * size.y},
    pieceArray {new Vec*[maxPieces]},
    pieceArraySize {0},
    size {size},
    squareMatrix {new int*[size.x]}
{
    for (int i = 0; i < size.x; ++i) {
       squareMatrix[i] = new int[size.y];
       for (int j = 0; j < size.y; ++j) {
           squareMatrix[i][j] = -1;
       }
    }
}

Board::~Board() {
    while (idRecycleList != nullptr){
        idList* tmp = idRecycleList;
        idRecycleList = idRecycleList->next;
        delete tmp;
    }

    for (int i = 0; i < pieceArraySize; ++i) {
        if (pieceArray[i] == nullptr) {
            delete pieceArray[i];
        }
    }
    delete[] pieceArray;

    for (int x = 0; x < size.x; ++x) {
        delete [] squareMatrix[x];
    }
}


/*
 * Places a piece at the given position.
 * Returns an int id which can be used to refer to the piece in future.
 * If there is already a piece at the given position the new piece is ignored and the method returns -1.
 * Throws an out of range exception if the position is outside the board.
 */
int Board::add(Vec position) {
    //If position is out of bounds throw out_of_range exception.
    checkInBounds(position);
    //If square is occupied return -1.
    if (squareMatrix[position.x][position.y] != -1) {
        return -1;
    }
    //otherwise get a new id and place it on the board.
    int id = getNextPieceId();
    pieceArray[id] = new Vec(position.x, position.y);
    squareMatrix[position.x][position.y] = id;
    return id;
}



/*
 * Checks the board for consistency:
 *  There is only one of each id in the 2 dimensional representation (squareMatrix).
 *  Each id with a position in pieceArray appears at the corresponding position in the 2d representation.
 *  Each id in the squareMatrix has its position in pieceArray.
 */
bool Board::checkConsistency() {
    //TODO implement this
    throw std::logic_error("Not implemented");
    return false;
}

/*
 * Throws a logic_error if the id doesn't refer to a piece on the board.
 */
void Board::checkIdExists(int id) {
    if (id < 0 || id >= maxPieces || pieceArray[id] == nullptr) {
        std::stringstream errorMessage;
        errorMessage << "There is no piece with id " << id << " on the board";
        throw std::logic_error{errorMessage.str()};
    }
}

/*
 * Throws an exception if the given position is outside the board.
 */
void Board::checkInBounds(Vec position) {
    if (position.x < 0 || position.y < 0
        || position.x >= size.x || position.y >= size.y) {
        std::stringstream errorMessage;
        errorMessage << "Position (" << position.x << ", " << position.y << ") out of range of board size (" << size.x << ", " << size.y << ")";
        throw std::out_of_range{errorMessage.str()};
    }
}

Vec Board::find(int id) {
    checkIdExists(id);
    return *pieceArray[id];
}

/*
 * The next available id.
 */
int Board::getNextPieceId() {
    int id;
    if (idRecycleList != nullptr) {
        //TODO deal with this case
    } else {
        id = pieceArraySize++;
    }
    return id;
}

const Vec &Board::getSize() const {
    return size;
}
/*
 * Moves the piece with the given id from where it is to the given position.
 * If there is already a piece in the new position that piece is removed from the board and its id returned.
 * Otherwise, -1 is returned.
 * Throws a logic_error if there is no piece matching the given piece id.
 * Throws an out_of_range exception if the given position is outside the board.
 */
int Board::move(int id, Vec position) {
    checkInBounds(position);
    checkIdExists(id);

    int otherId = peak(position);
    if (otherId != -1) {
        remove(otherId);
    }

    remove(id);
    squareMatrix[position.x][position.y] = id;
    delete pieceArray[id];
    pieceArray[id] = new Vec(position);
    return false;
}

/*
 * Returns either the id of the piece at the given position or -1 if there is no such piece.
 * Throws an out of bounds exception if the position is outside the board.
 */
int Board::peak(Vec position) {
    checkInBounds(position);
    int id = squareMatrix[position.x][position.y];
    return id;
}

/*
 * Removes the piece with the given id from the board.
 * Throws an invalid_argument exception if the id doesn't exist.
 */
void Board::remove(int id) {
    //TODO recycle old id with idList
    checkIdExists(id);
    Vec* pos = &*pieceArray[id];
    pieceArray[id] = nullptr;
    squareMatrix[pos->x][pos->y] = -1;
    delete pos;
}

std::string Board::toString() {
    std::stringstream ss;
    for (int y = 0; y < size.y; ++y) {
        for (int x = 0; x < size.x; ++x) {
            int square = squareMatrix[x][y];
            ss << (square == -1 ? "- ": std::to_string(square) + " ");
        }
        ss << '\n';
    }
    return ss.str();
}



