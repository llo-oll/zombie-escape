#include <iosfwd>
#include <sstream>
#include <iostream>
#include "Board.h"

Board::Board(IntVec size)
        : idRecycleList{nullptr},
          maxPieces{size.x * size.y},
          pieceArray{new IntVec *[maxPieces]},
          pieceArraySize{0},
          size{size},
          squareMatrix{new int *[size.x]} {
    for (int i = 0; i < size.x; ++i) {
        squareMatrix[i] = new int[size.y];
        for (int j = 0; j < size.y; ++j) {
            squareMatrix[i][j] = -1;
        }
    }
}

Board::~Board() {
    while (idRecycleList != nullptr) {
        idList *tmp = idRecycleList;
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
        delete[] squareMatrix[x];
    }
    delete[] squareMatrix;
}

/**
 * Places a piece at the given position.
 * Returns an int id which can be used to refer to the piece in future.
 * If there is already a piece at the given position the new piece is ignored and the method returns -1.
 * Throws an out of range exception if the position is outside the board.
 * @param position the position at which to place the piece on the board.
 * @return the id used when refering to the piece that was just placed or -1 if there was already a piece at the given position.
 */
int Board::add(IntVec position) {
    //If position is out of bounds throw out_of_range exception.
    checkInBounds(position);
    //If square is occupied return -1.
    if (squareMatrix[position.x][position.y] != -1) {
        return -1;
    }
    //otherwise get a new id and place it on the board.
    int id = getNextPieceId();
    pieceArray[id] = new IntVec(position.x, position.y);
    squareMatrix[position.x][position.y] = id;
    return id;
}

/**
 * Useful for testing.
 *
 * Checks the board for consistency:
 *  There is only one of each id in the 2 dimensional representation (squareMatrix).
 *  Each id with a position in pieceArray appears at the corresponding position in the 2d representation.
 *  Each id in the squareMatrix has its position in pieceArray.
 * @return true if the board is in a consistent state false otherwise.
 */
bool Board::checkConsistency() const {
    //Check there is only one of each id in squareMatrix.
    bool idSet[pieceArraySize];
    for (int i = 0; i < pieceArraySize; ++i) {
        idSet[i] = false;
    }
    for (int x = 0; x < size.x; ++x) {
        for (int y = 0; y < size.y; ++y) {
            int id = squareMatrix[x][y];
            if (id != -1) {
                if (idSet[id]) {
                    return false;
                }
                idSet[id] = true;
            }
        }
    }

    //Each id with a position in pieceArray appears at the corresponding position in squareMatrix.
    for (int i = 0; i < pieceArraySize; ++i) {
        if (pieceArray[i] != nullptr) {
            IntVec pos = *pieceArray[i];
            if (squareMatrix[pos.x][pos.y] != i) {
                return false;
            }
        }
    }

    //Each id in the squareMatrix has its position in pieceArray.
    for (int x = 0; x < size.x; ++x) {
        for (int y = 0; y < size.y; ++y) {
            int id = squareMatrix[x][y];
            if (id != -1) {
                if (pieceArray[id] == nullptr || *pieceArray[id] != IntVec(x, y)) {
                    return false;
                }
            }
        }
    }
    return true;
}

/**
 * Throws a logic_error if the id doesn't refer to a piece on the board.
 */
void Board::checkIdExists(int id) const {
    if (id < 0 || id >= maxPieces || pieceArray[id] == nullptr) {
        std::stringstream errorMessage;
        errorMessage << "There is no piece with id " << id << " on the board";
        throw std::logic_error{errorMessage.str()};
    }
}

/**
 * Throws an exception if the given position is outside the board.
 * @param position
 */
void Board::checkInBounds(IntVec position) const {
    if (position.x < 0 || position.y < 0
        || position.x >= size.x || position.y >= size.y) {
        std::stringstream errorMessage;
        errorMessage << "Position (" << position.x << ", " << position.y << ") out of range of board size (" << size.x
                     << ", " << size.y << ")";
        throw std::out_of_range{errorMessage.str()};
    }
}

/**
 * Throws a logic error if the piece doesn't exist
 * @param id the id of the piece to find
 * @return the position of the piece
 */
IntVec Board::find(int id) const {
    checkIdExists(id);
    return *pieceArray[id];
}

/**
 * @return The next available id.
 */
int Board::getNextPieceId() {
    int id;
    if (idRecycleList != nullptr) {
        id = idRecycleList->id;
        idList *tmp = idRecycleList;
        idRecycleList = idRecycleList->next;
        delete tmp;
    } else {
        id = pieceArraySize++;
    }
    return id;
}

const IntVec &Board::getSize() const {
    return size;
}

bool Board::isInBounds(IntVec position) const {
    return position.x >= 0 && position.y >= 0 && position.x < size.x && position.y < size.y;
}

/**
 * Moves the piece with the given id from where it is to the given position.
 * If there is already a piece in the new position that piece is removed from the board and its id returned.
 * Otherwise, -1 is returned.
 * Throws a logic_error if there is no piece matching the given piece id.
 * Throws an out_of_range exception if the given position is outside the board.
 * @param id the piece to move
 * @param position the position to move to.
 * @return the id of any piece that was already at the position or -1 if there was no piece.
 */
int Board::move(int id, IntVec position) {
    checkInBounds(position);
    checkIdExists(id);

    int otherId = peak(position);
    if (otherId == id) return id;
    if (otherId != -1) remove(otherId);

    remove(id);
    squareMatrix[position.x][position.y] = id;
    delete pieceArray[id];
    pieceArray[id] = new IntVec(position);
    return otherId;
}

/**
 * Throws an out of bounds exception if the position is outside the board.
 * @param position the position to peak
 * @return the id of the piece at the position or -1 if there is no piece.
 */
int Board::peak(IntVec position) const {
    checkInBounds(position);
    int id = squareMatrix[position.x][position.y];
    return id;
}

/**
 * Adds the id to recyclelist.
 * @param id
 */
void Board::recycleId(int id) {
    idRecycleList = new idList{id, (idRecycleList == nullptr ? nullptr : idRecycleList)};
}

/**
 * Removes the piece with the given id from the board.
 * Throws an invalid_argument exception if the id doesn't exist.
 * @param id
 */
void Board::remove(int id) {
    checkIdExists(id);
    IntVec *pos = &*pieceArray[id];
    pieceArray[id] = nullptr;
    squareMatrix[pos->x][pos->y] = -1;
    recycleId(id);
    delete pos;
}

std::string Board::toString() const {
    std::stringstream ss;
    for (int y = 0; y < size.y; ++y) {
        for (int x = 0; x < size.x; ++x) {
            int square = squareMatrix[x][y];
            ss << (square == -1 ? "- " : std::to_string(square) + " ");
        }
        ss << '\n';
    }
    return ss.str();
}





