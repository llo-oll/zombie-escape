//
// Created by ben on 20/08/18.
//

#include "Vec.h"

Vec::Vec(const int x, const int y)
    :x {x}, y {y}
{}

bool Vec::operator==(const Vec &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Vec::operator!=(const Vec &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Vec &vec) {
    os << "x: " << vec.x << " y: " << vec.y;
    return os;
}

Vec::Vec(const Vec &other) {
    x = other.x;
    y = other.y;
}
