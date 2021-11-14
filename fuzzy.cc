#include <iostream>
#include "fuzzy.h"
#include <vector>

using std::vector;
using std::ostream;

ostream &operator<<(ostream &os, const TriFuzzyNum &t) {
    os << "("
       << t.l
       << ", "
       << t.m
       << ", "
       << t.u
       << ")";
    return os;
}





