#pragma once

#include <iostream>

#include "interface.h"
#include "vector.h"

class geometry::Point : public geometry::IShape {
 public:
  int64_t x, y;
  Point();
  Point(int64_t, int64_t);
  Point(const Point&);
  Point& operator=(const Point&);
  geometry::Vector operator-(const geometry::Point&) const;
  Point& Move(const geometry::Vector&) override;
  bool ContainsPoint(const geometry::Point&) const override;
  bool CrossesSegment(const geometry::Segment&) const override;
  double Length(const geometry::Segment&);
  std::string ToString() const override;
  Point* Clone() const override;
  ~Point() final;
};

geometry::Point operator+(const geometry::Point&, const geometry::Vector&);
bool operator==(const geometry::Point&, const geometry::Point&);
bool operator!=(const geometry::Point&, const geometry::Point&);