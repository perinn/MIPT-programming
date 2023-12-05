#include "rational.h"

Rational::Rational() {
  num = 0;
  den = 1;
}

Rational::Rational(int32_t x) {
  num = x;
  den = 1;
}

Rational::Rational(int32_t x, int32_t y) {
  if (y != 0) {
    num = x;
    den = y;
    Rational::Reduction();
  } else {
    throw RationalDivisionByZero{};
  }
  
}

int32_t Rational::GetNumerator() const {
  return num;
}

int32_t Rational::GetDenominator() const {
  return den;
}

void Rational::SetNumerator(int32_t x) {
  num = x;
  Reduction();
}

void Rational::SetDenominator(int32_t x) {
  if (x > 0) {
    den = x;
  } else if (x < 0) {
    num *= -1;
    den = -x;
  } else {
    throw RationalDivisionByZero{};
  }
  Reduction();
}

Rational operator+(const Rational& x, const Rational& y) {
  Rational s = x;
  s += y;
  return s;
}

Rational operator-(const Rational& x, const Rational& y) {
  Rational s = x;
  s -= y;
  return s;
}

Rational operator/(const Rational& x, const Rational& y) {
  if (y.num != 0) {
    Rational s = x;
    s /= y;
    return s;
  }
  throw RationalDivisionByZero{};
}

Rational operator*(const Rational& x, const Rational& y) {
  Rational s = x;
  s *= y;
  return s;
}

Rational& Rational::operator+=(const Rational& x) {
  num = num * x.den + den * x.num;
  den *= x.den;
  Rational::Reduction();
  return *this;
}

Rational& Rational::operator-=(const Rational& x) {
  num = num * x.den - den * x.num;
  den *= x.den;
  Rational::Reduction();
  return *this;
}

Rational& Rational::operator/=(const Rational& x) {
  if (x.num != 0) {
    num *= x.den;
    den *= x.num;
    Rational::Reduction();
    return *this;
  }
  throw RationalDivisionByZero{};  
}

Rational& Rational::operator*=(const Rational& x) {
  num *= x.num;
  den *= x.den;
  Rational::Reduction();
  return *this;
}

Rational operator+(const Rational& x) {
  return {x.num, x.den};
}

Rational operator-(const Rational& x) {
  return {-x.num, x.den};
}

Rational& Rational::operator++() {
  num += den;
  Reduction();
  return *this;
}

Rational Rational::operator++(int32_t) {
  Rational x = *this;
  ++*this;
  return x;
}

Rational& Rational::operator--() {
  num -= den;
  Reduction();
  return *this;
}

Rational Rational::operator--(int32_t) {
  Rational x = *this;
  --*this;
  return x;
}

bool operator<(const Rational& x, const Rational& y) {
  return x.num * y.den < x.den * y.num;
}
bool operator>(const Rational& x, const Rational& y) {
  return y < x;
}

bool operator==(const Rational& x, const Rational& y) {
  return !(y < x || x < y);
}

bool operator!=(const Rational& x, const Rational& y) {
  return y < x || x < y;
}

bool operator<=(const Rational& x, const Rational& y) {
  return x < y || x == y;
}

bool operator>=(const Rational& x, const Rational& y) {
  return x > y || x == y;
}

std::istream& operator>>(std::istream& is, Rational& x) {
  is >> x.num;
  if (is.peek() != '/') {
    x.den = 1;
  } else {
    char t;
    is >> t >> x.den;
    if (x.den == 0) {
      throw RationalDivisionByZero{};
    }
  }
  x.Reduction();
  return is;
}

std::ostream& operator<<(std::ostream& os, const Rational& x) {
  if (x.den != 1) {
    os << x.num << '/' << x.den;    
  } else {
    os << x.num;    
  }
  return os;
}