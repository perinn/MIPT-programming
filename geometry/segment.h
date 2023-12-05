#pragma once

#include "interface.h"
#include "point.h"

class geometry::Segment : public geometry::IShape {
 public:
  geometry::Point first, second;
  Segment() = default;
  Segment(const geometry::Point&, const geometry::Point&);
  Segment(const Segment&);
  Segment& operator=(const Segment&);
  Segment& Move(const Vector&) override;
  Segment* Clone() const override;
  std::string ToString() const override;
  bool ContainsPoint(const geometry::Point&) const override;
  bool CrossesSegment(const geometry::Segment&) const override;
  ~Segment() final;
};

bool Crossing(const geometry::Segment&, const geometry::Segment&);