#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>

class Point;
class Vector;
class Line;
class Segment;
class Ray;
class Polygon;
class Circle;

class Point {
  int64_t x_, y_;

 public:
  Point();
  Point(int64_t, int64_t);
  explicit Point(const Vector&);
  int64_t GetX() const;
  int64_t GetY() const;
  long double Distance(const Point&, const Point&);
  friend std::istream& operator>>(std::istream&, Point&);
  friend std::ostream& operator<<(std::ostream&, const Point&);
  friend bool operator==(const Point&, const Point&);
  friend bool operator!=(const Point&, const Point&);
  friend Vector operator-(const Point&, const Point&);
};

class Vector {
  int64_t x_, y_;

 public:
  Vector();
  Vector(int64_t, int64_t);
  Vector(int64_t, int64_t, int64_t, int64_t);
  explicit Vector(const Point&);
  Vector(const Point&, const Point&);
  int64_t GetX() const;
  int64_t GetY() const;
  long double GetL() const;
  int64_t ScalarProduct(const Vector&, const Vector&);
  int64_t VectorProduct(const Vector&, const Vector&);
  long double Angle(const Vector&, const Vector&);
  friend Vector operator*(int64_t, const Vector&);
  friend Vector operator*(const Vector&, int64_t);
  friend Vector operator+(const Vector&, const Vector&);
  friend Vector operator-(const Vector&, const Vector&);
  friend std::istream& operator>>(std::istream&, Vector&);
  friend std::ostream& operator<<(std::ostream&, const Vector&);
};

class Line {
  int64_t a_, b_, c_;

 public:
  Line();
  Line(int64_t, int64_t, int64_t);
  Line(const Point&, const Vector&);
  Line(const Point&, const Point&);
  explicit Line(const Segment&);
  int64_t GetA() const;
  int64_t GetB() const;
  int64_t GetC() const;
  Vector GuidingVector(const Line&);
  Vector NormalVector(const Line&);
  bool Parallel(const Line&, const Line&);
  bool IntersectionB(const Line&, const Line&);
  bool IntersectionB(const Line&, const Point&);
  bool IntersectionB(const Point&, const Line&);
  Point NullPoint(const Line&);
  Point IntersectionP(const Line&, const Line&);
  long double Distance(const Line&, const Line&);
  long double Distance(const Line&, const Point&);
  long double Distance(const Point&, const Line&);
  friend bool operator==(const Line&, const Line&);
  friend bool operator!=(const Line&, const Line&);
  friend std::istream& operator>>(std::istream&, Line&);
  friend std::ostream& operator<<(std::ostream&, const Line&);
};

class Segment {
  Point point1_;
  Point point2_;

 public:
  Segment();
  Segment(const Point&, const Point&);
  Point GetA() const;
  Point GetB() const;
  long double Distance(const Segment&, const Point&);
  long double Distance(const Point&, const Segment&);
  long double Distance(const Segment&, const Segment&);
  bool IntersectionB(const Segment&, const Point&);
  bool IntersectionB(const Point&, const Segment&);
  bool IntersectionB(const Segment&, const Line&);
  bool IntersectionB(const Line&, const Segment&);
  bool IntersectionC(const Segment&, const Line&);
  bool IntersectionC(const Line&, const Segment&);
  bool IntersectionB(const Segment&, const Segment&);
  bool IntersectionB(const Segment&, const Ray&);
  bool IntersectionB(const Ray&, const Segment&);
  friend std::istream& operator>>(std::istream&, Segment&);
};

class Ray {
  Point point_;
  Vector vector_;

 public:
  Ray();
  Ray(const Point&, const Point&);
  Ray(const Point&, const Vector&);
  Vector GetV() const;
  Point GetP() const;
  bool IntersectionB(const Ray&, const Point&);
  bool IntersectionB(const Point&, const Ray&);
  long double Distance(const Ray&, const Point&);
  long double Distance(const Point&, const Ray&);
};

class Polygon {
  std::vector<Point> points_;
  std::vector<Point>& link_ = points_;

