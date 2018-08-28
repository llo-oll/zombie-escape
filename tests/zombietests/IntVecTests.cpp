#include "IntVec.h"
#include <gtest/gtest.h>

TEST(IntVecTests, unitise) {
    //IntVec(1,0)
    EXPECT_EQ(IntVec(1,0), IntVec(1,0).unitise());
    EXPECT_EQ(IntVec(1,0), IntVec(4,1).unitise());
    EXPECT_EQ(IntVec(1,0), IntVec(7,-1).unitise());
    EXPECT_EQ(IntVec(1,0), IntVec(9,0).unitise());
    EXPECT_EQ(IntVec(1,0), IntVec(12,-5).unitise());
    //IntVec(1,1)
    EXPECT_EQ(IntVec(1,1), IntVec(1,1).unitise());
    EXPECT_EQ(IntVec(1,1), IntVec(3,2).unitise());
    EXPECT_EQ(IntVec(1,1), IntVec(3,5).unitise());
    EXPECT_EQ(IntVec(1,1), IntVec(11,6).unitise());
    EXPECT_EQ(IntVec(1,1), IntVec(8,7).unitise());
    //IntVec(0,1)
    EXPECT_EQ(IntVec(0,1), IntVec(0,1).unitise());
    EXPECT_EQ(IntVec(0,1), IntVec(1,4).unitise());
    EXPECT_EQ(IntVec(0,1), IntVec(-1,7).unitise());
    EXPECT_EQ(IntVec(0,1), IntVec(0,9).unitise());
    EXPECT_EQ(IntVec(0,1), IntVec(-5,12).unitise());
    //IntVec(-1,1)
    EXPECT_EQ(IntVec(-1,1), IntVec(-1,1).unitise());
    EXPECT_EQ(IntVec(-1,1), IntVec(-3,2).unitise());
    EXPECT_EQ(IntVec(-1,1), IntVec(-3,5).unitise());
    EXPECT_EQ(IntVec(-1,1), IntVec(-11,6).unitise());
    EXPECT_EQ(IntVec(-1,1), IntVec(-8,7).unitise());
    //IntVec(-1,0)
    EXPECT_EQ(IntVec(-1,0), IntVec(-1,0).unitise());
    EXPECT_EQ(IntVec(-1,0), IntVec(-4,1).unitise());
    EXPECT_EQ(IntVec(-1,0), IntVec(-7,-1).unitise());
    EXPECT_EQ(IntVec(-1,0), IntVec(-9,0).unitise());
    EXPECT_EQ(IntVec(-1,0), IntVec(-12,-5).unitise());
    //IntVec(-1,-1)
    EXPECT_EQ(IntVec(-1,-1), IntVec(-1,-1).unitise());
    EXPECT_EQ(IntVec(-1,-1), IntVec(-3,-2).unitise());
    EXPECT_EQ(IntVec(-1,-1), IntVec(-3,-5).unitise());
    EXPECT_EQ(IntVec(-1,-1), IntVec(-11,-6).unitise());
    EXPECT_EQ(IntVec(-1,-1), IntVec(-8,-7).unitise());
    //IntVec(0,-1)
    EXPECT_EQ(IntVec(0,-1), IntVec(0,-1).unitise());
    EXPECT_EQ(IntVec(0,-1), IntVec(1,-4).unitise());
    EXPECT_EQ(IntVec(0,-1), IntVec(-1,-7).unitise());
    EXPECT_EQ(IntVec(0,-1), IntVec(0,-9).unitise());
    EXPECT_EQ(IntVec(0,-1), IntVec(-5,-12).unitise());

    EXPECT_EQ(1, IntVec(4,2).unitise().x);
    EXPECT_EQ(1, IntVec(4,8).unitise().y);
    EXPECT_EQ(1, IntVec(-2,4).unitise().y);
    EXPECT_EQ(-1, IntVec(-2,1).unitise().x);
    EXPECT_EQ(-1, IntVec(-4,-2).unitise().x);
    EXPECT_EQ(-1, IntVec(-1,-2).unitise().y);
    EXPECT_EQ(-1, IntVec(1,-2).unitise().y);
    EXPECT_EQ(1, IntVec(8,-4).unitise().x);
}

