#ifndef FUZZY_H
#define FUZZY_H

#include <algorithm>
#include <iostream>
#include <cmath>
#include <tuple>
#include <numeric>
#include <set>

// TODO inline dla stałej, sortowanie przy mnożeniu.
using real_t = double;
using std::ostream;

class TriFuzzyNum {
    real_t l, m, u;

public:
    constexpr TriFuzzyNum(real_t a, real_t b, real_t c) {
        real_t values[] = {a, b, c};
        std::sort(std::begin(values), std::end(values));

        this->l = values[0];
        this->m = values[1];
        this->u = values[2];
    }

    constexpr TriFuzzyNum(const TriFuzzyNum& t) = default;
    constexpr TriFuzzyNum(TriFuzzyNum&& t) = default;

    constexpr TriFuzzyNum& operator=(TriFuzzyNum&& t) = default;

    constexpr real_t lower_value() const { return this->l; }
    constexpr real_t modal_value() const { return this->m; }
    constexpr real_t upper_value() const { return this->u; }

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
        return TriFuzzyNum(new_l, new_m, new_u);
    }

    constexpr TriFuzzyNum operator/(unsigned int d) const {
        return TriFuzzyNum(this->l / d, this->m / d, this->u / d);
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

    std::tuple<real_t, real_t, real_t> rank() const {
        real_t z = (u - l) + sqrt(1 + (u - m) * (u - m)) + sqrt(1 + (m - l) * (m - l));
        real_t x = ((u - l) * m + sqrt(1 + (u - m) * (u - m)) * l + sqrt(1 + (m - l) * (m - l)) * u) / z;
        real_t y = (u - l) / z;
        return std::make_tuple(x - y / 2, 1 - y, m);
    }

    auto operator<=>(const TriFuzzyNum &other) const {
        auto my_rank = this->rank();
        auto other_rank = other.rank();
        return my_rank <=> other_rank;
    }

    constexpr bool operator==(const TriFuzzyNum &other) const = default;

    friend std::ostream& operator<<(std::ostream& stream, const TriFuzzyNum& num) {
        stream
            << '('
            << num.l << ", "
            << num.m << ", "
            << num.u << ')';
        return stream;
    }
};

class TriFuzzyNumSet {
    std::multiset<TriFuzzyNum> nums;

public:
    TriFuzzyNumSet() = default;
    TriFuzzyNumSet(std::initializer_list<TriFuzzyNum> init): nums(init) {};

    TriFuzzyNumSet(const TriFuzzyNumSet& num) = default;
    TriFuzzyNumSet(TriFuzzyNumSet&& num) = default;

    TriFuzzyNumSet& operator=(TriFuzzyNumSet&& num) = default;
    TriFuzzyNumSet& operator=(const TriFuzzyNumSet& num) = default;

    void insert(const TriFuzzyNum& num) { nums.insert(num); }
    void insert(TriFuzzyNum&& num) { nums.insert(num); }

    void remove(const TriFuzzyNum& num) { nums.erase(num); }

    TriFuzzyNum arithmetic_mean() {
        if (nums.empty()) throw std::length_error("TriFuzzyNumSet::arithmetic_mean - the set is empty.");
        return std::accumulate(nums.begin(), nums.end(), TriFuzzyNum {0, 0, 0}) / nums.size();
    }
};

constexpr TriFuzzyNum crisp_number(real_t v) {
    return TriFuzzyNum(v, v, v);
}

constexpr TriFuzzyNum crisp_zero = crisp_number(0);

#endif //FUZZY_H
