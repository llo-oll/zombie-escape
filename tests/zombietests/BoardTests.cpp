#include "Board.h"
#include "IntVec.h"
#include <gtest/gtest.h>


TEST(BoardTests, outOfBoundsAddPiece) {
    Board board {Board(IntVec(143,77))};
    EXPECT_THROW(board.add(IntVec(-1, 7)), std::out_of_range);
    EXPECT_THROW(board.add(IntVec(94, -1)), std::out_of_range);
    EXPECT_THROW(board.add(IntVec(3, 77)), std::out_of_range);
    EXPECT_THROW(board.add(IntVec(143, 3)), std::out_of_range);
    EXPECT_TRUE(board.checkConsistency());
}

TEST(BoardTests, inBoundsAddPiece) {
    Board board {Board(IntVec(33, 10))};
    EXPECT_NO_THROW(board.add(IntVec(0, 9)));
    EXPECT_NO_THROW(board.add(IntVec(32, 0)));
    EXPECT_TRUE(board.checkConsistency());
}

TEST(BoardTests, canAddPiece) {
    Board board {Board(IntVec(33, 50))};
    int id = board.add(IntVec(10, 10));
    EXPECT_NE(-1, id);
    EXPECT_TRUE(board.checkConsistency());
}

TEST(BoardTests, canPeakPiece) {
    Board board {Board(IntVec(20,20))};
    IntVec pos {IntVec(11,4)};
    int id = board.add(pos);
    EXPECT_EQ(id, board.peak(pos));
    EXPECT_TRUE(board.checkConsistency());
}

TEST(BoardTests, doesntAddPieceInSamePlace) {
    Board board {Board(IntVec(21, 50))};
    int id = board.add(IntVec(3, 2));
    EXPECT_EQ(-1, board.add(IntVec(3, 2)));
    EXPECT_TRUE(board.checkConsistency());
}

TEST(BoardTests, canRemovePiece) {
    Board board {Board(IntVec(11, 12))};
    int id = board.add(IntVec(3,4));
    board.remove(id);
    EXPECT_THROW(board.find(id), std::logic_error);
    EXPECT_TRUE(board.checkConsistency());
}

TEST(BoardTests, canMovePiece) {
    Board board {Board(IntVec(10, 5))};
    int id = board.add(IntVec(0, 0));
    IntVec moveTo = IntVec(9, 4);
    board.move(id, moveTo);
    EXPECT_EQ(moveTo, board.find(id));
    EXPECT_TRUE(board.checkConsistency());
}

TEST(BoardTests, canZeroMovePiece) {
    Board board {Board(IntVec(10, 10))};
    IntVec pos = IntVec(3,2);
    int id = board.add(pos);
    board.move(id, pos);
    EXPECT_EQ(pos, board.find(id));
}

TEST(BoardTests, canCapture) {
    Board board {Board(IntVec(10, 5))};
    int id = board.add(IntVec(0, 0));
    IntVec capturePosition = IntVec(4,4);
    int id2 =  board.add(capturePosition);
    board.move(id, capturePosition);
    EXPECT_EQ(capturePosition, board.find(id));
    EXPECT_THROW(board.find(id2), std::logic_error);
    EXPECT_TRUE(board.checkConsistency());
}


TEST(BoardTests, recycleID) {
    Board board{Board(IntVec(10, 10))};
    int idToRecycle = board.add(IntVec(5, 5));
    int another = board.add(IntVec(3,6));
    int anId = board.add(IntVec(4,2));
    board.remove(idToRecycle);
    board.remove(another);
    int anOldId = board.add(IntVec(2,2));
    int otherOldId = board.add(IntVec(3,1));
    EXPECT_TRUE((idToRecycle == anOldId && another == otherOldId) || (idToRecycle == otherOldId && another == anOldId));
    EXPECT_TRUE(board.checkConsistency());
}
