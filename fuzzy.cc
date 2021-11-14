#include <algorithm>
#include "fuzzy.h"

/*
TriFuzzyNum num(1.25, 2.25, 3.25);
TriFuzzyNum num(2.25, 3.25, 1.25);
constexpr TriFuzzyNum num(1.25, 2.25, 3.25);
constinit static TriFuzzyNum num(1.25, 2.25, 3.25);
*/

constexpr TriFuzzyNum::TriFuzzyNum(real_t a, real_t b, real_t c) {
    this->l = std::min(a, b, c);
    this->u = std::max(a, b, c);
    this->m =
        l <= a <= u 
        ? a
        : l <= b <= u
            ? b
            : c;
}