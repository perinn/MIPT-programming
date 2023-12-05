#pragma once

#include "interface.h"
#include "point.h"

class geometry::Ray : public geometry::IShape {
 public:
  geometry::Point point;
  geometry::Vector guide;
  Ray();
  Ray(const geometry::Point&, const geometry::Point&);
  Ray(const Ray&);
  Ray& operator=(const Ray&);
  Ray& Move(const Vector&) override;
  Ray* Clone() const override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  std::string ToString() const override;
  ~Ray() final;
};