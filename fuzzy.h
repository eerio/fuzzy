#ifndef FUZZY_H
#define FUZZY_H

#include <algorithm>
#include <array>
#include <iostream>
#include <cmath>
#include <tuple>
#include <numeric>
#include <set>

using real_t = double;

class TriFuzzyNum {
    real_t l, m, u;

    using rank_t = std::tuple<real_t, real_t, real_t>;

     [[nodiscard]] rank_t rank() const {
        real_t z = (u - l) + sqrt(1 + (u - m) * (u - m)) + sqrt(1 + (m - l) * (m - l));
        real_t x = ((u - l) * m + sqrt(1 + (u - m) * (u - m)) * l + sqrt(1 + (m - l) * (m - l)) * u) / z;
        real_t y = (u - l) / z;
        return std::make_tuple(x - y / 2, 1 - y, m);
    }

    constexpr void normalize() {
        std::array<real_t, 3> values {l, m, u};
        std::ranges::sort(values);

        l = values[0];
        m = values[1];
        u = values[2];
    }

public:
    constexpr TriFuzzyNum(real_t a, real_t b, real_t c) : l(a), m(b), u(c) {
        this->normalize();
    }

    constexpr TriFuzzyNum(const TriFuzzyNum& t) = default;
    constexpr TriFuzzyNum(TriFuzzyNum&& t) = default;

    constexpr TriFuzzyNum& operator=(TriFuzzyNum&& t) = default;

    [[nodiscard]] constexpr real_t lower_value() const { return l; }
    [[nodiscard]] constexpr real_t modal_value() const { return m; }
    [[nodiscard]] constexpr real_t upper_value() const { return u; }

    constexpr TriFuzzyNum operator+(const TriFuzzyNum &that) const {
        auto res = TriFuzzyNum(*this);
        res += that;
        return res;
    }

    constexpr TriFuzzyNum operator-(const TriFuzzyNum &that) const {
        auto res = TriFuzzyNum(*this);
        res -= that;
        return res;
    }

    constexpr TriFuzzyNum operator*(const TriFuzzyNum &that) const {
        auto res = TriFuzzyNum(*this);
        res *= that;
        return res;
    }

    constexpr TriFuzzyNum operator/(unsigned int d) const {
        return {l / d, m / d, u / d};
    }

    constexpr TriFuzzyNum& operator+=(const TriFuzzyNum &that) {
        u += that.u;
        m += that.m;
        l += that.l;
        return *this;
    }

    constexpr TriFuzzyNum& operator-=(const TriFuzzyNum &that) {
        l -= that.u;
        m -= that.m;
        u -= that.l;
        return *this;
    }

    constexpr TriFuzzyNum& operator*=(const TriFuzzyNum &that) {
        u *= that.u;
        m *= that.m;
        l *= that.l;
        normalize();
        return *this;
    }

    auto operator<=>(const TriFuzzyNum &other) const {
        return this->rank() <=> other.rank();
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
    void remove(TriFuzzyNum&& num) { nums.erase(num); }

    TriFuzzyNum arithmetic_mean() const {
        if (nums.empty()) throw std::length_error(
            "TriFuzzyNumSet::arithmetic_mean - the set is empty."
        );

        TriFuzzyNum sum = std::accumulate(
            nums.begin(),
            nums.end(),
            TriFuzzyNum {0, 0, 0}
        );

        return sum / nums.size();
    }
};

consteval TriFuzzyNum crisp_number(real_t v) {
    return {v, v, v};
}

inline constinit const TriFuzzyNum crisp_zero = crisp_number(0);

#endif //FUZZY_H
