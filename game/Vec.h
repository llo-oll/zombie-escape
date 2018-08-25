//
// Created by ben on 20/08/18.
//

#ifndef LEARN_CPP_VEC_H
#define LEARN_CPP_VEC_H


#include <ostream>

class Vec {
public:
    const int x;
    const int y;
    Vec(int x, int y);
    Vec(const Vec& other);

    bool operator==(const Vec &rhs) const;

    bool operator!=(const Vec &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Vec &vec);
};


#endif //LEARN_CPP_VEC_H
