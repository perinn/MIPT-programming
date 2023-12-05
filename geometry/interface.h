#pragma once

#include <iostream>

namespace geometry {
  class Point;  
  class Vector;
  class Line;
  class Ray;
  class Segment;
  class Polygon;
  class Circle;
  class IShape {
  public:
    virtual ~IShape() = default;
    virtual IShape& Move(const Vector& vector) = 0;
    virtual bool ContainsPoint(const Point& point) const = 0;
    virtual bool CrossesSegment(const Segment& segment) const = 0;
    virtual IShape* Clone() const = 0;
    virtual std::string ToString() const = 0;
  };
}