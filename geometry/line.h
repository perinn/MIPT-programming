#pragma once

#include "interface.h"
#include "point.h"
#include "vector.h"

class geometry::Line : public geometry::IShape {
 public:
  geometry::Point point;
  geometry::Vector guide;
  Line(const geometry::Point&, const geometry::Point&);
  Line(const Line&);
  Line& operator=(const Line&);
  Line& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Line* Clone() const override;
  std::string ToString() const override;
  ~Line() final;
};

long double IntersectionX(const geometry::Line&, const geometry::Line&);