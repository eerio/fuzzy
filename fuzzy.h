#ifndef _FUZZY_H
#define _FUZZY_H

using real_t = long double;

class TriFuzzyNum {
    real_t l;
    real_t m;
    real_t u;

public:
    TriFuzzyNum(real_t a, real_t b, real_t c);
    real_t lower_value();
    real_t modal_value();
    real_t upper_value();

}

#endif // _FUZZY_H
