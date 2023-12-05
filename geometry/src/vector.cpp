#include <iostream>
#include <cmath>

#include "../vector.h"

geometry::Vector::Vector() : x(0), y(0) {
}

geometry::Vector::Vector(const int64_t& x_begin, const int64_t& y_begin, const int64_t& x_end, const int64_t& y_end)
    : x(x_end - x_begin), y(y_end - y_begin) {
}

geometry::Vector::Vector(const geometry::Point& begin, const geometry::Point& end)
    : x(end.x - begin.x), y(end.y - begin.y) {
}

geometry::Vector geometry::Vector::operator+() {
  return *this;
}

geometry::Vector geometry::Vector::operator-() {
  x = -x;
  y = -y;
  return *this;
}

geometry::Vector geometry::Vector::operator+(const geometry::Vector& second) const {
  geometry::Vector tmp;
  tmp.x = this->x + second.x;
  tmp.y = this->y + second.y;
  return tmp;
}

geometry::Vector geometry::Vector::operator-(const geometry::Vector& second) const {
  geometry::Vector tmp;
  tmp.x = this->x - second.x;
  tmp.y = this->y - second.y;
  return tmp;
}

geometry::Vector geometry::Vector::operator*(const int64_t& val) const {
  geometry::Vector tmp(0, 0, x, y);
  tmp.x = tmp.x * val;
  tmp.y = tmp.y * val;
  return tmp;
}

geometry::Vector geometry::Vector::operator/(const int64_t& val) const {
  geometry::Vector tmp(0, 0, x, y);
  tmp.x = tmp.x / val;
  tmp.y = tmp.y / val;
  return tmp;
}

geometry::Vector& geometry::Vector::operator+=(const geometry::Vector& second) {
  this->x = this->x + second.x;
  this->y = this->y + second.y;
  return *this;
}

geometry::Vector& geometry::Vector::operator-=(const geometry::Vector& second) {
  this->x = this->x - second.x;
  this->y = this->y - second.y;
  return *this;
}

geometry::Vector& geometry::Vector::operator*=(const int64_t& val) {
  this->x = this->x * val;
  this->y = this->y * val;
  return *this;
}

geometry::Vector& geometry::Vector::operator/=(const int64_t& val) {
  this->x = this->x / val;
  this->y = this->y / val;
  return *this;
}

bool geometry::Vector::operator==(const geometry::Vector& second) const {
  return this->x == second.x && this->y == second.y ? true : false;
}

std::string geometry::Vector::ToString() const {
  std::string ans = "Vector(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ')';
  return ans;
}

long double LengthOfVector(const geometry::Vector& vector) {
  auto len = static_cast<long double>(sqrt(pow(vector.x, 2) + pow(vector.y, 2)));
  return len;
}

int64_t ScalarProduct(const geometry::Vector& first, const geometry::Vector& second) {
  auto ans = first.x * second.x + first.y * second.y;
  return ans;
}

int64_t VectorProduct(const geometry::Vector& first, const geometry::Vector& second) {
  auto ans = first.x * second.y - first.y * second.x;
  return ans;
}

long double AreaOfTreangle(const geometry::Vector& first, const geometry::Vector& second) {
  return std::abs(VectorProduct(first, second) / 2);
}

std::istream& operator>>(std::istream& is, geometry::Vector& vector) {
  int64_t x_begin, y_begin, x_end, y_end;
  is >> x_begin >> y_begin >> x_end >> y_end;
  vector.x = x_end - x_begin;
  vector.y = y_end - y_begin;
  return is;
}

std::ostream& operator<<(std::ostream& os, geometry::Vector vector) {
  os << vector.x << ' ' << vector.y;
  return os;
}
