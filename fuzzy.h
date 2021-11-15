#ifndef FUZZY_H
#define FUZZY_H

#include <iostream>
#include <cmath>
// TODO inline dla stałej, sortowanie przy mnożeniu.
using real_t = double;
using std::ostream;

class TriFuzzyNum {
public:
    constexpr TriFuzzyNum(const real_t &a, const real_t &b, const real_t &c) {
        real_t values[] = {a, b, c};
        std::sort(std::begin(values), std::end(values));

        this->l = values[0];
        this->m = values[1];
        this->u = values[2];
    }

    constexpr real_t lower_value() const {
        return this->l;
    }

    constexpr real_t modal_value() const {
        return this->m;
    }

    constexpr real_t upper_value() const {
        return this->u;
    }

    constexpr TriFuzzyNum operator+(const TriFuzzyNum &that) const {
        real_t new_l = this->l + that.l;
        real_t new_m = this->m + that.m;
        real_t new_u = this->u + that.u;
        return TriFuzzyNum(new_l, new_m, new_u);
    }

    constexpr TriFuzzyNum operator-(const TriFuzzyNum &that) const {
        real_t new_l = this->l - that.u;
        real_t new_m = this->m - that.m;
        real_t new_u = this->u - that.l;
        return TriFuzzyNum(new_l, new_m, new_u);
    }

    constexpr TriFuzzyNum operator*(const TriFuzzyNum &that) const {
        real_t new_l = this->l * that.l;
        real_t new_m = this->m * that.m;
        real_t new_u = this->u * that.u;

        real_t values[] = {new_l, new_m, new_u};
        std::sort(std::begin(values), std::end(values));

        return TriFuzzyNum(values[0], values[1], values[2]);
    }

    constexpr TriFuzzyNum operator+=(const TriFuzzyNum &that) {
        *this = *this + that;
        return *this;
    }

    constexpr TriFuzzyNum operator-=(const TriFuzzyNum &that) {
        *this = *this - that;
        return *this;
    }

    constexpr TriFuzzyNum operator*=(const TriFuzzyNum &that) {
        *this = *this * that;
        return *this;
    }

    constexpr int operator<=>(const TriFuzzyNum &that) const {
        real_t z1 = this->u - this->l + sqrt(1 + (this->u - this->m) *
                (this->u - this->m)) + sqrt(1 + (this->m - this->l) * (this->m - this->l));
        real_t y1 = (this->u - this->l) / z1;
        real_t x1 = ((this->u - this->l) * this->m + sqrt(1 + (this->u - this->m) * (this->u - this->m))
                * this->l + sqrt(1 + (this->m - this->l) *(this->m - this->l)) * this->u) / z1;

        real_t z2 = that.u - that.l + sqrt(1 + (that.u - that.m) *
                (that.u - that.m)) + sqrt(1 + (that.m - that.l) * (that.m - that.l));
        real_t y2 = (that.u - that.l) / z2;
        real_t x2 = ((that.u - that.l) * that.m + sqrt(1 + (that.u - that.m) * (that.u - that.m))
                * that.l + sqrt(1 + (that.m - that.l) *(that.m - that.l)) * that.u) / z2;

        real_t first1 = (x1 - y1) / 2;
        real_t first2 =(x2 - y2) / 2;
        real_t second1 = 1 - y1;
        real_t second2 = 1 - y2;
        real_t third1 = this->m;
        real_t third2 = that.m;

        if (first1 > first2) return 1;
        else if (first1 < first2) return -1;
        else {
            if (second1 > second2) return 1;
            else if (second1 < second2) return -1;
            else {
                if (third1 > third2) return 1;
                else if (third1 < third2) return -1;
                else return 0;
            }
        }
    }

    constexpr bool operator==(const TriFuzzyNum &that) const {
        return (this->l == that.l && this->m == that.m && this->u == that.u);
    }

    constexpr bool operator!=(const TriFuzzyNum &that) const {
        return (this->l != that.l || this->m != that.m || this->u != that.u);
    }

    /*constexpr TriFuzzyNum crisp_number(real_t v) {
        return TriFuzzyNum(v, v, v);
    }*/

private:
    real_t l, m, u;
    friend std::ostream& operator<<(std::ostream&, const TriFuzzyNum&);
};

#endif //FUZZY_H
