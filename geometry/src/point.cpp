#include <string>

#include "../vector.h"
#include "../segment.h"

geometry::Point::Point() : x(0), y(0) {
}

geometry::Point::Point(int64_t first, int64_t second) : x(first), y(second) {
}

geometry::Point::Point(const geometry::Point& other) : x(other.x), y(other.y) {
}

geometry::Point& geometry::Point::operator=(const Point& other) {
  this->x = other.x;
  this->y = other.y;
  return *this;
}

geometry::Vector geometry::Point::operator-(const geometry::Point& point) const {
  Vector vector(point, *this);
  return vector;
}

geometry::Point& geometry::Point::Move(const Vector& vector) {
  this->x = this->x + vector.x;
  this->y = this->y + vector.y;
  return *this;
}

bool geometry::Point::ContainsPoint(const geometry::Point& point) const {
  return this->x == point.x && this->y == point.y ? true : false;
}

bool geometry::Point::CrossesSegment(const Segment& segment) const {
  Vector guide1(segment.first.x, segment.first.y, segment.second.x, segment.second.y);
  Vector guide2(segment.second.x, segment.second.y, segment.first.x, segment.first.y);
  Vector tmp1(segment.first.x, segment.first.y, this->x, this->y);
  Vector tmp2(segment.second.x, segment.second.y, this->x, this->y);
  return ((segment.first == segment.second && segment.first == *this) || ((VectorProduct(guide1, tmp1) == 0) && (ScalarProduct(guide1, tmp1) >= 0) && (ScalarProduct(guide2, tmp2) >= 0))) ? true : false;
}

double geometry::Point::Length(const geometry::Segment& other) {
  double segment_len = 0.0;
  if (ScalarProduct(geometry::Vector(other.first, other.second), geometry::Vector(other.first, *this)) <= 0.0) {
    segment_len = LengthOfVector(geometry::Vector(other.first, *this));
  } else if (ScalarProduct(geometry::Vector(other.second, other.first), geometry::Vector(other.second, *this)) <= 0.0) {
    segment_len = LengthOfVector(geometry::Vector(other.second, *this));
  } else {
    segment_len =
        std::abs(VectorProduct(geometry::Vector(other.first, other.second), geometry::Vector(other.first, *this))) /
        LengthOfVector(geometry::Vector(other.first, other.second));
  }
  return segment_len;
}

std::string geometry::Point::ToString() const {
  auto x_str = std::to_string(this->x);
  auto y_str = std::to_string(this->y);
  auto ans = "Point(" + x_str + ", " + y_str + ')';
  return ans;
}

geometry::Point* geometry::Point::Clone() const {
  auto* new_point = new Point(this->x, this->y);
  return new_point;
}

geometry::Point::~Point() = default;

geometry::Point operator+(const geometry::Point& point, const geometry::Vector& vector) {
  return geometry::Point(point.x + vector.x, point.y + vector.y);
}

bool operator==(const geometry::Point& first, const geometry::Point& second) {
  return first.x == second.x && first.y == second.y ? true : false;
}

bool operator!=(const geometry::Point& first, const geometry::Point& second) {
  return first.x != second.x || first.y != second.y ? true : false;
}