 public:
  Polygon();
  explicit Polygon(size_t);
  size_t Size() const;
  std::vector<Point>& Points() const;
  void Push(Point&);
  void Del(size_t);
  friend std::istream& operator>>(std::istream&, Polygon&);
  friend std::ostream& operator<<(std::ostream&, Polygon&);
  long double Area() const;
  bool IsConvex(const Polygon&);
  bool IsInside(const Polygon&, const Point&);
  bool IntersectionB(const Polygon&, const Point&);
  Polygon ConvexHull(const Polygon&);
  std::vector<Polygon> Infection(const Polygon&);
  size_t WhereInInfection(const std::vector<Polygon>&, const Point&);
};

class Circle {};

// Point

Point::Point() {
  x_ = 0;
  y_ = 0;
}

Point::Point(int64_t x, int64_t y) {
  x_ = x;
  y_ = y;
}

Point::Point(const Vector& vector) {
  x_ = vector.GetX();
  y_ = vector.GetY();
}

int64_t Point::GetX() const {
  return x_;
}

int64_t Point::GetY() const {
  return y_;
}

long double Distance(const Point& point1, const Point& point2) {
  return sqrt((point1.GetX() - point2.GetX()) * (point1.GetX() - point2.GetX()) +
              (point1.GetY() - point2.GetY()) * (point1.GetY() - point2.GetY()));
}

std::istream& operator>>(std::istream& is, Point& point) {
  is >> point.x_ >> point.y_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
  os << point.GetX() << " " << point.GetY();
  return os;
}

bool operator==(const Point& point1, const Point& point2) {
  return (point1.GetX() == point2.GetX()) && (point1.GetY() == point2.GetY());
}

bool operator!=(const Point& point1, const Point& point2) {
  return !(point1.GetX() == point2.GetX()) && (point1.GetY() == point2.GetY());
}

Vector operator-(const Point& point1, const Point& point2) {
  return Vector(point2, point1);
}

// Vector

Vector::Vector() {
  x_ = 0;
  y_ = 0;
}

Vector::Vector(int64_t x, int64_t y) {
  x_ = x;
  y_ = y;
}

Vector::Vector(int64_t x_start, int64_t y_start, int64_t x_end, int64_t y_end) {
  x_ = x_end - x_start;
  y_ = y_end - y_start;
}

Vector::Vector(const Point& point) {
  x_ = point.GetX();
  y_ = point.GetY();
}

Vector::Vector(const Point& point1, const Point& point2) {
  x_ = point2.GetX() - point1.GetX();
  y_ = point2.GetY() - point1.GetY();
}

int64_t Vector::GetX() const {
  return x_;
}

int64_t Vector::GetY() const {
  return y_;
}

long double Vector::GetL() const {
  return sqrt(x_ * x_ + y_ * y_);
}

int64_t ScalarProduct(const Vector& vector1, const Vector& vector2) {
  return vector1.GetX() * vector2.GetX() + vector1.GetY() * vector2.GetY();
}

int64_t VectorProduct(const Vector& vector1, const Vector& vector2) {
  return vector1.GetX() * vector2.GetY() - vector1.GetY() * vector2.GetX();
}

long double Angle(const Vector& vector1, const Vector& vector2) {
  return VectorProduct(vector1, vector2) / (vector1.GetL() * vector2.GetL());
}
Vector operator*(int64_t value, const Vector& vector) {
  return Vector(vector.GetX() * value, vector.GetY() * value);
}

Vector operator*(const Vector& vector, int64_t value) {
  return Vector(vector.GetX() * value, vector.GetY() * value);
}

Vector operator+(const Vector& vector1, const Vector& vector2) {
  return Vector(vector1.GetX() + vector2.GetX(), vector1.GetY() + vector2.GetY());
}

Vector operator-(const Vector& vector1, const Vector& vector2) {
  return Vector(vector1.GetX() - vector2.GetX(), vector1.GetY() - vector2.GetY());
}

