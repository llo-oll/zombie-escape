#ifndef LEARN_CPP_ROOM_H
#define LEARN_CPP_ROOM_H


#include "IntVec.h"
#include <string>


class Board {
public:
    explicit Board(IntVec size);

    ~Board();

    std::string toString() const;

    const IntVec &getSize() const;

    int add(IntVec position);

    bool checkConsistency() const;

    IntVec find(int id) const;

    bool isInBounds(IntVec position) const;

    int move(int id, IntVec position);

    int peak(IntVec position) const;

    void remove(int id);


private:
    struct idList {
        int id;
        idList *next;
    };
    idList *idRecycleList;
    const int maxPieces;
    //Maps piece ids to vectors representing positions. A 1d array of pointers to Vecs.
    IntVec **pieceArray;
    int pieceArraySize;
    const IntVec size;
    //Maps positions to piece ids. A 2d array of ints.
    int **squareMatrix;

    void checkIdExists(int id) const;

    void checkInBounds(IntVec position) const;

    int getNextPieceId();

    void recycleId(int id);
};


#endif //LEARN_CPP_ROOM_H
