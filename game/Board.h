//
// Created by ben on 20/08/18.
//

#ifndef LEARN_CPP_ROOM_H
#define LEARN_CPP_ROOM_H


#include "Vec.h"
#include <string>



class Board {
public:
    Board(Vec size);
    ~Board();
    std::string toString();
    const Vec &getSize() const;
    int add(Vec position);
    bool checkConsistency();
    Vec find(int id);
    int move(int id, Vec position);
    int peak(Vec position);
    void remove(int id);


private:
    struct idList {
        int id;
        idList* next;
    };
    idList* idRecycleList;
    const int maxPieces;
    //Maps piece ids to vectors representing positions. A 1d array of pointers to Vecs.
    Vec** pieceArray;
    int pieceArraySize;
    const Vec size;
    //Maps positions to piece ids. A 2d array of ints.
    int** squareMatrix;

    void checkIdExists(int id);
    void checkInBounds(Vec position);
    int getNextPieceId();
    void recycleId(int id);
};


#endif //LEARN_CPP_ROOM_H
