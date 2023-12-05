#pragma once

#include "interface.h"
#include "point.h"

class geometry::Circle : public geometry::IShape {
 public:
  geometry::Point centre;
  int64_t r;
  Circle(const geometry::Point&, const int64_t&);
  Circle(const Circle&);
  Circle& operator=(const Circle&);
  Circle& Move(const Vector&) override;
  Circle* Clone() const override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  std::string ToString() const override;
  ~Circle() final;
};