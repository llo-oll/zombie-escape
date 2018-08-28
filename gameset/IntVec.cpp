#include "IntVec.h"

IntVec::IntVec(int x, int y)
    :x {x}, y {y}
{}

IntVec::IntVec(const IntVec &that)
        :x {that.x},
         y {that.y}
{}


bool IntVec::operator==(const IntVec &that) const {
    return x == that.x &&
           y == that.y;
}

bool IntVec::operator!=(const IntVec &that) const {
    return !(that == *this);
}

IntVec IntVec::operator+(const IntVec &that) const {
    return IntVec(x+that.x, y+that.y);
}

IntVec IntVec::operator-(const IntVec &that) const {
    return IntVec(x-that.x, y-that.y);
}

std::ostream &operator<<(std::ostream &os, const IntVec &vec) {
    os << "x: " << vec.x << " y: " << vec.y;
    return os;
}


/**
 * @return the additive inverse of this IntVec.
 */
IntVec IntVec::inverse() {
    return IntVec(-x, -y);
}

/**
 * @return an IntVec representing a move of 1 square on a grid in the direction of the square represented by "this" IntVec
 * one of (0,1), (1,1), (1,0), (1, -1), (0, -1), (-1, -1), (-1, 0), (1, -1), and (0, 0)
 */
IntVec IntVec::unitise() {
    //   <_<
    int x_ = y != 0 ? 2 * x / abs(y) : x;
    int y_ = x != 0 ? 2 * y / abs(x) : y;
    int xNew = x_ != 0 ? x_ / abs(x_) : 0;
    int yNew = y_ != 0 ? y_ / abs(y_) : 0;
    return IntVec(xNew, yNew);
}





