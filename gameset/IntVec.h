#ifndef LEARN_CPP_VEC_H
#define LEARN_CPP_VEC_H


#include <ostream>

class IntVec {
public:
    const int x;
    const int y;
    IntVec(int x, int y);
    IntVec(const IntVec& that);

    bool operator==(const IntVec &that) const;

    bool operator!=(const IntVec &that) const;

    IntVec operator+(const IntVec &that) const;

    IntVec operator-(const IntVec &that) const;

    friend std::ostream &operator<<(std::ostream &os, const IntVec &vec);

    IntVec inverse();
    IntVec unitise();
};


#endif //LEARN_CPP_VEC_H
