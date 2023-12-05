#pragma once

#include "interface.h"
#include "point.h"

class geometry::Vector {
 public:
  int64_t x, y;
  Vector();
  Vector(const int64_t&, const int64_t&, const int64_t&, const int64_t&);
  Vector(const geometry::Point&, const geometry::Point&);
  Vector(const Vector&) = default;
  Vector& operator=(const Vector&) = default;
  Vector operator+();
  Vector operator-();
  Vector operator+(const Vector&) const;
  Vector operator-(const Vector&) const;
  Vector operator*(const int64_t&) const;
  Vector operator/(const int64_t&) const;
  Vector& operator+=(const Vector&);
  Vector& operator-=(const Vector&);
  Vector& operator*=(const int64_t&);
  Vector& operator/=(const int64_t&);
  bool operator==(const Vector&) const;
  std::string ToString() const;
  ~Vector() = default;
};

long double LengthOfVector(const geometry::Vector&);
int64_t ScalarProduct(const geometry::Vector&, const geometry::Vector&);
int64_t VectorProduct(const geometry::Vector&, const geometry::Vector&);
long double AreaOfTreangle(const geometry::Vector&, const geometry::Vector&);
std::istream& operator>>(std::istream&, geometry::Vector&);
std::ostream& operator<<(std::ostream&, geometry::Vector);