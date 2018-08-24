#include "Board.h"
#include "Vec.h"
#include <gtest/gtest.h>


TEST(BoardTests, outOfBoundsAddPiece) {
    Board board {Board(Vec(143,77))};
    EXPECT_THROW(board.add(Vec(-1, 7)), std::out_of_range);
    EXPECT_THROW(board.add(Vec(94, -1)), std::out_of_range);
    EXPECT_THROW(board.add(Vec(3, 77)), std::out_of_range);
    EXPECT_THROW(board.add(Vec(143, 3)), std::out_of_range);

}

TEST(BoardTests, inBoundsAddPiece) {
    Board board {Board(Vec(33, 10))};
    EXPECT_NO_THROW(board.add(Vec(0, 9)));
    EXPECT_NO_THROW(board.add(Vec(32, 0)));
}

TEST(BoardTests, canAddPiece) {
    Board board {Board(Vec(33, 50))};
    int id = board.add(Vec(10, 10));
    EXPECT_NE(-1, id);
}

TEST(BoardTests, canPeakPiece) {
    Board board {Board(Vec(20,20))};
    Vec pos {Vec(11,4)};
    int id = board.add(pos);
    EXPECT_EQ(id, board.peak(pos));
}

TEST(BoardTests, doesntAddPieceInSamePlace) {
    Board board {Board(Vec(21, 50))};
    int id = board.add(Vec(3, 2));
    EXPECT_EQ(-1, board.add(Vec(3, 2)));
}

TEST(BoardTests, canRemovePiece) {
    Board board {Board(Vec(11, 12))};
    int id = board.add(Vec(3,4));
    board.remove(id);
    EXPECT_THROW(board.find(id), std::logic_error);
}

TEST(BoardTests, canMovePiece) {
    Board board {Board(Vec(10, 5))};
    int id = board.add(Vec(0, 0));
    Vec moveTo = Vec(9, 4);
    board.move(id, moveTo);
    EXPECT_EQ(moveTo, board.find(id));
}

TEST(BoardTests, canCapture) {
    Board board {Board(Vec(10, 5))};
    int id = board.add(Vec(0, 0));
    Vec capturePosition = Vec(4,4);
    int id2 =  board.add(capturePosition);
    board.move(id, capturePosition);
    EXPECT_EQ(capturePosition, board.find(id));
    EXPECT_THROW(board.find(id2), std::logic_error);
}
