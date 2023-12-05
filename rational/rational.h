#include <stdexcept>
#include <iostream>
#include <numeric>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
  int32_t num, den;
  inline void Reduction() {
    int32_t tmp = gcd(num, den);
    num /= tmp;
    den /= tmp;
    if (den < 0) {
      num *= -1;
      den *= -1;
    }
  }
  public:
  Rational();
  Rational(int32_t a);
  Rational(int32_t a, int32_t b);
  int32_t GetNumerator() const;
  int32_t GetDenominator() const;
  void SetNumerator(int32_t a);
  void SetDenominator(int32_t a);
  friend Rational operator+(const Rational& a, const Rational& b);
  friend Rational operator-(const Rational& a, const Rational& b);
  friend Rational operator/(const Rational& a, const Rational& b);
  friend Rational operator*(const Rational& a, const Rational& b);
  Rational& operator+=(const Rational& a);
  Rational& operator-=(const Rational& a);
  Rational& operator/=(const Rational& a);
  Rational& operator*=(const Rational& a);
  friend Rational operator+(const Rational& a);
  friend Rational operator-(const Rational& a);
  Rational& operator++();
  Rational operator++(int32_t);
  Rational& operator--();
  Rational operator--(int32_t);
  friend bool operator<(const Rational& a, const Rational& b);
  friend bool operator>(const Rational& a, const Rational& b);
  friend bool operator==(const Rational& a, const Rational& b);
  friend bool operator!=(const Rational& a, const Rational& b);
  friend bool operator<=(const Rational& a, const Rational& b);
  friend bool operator>=(const Rational& a, const Rational& b);
  friend std::istream& operator>>(std::istream& is, Rational& a);
  friend std::ostream& operator<<(std::ostream& os, const Rational& a);
};