std::istream& operator>>(std::istream& is, Vector& vector) {
  int64_t x_start, y_start, x_end, y_end;
  is >> x_start >> y_start >> x_end >> y_end;
  vector.x_ = x_end - x_start;
  vector.y_ = y_end - y_start;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {
  os << vector.GetX() << " " << vector.GetY();
  return os;
}

// Line

Line::Line() {
  a_ = 0;
  b_ = 0;
  c_ = 0;
}

Line::Line(int64_t a, int64_t b, int64_t c) {
  a_ = a;
  b_ = b;
  c_ = c;
}

Line::Line(const Point& point, const Vector& vector) {
  a_ = vector.GetY();
  b_ = -vector.GetX();
  c_ = vector.GetX() * point.GetY() - vector.GetY() * point.GetX();
}

Line::Line(const Point& point1, const Point& point2) {
  auto vector = Vector(point1, point2);
  a_ = vector.GetY();
  b_ = -vector.GetX();
  c_ = vector.GetX() * point1.GetY() - vector.GetY() * point1.GetX();
}

Line::Line(const Segment& segment) {
  auto point1 = segment.GetA();
  auto point2 = segment.GetB();
  auto vector = Vector(point1, point2);
  a_ = vector.GetY();
  b_ = -vector.GetX();
  c_ = -point1.GetX() * vector.GetY() + point1.GetY() * vector.GetX();
}

int64_t Line::GetA() const {
  return a_;
}

int64_t Line::GetB() const {
  return b_;
}

int64_t Line::GetC() const {
  return c_;
}

Vector GuidingVector(const Line& line) {
  return Vector(-line.GetB(), line.GetA());
}

Vector NormalVector(const Line& line) {
  return Vector(line.GetA(), line.GetB());
}

bool Parallel(const Line& line1, const Line& line2) {
  auto vector1 = GuidingVector(line1);
  auto vector2 = GuidingVector(line2);
  return VectorProduct(vector1, vector2) == 0;
}

bool IntersectionB(const Line& line1, const Line& line2) {
  if (line1 == line2) {
    return true;
  }
  return line1.GetA() * line2.GetB() != line1.GetB() * line2.GetA();
}

bool IntersectionB(const Line& line, const Point& point) {
  return line.GetA() * point.GetX() + line.GetB() * point.GetY() + line.GetC() == 0;
}

bool IntersectionB(const Point& point, const Line& line) {
  return line.GetA() * point.GetX() + line.GetB() * point.GetY() + line.GetC() == 0;
}

Point NullPoint(const Line& line) {
  long double x, y;
  if (line.GetA() == 0) {
    x = 0;
    y = -line.GetC() / line.GetB();
  } else if (line.GetB() == 0) {
    x = -line.GetC() / line.GetA();
    y = 0;
  } else {
    x = -(line.GetC()) / (2 * line.GetA());
    y = -(line.GetC()) / (2 * line.GetB());
  }
  return Point(x, y);
}

Point IntersectionP(const Line& line1, const Line& line2) {
  long double delta = line1.GetA() * line2.GetB() - line1.GetB() * line2.GetA();
  long double delta_x = -line1.GetC() * line2.GetB() + line1.GetB() * line2.GetC();
  long double delta_y = -line1.GetA() * line2.GetC() + line1.GetC() * line2.GetA();
  long double x = delta_x / delta;
  long double y = delta_y / delta;
  return Point(x, y);
}

long double Distance(const Line& line1, const Line& line2) {
  auto vector1 = Vector(NullPoint(line1));
  auto vector2 = Vector(NullPoint(line2));
  auto vector = vector1 - vector2;
  auto normal_vector = NormalVector(line2);
  return static_cast<long double>(abs(ScalarProduct(vector, normal_vector))) / normal_vector.GetL();
}

long double Distance(const Line& line, const Point& point) {
  return (static_cast<long double>(abs(line.GetA() * point.GetX() + line.GetB() * point.GetY() + line.GetC()))) /
         (sqrt(line.GetA() * line.GetA() + line.GetB() * line.GetB()));
}

long double Distance(const Point& point, const Line& line) {
  return (static_cast<long double>(abs(line.GetA() * point.GetX() + line.GetB() * point.GetY() + line.GetC()))) /
         (sqrt(line.GetA() * line.GetA() + line.GetB() * line.GetB()));
}

bool operator==(const Line& line1, const Line& line2) {
  return (line1.GetA() * line2.GetB() == line1.GetB() * line2.GetA()) &&
         (line1.GetB() * line2.GetC() == line1.GetC() * line2.GetB());
}

bool operator!=(const Line& line1, const Line& line2) {
  return !(line1.GetA() * line2.GetB() == line1.GetB() * line2.GetA()) &&
         (line1.GetB() * line2.GetC() == line1.GetC() * line2.GetB());
}

std::istream& operator>>(std::istream& is, Line& line) {
  is >> line.a_ >> line.b_ >> line.c_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Line& line) {
  os << line.GetA() << " " << line.GetB() << " " << line.GetC() << "\n";
  return os;
}

// Segment

Segment::Segment() {
  point1_ = Point();
  point2_ = Point();
}

Segment::Segment(const Point& point1, const Point& point2) {
  point1_ = point1;
  point2_ = point2;
}

Point Segment::GetA() const {
  return point1_;
}

Point Segment::GetB() const {
  return point2_;
}

long double Distance(const Segment& segment, const Point& point) {
  auto ap = Vector(segment.GetA(), point);
  auto ab = Vector(segment.GetA(), segment.GetB());
  auto bp = Vector(segment.GetB(), point);
  auto ba = Vector(segment.GetB(), segment.GetA());
  if (ScalarProduct(ap, ab) <= 0) {
    return ap.GetL();
  }
  if (ScalarProduct(bp, ba) <= 0) {
    return bp.GetL();
  }
  Line line = Line(segment.GetA(), segment.GetB());
  return Distance(line, point);
}

long double Distance(const Point& point, const Segment& segment) {
  auto ap = Vector(segment.GetA(), point);
  auto ab = Vector(segment.GetA(), segment.GetB());
  auto bp = Vector(segment.GetB(), point);
  auto ba = Vector(segment.GetB(), segment.GetA());
  if (ScalarProduct(ap, ab) <= 0) {
    return ap.GetL();
  }
  if (ScalarProduct(bp, ba) <= 0) {
    return bp.GetL();
  }
  Line line = Line(segment.GetA(), segment.GetB());
  return Distance(line, point);
}

bool IntersectionB(const Segment& segment, const Point& point) {
  auto ap = Vector(segment.GetA(), point);
  auto pb = Vector(point, segment.GetB());
  return VectorProduct(ap, pb) == 0 && ScalarProduct(ap, pb) >= 0;
}

bool IntersectionB(const Point& point, const Segment& segment) {
  auto ap = Vector(segment.GetA(), point);
  auto pb = Vector(point, segment.GetB());
  return VectorProduct(ap, pb) == 0 && ScalarProduct(ap, pb) >= 0;
}

bool IntersectionB(const Segment& segment, const Line& line) {
  auto point1 = segment.GetA();
  auto point2 = segment.GetB();
  return (line.GetA() * point1.GetX() + line.GetB() * point1.GetY() + line.GetC()) *
             (line.GetA() * point2.GetX() + line.GetB() * point2.GetY() + line.GetC()) <=
         0;
}

bool IntersectionB(const Line& line, const Segment& segment) {
  auto point1 = segment.GetA();
  auto point2 = segment.GetB();
  return (line.GetA() * point1.GetX() + line.GetB() * point1.GetY() + line.GetC()) *
             (line.GetA() * point2.GetX() + line.GetB() * point2.GetY() + line.GetC()) <=
         0;
}

bool IntersectionC(const Segment& segment, const Line& line) {
  auto point1 = segment.GetA();
  auto point2 = segment.GetB();
  return (line.GetA() * point1.GetX() + line.GetB() * point1.GetY() + line.GetC()) == 0 &&
         (line.GetA() * point2.GetX() + line.GetB() * point2.GetY() + line.GetC()) == 0;
}

bool IntersectionC(const Line& line, const Segment& segment) {
  auto point1 = segment.GetA();
  auto point2 = segment.GetB();
  return (line.GetA() * point1.GetX() + line.GetB() * point1.GetY() + line.GetC()) == 0 &&
         (line.GetA() * point2.GetX() + line.GetB() * point2.GetY() + line.GetC()) == 0;
}

bool IntersectionB(const Segment& segment1, const Segment& segment2) {
  auto line1 = Line(segment1);
  auto line2 = Line(segment2);
  if (IntersectionB(segment1, line2) && IntersectionB(segment2, line1)) {
    if (IntersectionC(segment1, line2) && IntersectionC(segment2, line1)) {
      return (IntersectionB(segment1, segment2.GetA())) || (IntersectionB(segment1, segment2.GetB())) ||
             (IntersectionB(segment2, segment1.GetA())) || (IntersectionB(segment2, segment1.GetB()));
    }
    return true;
  }
  return false;
}

bool IntersectionB(const Segment& segment, const Ray& ray) {
  auto line = Line(ray.GetP(), ray.GetV());
  if (IntersectionB(segment, line)) {
    auto ao = ray.GetP() - segment.GetA();
    auto vector = ray.GetV();
    auto ab = segment.GetB() - segment.GetA();
    return VectorProduct(ao, ab) * VectorProduct(vector, ab) < 0 || (VectorProduct(ao, ab) == 0) ||
           (VectorProduct(ao, ab) == 0 && VectorProduct(vector, ab) == 0);
  }
  return false;
}

bool IntersectionB(const Ray& ray, const Segment& segment) {
  auto line = Line(ray.GetP(), ray.GetV());
  if (IntersectionB(segment, line)) {
    auto ao = ray.GetP() - segment.GetA();
    auto vector = ray.GetV();
    auto ab = segment.GetB() - segment.GetA();
    return VectorProduct(ao, ab) * VectorProduct(vector, ab) < 0 || (VectorProduct(ao, ab) == 0) ||
           (VectorProduct(ao, ab) == 0 && VectorProduct(vector, ab) == 0);
  }
  return false;
}

long double Distance(const Segment& segment1, const Segment& segment2) {
  if (IntersectionB(segment1, segment2)) {
    return 0;
  }
  if (segment1.GetA() == segment1.GetB()) {
    if (segment2.GetA() == segment2.GetB()) {
      return Distance(segment1.GetA(), segment2.GetA());
    }
    return Distance(segment2, segment1.GetA());
  }
  if (segment2.GetA() == segment2.GetB()) {
    return Distance(segment1, segment2.GetA());
  }
  long double ans = Distance(segment1.GetA(), segment2);
  ans = std::min(ans, Distance(segment1.GetB(), segment2));
  ans = std::min(ans, Distance(segment2.GetA(), segment1));
  ans = std::min(ans, Distance(segment2.GetB(), segment1));
  return ans;
}

std::istream& operator>>(std::istream& is, Segment& segment) {
  std::cin >> segment.point1_ >> segment.point2_;
  return is;
}

// Ray

Ray::Ray() {
  point_ = Point();
  vector_ = Vector();
}

Ray::Ray(const Point& point, const Vector& vector) {
  point_ = point;
  vector_ = vector;
}

Ray::Ray(const Point& point1, const Point& point2) {
  Vector vector = Vector(point1, point2);
  point_ = point1;
  vector_ = vector;
}

Vector Ray::GetV() const {
  return vector_;
}

Point Ray::GetP() const {
  return point_;
}

bool IntersectionB(const Ray& ray, const Point& point) {
  auto op = Vector(ray.GetP(), point);
  return ScalarProduct(ray.GetV(), op) >= 0 && VectorProduct(ray.GetV(), op) == 0;
}

bool IntersectionB(const Point& point, const Ray& ray) {
  auto op = Vector(ray.GetP(), point);
  return ScalarProduct(ray.GetV(), op) >= 0 && VectorProduct(ray.GetV(), op) == 0;
}

long double Distance(const Ray& ray, const Point& point) {
  auto op = Vector(ray.GetP(), point);
  if (ScalarProduct(ray.GetV(), op) > 0) {
    return static_cast<long double>(abs(VectorProduct(ray.GetV(), op))) / ray.GetV().GetL();
  }
  return op.GetL();
}

long double Distance(const Point& point, const Ray& ray) {
  auto op = Vector(ray.GetP(), point);
  if (ScalarProduct(ray.GetV(), op) > 0) {
    return static_cast<long double>(abs(VectorProduct(ray.GetV(), op))) / ray.GetV().GetL();
  }
  return op.GetL();
}

// Polygon

Polygon::Polygon() {
  points_.resize(0);
}

Polygon::Polygon(size_t size) {
  points_.resize(size);
}

void Polygon::Push(Point& point) {
  points_.push_back(point);
}

void Polygon::Del(size_t i) {
  points_.erase(points_.begin() + i);
}

size_t Polygon::Size() const {
  return points_.size();
}

std::vector<Point>& Polygon::Points() const {
  return link_;
}

long double Polygon::Area() const {
  uint64_t area_plus = 0;
  uint64_t area_minus = 0;
  int64_t area = 0;
  for (size_t i = 0; i < points_.size(); ++i) {
    auto a = Vector(points_[i]);
    auto b = Vector(points_[(i + 1) % points_.size()]);
    area = VectorProduct(b, a);
    if (area > 0) {
      area_plus += area;
    } else {
      area_minus -= area;
    }
  }
  return static_cast<long double>(std::max(area_plus, area_minus) - std::min(area_plus, area_minus)) / 2;
}

bool IsConvex(const Polygon& pol) {
  if (pol.Points()[0] == pol.Points()[pol.Size() - 1]) {
    return false;
  }
  for (uint64_t i = 0; i < pol.Size() - 1; ++i) {
    if (pol.Points()[i] == pol.Points()[i + 1]) {
      return false;
    }
  }
  long double tmp = 0;
  bool flag = true;
  Vector ab, bc;
  for (uint64_t i = 0; i < pol.Size() - 2; ++i) {
    ab = Vector(pol.Points()[i], pol.Points()[i + 1]);
    bc = Vector(pol.Points()[i + 1], pol.Points()[i + 2]);
    if (VectorProduct(ab, bc) != 0) {
      tmp = VectorProduct(ab, bc);
      flag = false;
      break;
    }
  }
  if (flag) {
    ab = Vector(pol.Points()[pol.Size() - 2], pol.Points()[pol.Size() - 1]);
    bc = Vector(pol.Points()[pol.Size() - 1], pol.Points()[0]);
    if (VectorProduct(ab, bc) != 0) {
      tmp = VectorProduct(ab, bc);
      flag = false;
    }
    if (flag) {
      ab = Vector(pol.Points()[pol.Size() - 1], pol.Points()[0]);
      bc = Vector(pol.Points()[0], pol.Points()[1]);
      if (VectorProduct(ab, bc) != 0) {
        tmp = VectorProduct(ab, bc);
        flag = false;
      }
    }
  }
  if (flag) {
    return true;
  }
  for (uint64_t i = 0; i < pol.Size() - 2; ++i) {
    ab = Vector(pol.Points()[i], pol.Points()[i + 1]);
    bc = Vector(pol.Points()[i + 1], pol.Points()[i + 2]);
    if (VectorProduct(ab, bc) * tmp < 0) {
      return false;
    }
  }
  ab = Vector(pol.Points()[pol.Size() - 2], pol.Points()[pol.Size() - 1]);
  bc = Vector(pol.Points()[pol.Size() - 1], pol.Points()[0]);
  if (VectorProduct(ab, bc) * tmp < 0) {
    return false;
  }
  ab = Vector(pol.Points()[pol.Size() - 1], pol.Points()[0]);
  bc = Vector(pol.Points()[0], pol.Points()[1]);
  return VectorProduct(ab, bc) * tmp >= 0;
}

bool IsInside(const Polygon& pol, const Point& point) {
  auto ray = Ray(point, Point(point.GetX() + 1, point.GetY() + 100001));
  uint64_t cnt = 0;
  for (size_t i = 0; i < pol.Size(); ++i) {
    if (!(pol.Points()[i] == pol.Points()[(i + 1) % pol.Size()])) {
      auto segment = Segment(pol.Points()[i], pol.Points()[(i + 1) % pol.Size()]);
      if (IntersectionB(point, segment)) {
        return true;
      }
      if (IntersectionB(ray, segment)) {
        ++cnt;
      }
    }
  }
  bool isline = true;
  for (size_t i = 0; i < pol.Size(); ++i) {
    auto a = Vector(pol.Points()[i], pol.Points()[(i + 1) % pol.Size()]);
    auto b = Vector(pol.Points()[(i + 1) % pol.Size()], pol.Points()[(i + 2) % pol.Size()]);
    if (VectorProduct(a, b) != 0) {
      isline = false;
      break;
    }
  }
  if (isline) {
    return false;
  }
  return cnt % 2 == 1;
}

bool IntersectionB(const Polygon& pol, const Point& point) {
  for (size_t i = 0; i < pol.Size(); ++i) {
    if (pol.Points()[i] != pol.Points()[(i + 1) % pol.Size()]) {
      auto segment = Segment(pol.Points()[i], pol.Points()[(i + 1) % pol.Size()]);
      if (IntersectionB(point, segment)) {
        return true;
      }
    } else {
      if (point == pol.Points()[i]) {
        return true;
      }
    }
  }
  return false;
}

Polygon ConvexHull(const Polygon& pol) {
  if (pol.Size() < 2) {
    return pol;
  }
  std::vector<Point> vec(pol.Points());
  auto p0 = vec[0];
  for (const auto& point : vec) {
    if (point.GetY() < p0.GetY() || (point.GetY() == p0.GetY() && point.GetX() < p0.GetX())) {
      p0 = point;
    }
  }
  std::sort(vec.begin(), vec.end(), [&p0](const Point pa, const Point pb) {
    auto a = Vector(p0, pa);
    auto b = Vector(p0, pb);
    long double angle = VectorProduct(a, b);
    return (angle ? angle > 0 : (a.GetY() != b.GetY() ? a.GetY() < b.GetY() : a.GetX() < b.GetX()));
  });
  std::vector<Point> stack{vec[0], vec[1]};
  for (size_t i = 2; i < vec.size(); ++i) {
    auto point = vec[i];
    auto q = stack.back();
    auto ray = stack[stack.size() - 2];
    while (VectorProduct(Vector(ray, q), Vector(ray, point)) <= 0) {
      stack.pop_back();
      if (stack.size() < 2) {
        break;
      }
      q = stack.back();
      ray = stack[stack.size() - 2];
    }
    stack.push_back(point);
  }
  auto ans = Polygon();
  ans.Push(stack[0]);
  for (size_t i = stack.size() - 1; i > 0; --i) {
    ans.Push(stack[i]);
  }
  return ans;
}

Polygon ConvexHullJarvis(const Polygon& pol) {
  std::vector<Point> points(pol.Points());
  std::vector<Point> vec;
  for (size_t i = 0; i < pol.Size(); ++i) {
    if (points[i].GetX() < points[0].GetX() ||
        (points[i].GetX() == points[0].GetX() && points[i].GetY() < points[0].GetY())) {
      std::swap(points[i], points[0]);
    }
  }
  uint64_t tmp = 0;
  while (true) {
    vec.push_back(points[tmp]);
    uint64_t next = pol.Size() - 1;
    for (size_t i = 0; i < points.size(); ++i) {
      auto ab = Vector(points[tmp], points[i]);
      auto bc = Vector(points[tmp], points[next]);
      if (i != tmp && (next == pol.Size() - 1 || VectorProduct(ab, bc) <= 0)) {
        if (next == pol.Size() - 1 || VectorProduct(ab, bc) != 0) {
          next = i;
        } else {
          if (ab.GetL() > bc.GetL()) {
            next = i;
          }
        }
      }
    }
    if (next == 0) {
      break;
    }
    tmp = next;
  }
  auto ans = Polygon();
  for (size_t i = 0; i < vec.size(); ++i) {
    ans.Push(vec[i]);
  }
  return ans;
}

// std::vector<Polygon> Infection(const Polygon& pol) {
//   std::vector<Polygon> ans;
//   auto pol_copy = pol;
//   while (pol_copy.Size() > 2) {
//     auto convex_hull = ConvexHull(pol_copy);
//     ans.push_back(convex_hull);
//     if (convex_hull.Area() == 0) {
//       break;
//     }
//     auto pol_copy_new = Polygon();
//     for (size_t i = 0; i < pol_copy.Size(); ++i) {
//       if (!IntersectionB(convex_hull, pol_copy.Points()[i])) {
//         pol_copy_new.Push(pol_copy.Points()[i]);
//       }
//     }
//     pol_copy.Points() = pol_copy_new.Points();
//   }
//   return ans;
// }

// size_t WhereInInfection(const std::vector<Polygon>& inf, const Point& point) {
//   for (size_t i = inf.size() - 1; i >= 0; --i) {
//     if (IsInside(inf[i], point)) {
//       return i;
//     }
//   }
//   return 0;
// }

std::istream& operator>>(std::istream& is, Polygon& pol) {
  for (size_t i = 0; i < pol.Size(); ++i) {
    is >> pol.points_[i];
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, Polygon& pol) {
  for (size_t i = 0; i < pol.Size(); ++i) {
    os << pol.points_[i] << "\n";
  }
  return os;
}

int main() {
  uint64_t n;
  std::cin >> n;
  auto pol = Polygon(n);
  std::cin >> pol;
  auto ch = ConvexHullJarvis(pol);
  std::cout << ch.Size() << '\n';
  std::cout << ch;
  std::cout << std::fixed;
  std::cout << std::setprecision(1);
  std::cout << ch.Area();
  return 0;
}