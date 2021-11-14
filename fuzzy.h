#ifndef _FUZZY_H
#define _FUZZY_H

using real_t = long double;

class TriFuzzyNum {
    real_t l;
    real_t m;
    real_t u;

public:
    constexpr TriFuzzyNum(real_t a, real_t b, real_t c);
    constexpr real_t lower_value();
    constexpr real_t modal_value();
    constexpr real_t upper_value();

    bool operator==(TriFuzzyNum other);
    TriFuzzyNum operator+(TriFuzzyNum other);
    TriFuzzyNum operator-(TriFuzzyNum other);

}

#endif // _FUZZY_H
