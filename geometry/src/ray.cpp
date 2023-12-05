#include <iostream>

#include "../vector.h"
#include "../segment.h"
#include "../ray.h"
#include "../line.h"


geometry::Ray::Ray() = default;

geometry::Ray::Ray(const Point& first, const Point& second) : point(first), guide(first, second) {
}

geometry::Ray::Ray(const geometry::Ray& other) : point(other.point), guide(other.guide) {
}

geometry::Ray& geometry::Ray::operator=(const geometry::Ray& other) {
  this->point = other.point;
  this->guide = other.guide;
  return *this;
}

geometry::Ray& geometry::Ray::Move(const Vector& vector) {
  this->point.x = this->point.x + vector.x;
  this->point.y = this->point.y + vector.y;
  return *this;
}

geometry::Ray* geometry::Ray::Clone() const {
  Ray* new_ray = new Ray(this->point, this->point + this->guide);
  return new_ray;
}

bool geometry::Ray::ContainsPoint(const Point& tmp_point) const {
  Vector tmp(this->point, tmp_point);
  return ((this->guide.x == 0) && (this->guide.y == 0) && this->point.ContainsPoint(tmp_point)) || ((VectorProduct(this->guide, tmp) == 0) && (ScalarProduct(this->guide, tmp) >= 0)) ? true : false;
}

bool geometry::Ray::CrossesSegment(const Segment& segment) const {
  bool flag = false;
  if (segment.ContainsPoint(this->point)) {
    flag = true;
  } else if ((this->guide.x == 0) && (this->guide.y == 0) && (this->point.CrossesSegment(segment))) {
    flag = true;
  } else if (Crossing(Segment(this->point, this->point + this->guide), segment)) {
    if (segment.first == segment.second && this->ContainsPoint(segment.first)) {
      flag = true;
    } else {
      double x = IntersectionX(geometry::Line(this->point, this->point + this->guide),
                               geometry::Line(segment.first, segment.second));
      if (x >= static_cast<double>(this->point.x)) {
        flag = true;
      }
    }
  }
  return flag;
}

std::string geometry::Ray::ToString() const {
  std::string ans = "Ray(" + this->point.ToString() + ", " + this->guide.ToString() + ')';
  return ans;
}

geometry::Ray::~Ray() = default;