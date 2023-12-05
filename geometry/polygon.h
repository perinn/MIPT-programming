#pragma once

#include <iostream>
#include <vector>
#include <utility>

#include "interface.h"
#include "point.h"

class geometry::Polygon : public geometry::IShape {
 public:
  std::vector<geometry::Point> points{};
  Polygon() = default;
  Polygon(const Polygon&);
  explicit Polygon(std::vector<geometry::Point>&&);
  explicit Polygon(const std::vector<geometry::Point>&);
  Polygon& operator=(const Polygon&);
  Polygon& Move(const geometry::Vector&) override;
  geometry::Polygon* Clone() const override;
  bool ContainsPoint(const geometry::Point&) const override;
  bool CrossesSegment(const geometry::Segment&) const override;
  bool IsConvexity() const;
  int64_t Area() const;
  std::string ToString() const override;
  ~Polygon() final;
};

std::vector<geometry::Point> JarvisConvexHull(std::vector<geometry::Point>&&);