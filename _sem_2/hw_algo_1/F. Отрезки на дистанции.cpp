#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <vector>

class Point;
class Vector;
class Line;
class Segment;
class Ray;
class Polygon;
class Circle;

class Point {
  long double x_, y_;

 public:
  Point();
  Point(long double, long double);
  explicit Point(const Vector&);
  long double GetX() const;
  long double GetY() const;
  long double Distance(const Point&, const Point&);
  friend std::istream& operator>>(std::istream&, Point&);
  friend std::ostream& operator<<(std::ostream&, const Point&);
  friend bool operator==(const Point&, const Point&);
  friend Vector operator-(const Point&, const Point&);
};

class Vector {
  long double x_, y_;

 public:
  Vector();
  Vector(long double, long double);
  Vector(long double, long double, long double, long double);
  explicit Vector(const Point&);
  Vector(const Point&, const Point&);
  long double GetX() const;
  long double GetY() const;
  long double GetL() const;
  long double ScalarProduct(const Vector&, const Vector&);
  long double VectorProduct(const Vector&, const Vector&);
  friend Vector operator*(long double, const Vector&);
  friend Vector operator*(const Vector&, long double);
  friend Vector operator/(const Vector&, long double n);
  friend Vector operator+(const Vector&, const Vector&);
  friend Vector operator-(const Vector&, const Vector&);
  friend std::istream& operator>>(std::istream&, Vector&);
  friend std::ostream& operator<<(std::ostream&, const Vector&);
};

class Line {
  long double a_, b_, c_;

 public:
  Line();
  Line(long double, long double, long double);
  Line(const Point&, const Vector&);
  Line(const Point&, const Point&);
  explicit Line(const Segment&);
  long double GetA() const;
  long double GetB() const;
  long double GetC() const;
  Vector GuidingVector(const Line&);
  Vector NormalVector(const Line&);
  bool Parallel(const Line&, const Line&);
  bool IntersectionB(const Line&, const Line&);
  bool IntersectionB(const Line&, const Point&);
  bool IntersectionB(const Point&, const Line&);
  Point NullPoint(const Line&);
  Point IntersectionP(const Line&, const Line&);
  Point PerpendicularP(const Line&, const Point&);
  long double Distance(const Line&, const Line&);
  long double Distance(const Line&, const Point&);
  long double Distance(const Point&, const Line&);
  friend bool operator==(const Line&, const Line&);
  friend std::istream& operator>>(std::istream&, Line&);
  friend std::ostream& operator<<(std::ostream&, const Line&);
};

class Segment {
  Point a_;
  Point b_;

 public:
  Segment();
  Segment(const Point&, const Point&);
  Point GetA() const;
  Point GetB() const;
  long double Distance(const Segment&, const Point&);
  long double Distance(const Point&, const Segment&);
  long double Distance(const Segment&, const Segment&);  //!!!
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
  Point p_;
  Vector v_;

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
  Point* points_;
  uint64_t n_;

 public:
  explicit Polygon(uint64_t);
  uint64_t Size() const;
  Point* Points() const;
  friend std::istream& operator>>(std::istream&, Polygon&);
  long double Area() const;
  bool IsConvex(const Polygon&);
  bool Inside(const Polygon&, const Point&);  //!!!
  ~Polygon() {
    delete[] points_;
  }
};

class Circle {};

// Point

Point::Point() {
  x_ = 0;
  y_ = 0;
}

Point::Point(long double x, long double y) {
  x_ = x;
  y_ = y;
}

Point::Point(const Vector& v) {
  x_ = v.GetX();
  y_ = v.GetY();
}

long double Point::GetX() const {
  return x_;
}

long double Point::GetY() const {
  return y_;
}

long double Distance(const Point& a, const Point& b) {
  return sqrt((a.GetX() - b.GetX()) * (a.GetX() - b.GetX()) + (a.GetY() - b.GetY()) * (a.GetY() - b.GetY()));
}

std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x_ >> p.y_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << p.GetX() << " " << p.GetY();
  return os;
}

bool operator==(const Point& a, const Point& b) {
  return (a.GetX() == b.GetX()) && (a.GetY() == b.GetY());
}

Vector operator-(const Point& a, const Point& b) {
  return Vector(b, a);
}

// Vector

Vector::Vector() {
  x_ = 0;
  y_ = 0;
}

Vector::Vector(long double x, long double y) {
  x_ = x;
  y_ = y;
}

Vector::Vector(long double x0, long double y0, long double x1, long double y1) {
  x_ = x1 - x0;
  y_ = y1 - y0;
}

Vector::Vector(const Point& p) {
  x_ = p.GetX();
  y_ = p.GetY();
}

Vector::Vector(const Point& a, const Point& b) {
  x_ = b.GetX() - a.GetX();
  y_ = b.GetY() - a.GetY();
}

long double Vector::GetX() const {
  return x_;
}

long double Vector::GetY() const {
  return y_;
}

long double Vector::GetL() const {
  return sqrt(x_ * x_ + y_ * y_);
}

long double ScalarProduct(const Vector& a, const Vector& b) {
  return a.GetX() * b.GetX() + a.GetY() * b.GetY();
}

long double VectorProduct(const Vector& a, const Vector& b) {
  return a.GetX() * b.GetY() - a.GetY() * b.GetX();
}

Vector operator*(long double n, const Vector& v) {
  return Vector(v.GetX() * n, v.GetY() * n);
}

Vector operator*(const Vector& v, long double n) {
  return Vector(v.GetX() * n, v.GetY() * n);
}

Vector operator/(const Vector& v, long double n) {
  return Vector(v.GetX() / n, v.GetY() / n);
}

Vector operator+(const Vector& a, const Vector& b) {
  return Vector(a.GetX() + b.GetX(), a.GetY() + b.GetY());
}

Vector operator-(const Vector& a, const Vector& b) {
  return Vector(a.GetX() - b.GetX(), a.GetY() - b.GetY());
}

std::istream& operator>>(std::istream& is, Vector& v) {
  long double start_x, start_y, end_x, end_y;
  is >> start_x >> start_y >> end_x >> end_y;
  v.x_ = end_x - start_x;
  v.y_ = end_y - start_y;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
  os << v.GetX() << " " << v.GetY();
  return os;
}

// Line

Line::Line() {
  a_ = 0;
  b_ = 0;
  c_ = 0;
}

Line::Line(long double a, long double b, long double c) {
  a_ = a;
  b_ = b;
  c_ = c;
}

Line::Line(const Point& p, const Vector& v) {
  a_ = v.GetY();
  b_ = -v.GetX();
  c_ = v.GetX() * p.GetY() - v.GetY() * p.GetX();
}

Line::Line(const Point& a, const Point& b) {
  auto v = Vector(a, b);
  a_ = v.GetY();
  b_ = -v.GetX();
  c_ = v.GetX() * a.GetY() - v.GetY() * a.GetX();
}

Line::Line(const Segment& sg) {
  auto a = sg.GetA();
  auto b = sg.GetB();
  auto t = Vector(a, b);
  a_ = t.GetY();
  b_ = -t.GetX();
  c_ = -a.GetX() * t.GetY() + a.GetY() * t.GetX();
}

long double Line::GetA() const {
  return a_;
}

long double Line::GetB() const {
  return b_;
}

long double Line::GetC() const {
  return c_;
}

Vector GuidingVector(const Line& l) {
  return Vector(-l.GetB(), l.GetA());
}

Vector NormalVector(const Line& l) {
  return Vector(l.GetA(), l.GetB());
}

bool Parallel(const Line& l1, const Line& l2) {
  auto v1 = GuidingVector(l1);
  auto v2 = GuidingVector(l2);
  return VectorProduct(v1, v2) == 0;
}

bool IntersectionB(const Line& l1, const Line& l2) {
  if (l1 == l2) {
    return true;
  }
  return l1.GetA() * l2.GetB() != l1.GetB() * l2.GetA();
}

bool IntersectionB(const Line& l, const Point& p) {
  return l.GetA() * p.GetX() + l.GetB() * p.GetY() + l.GetC() == 0;
}

bool IntersectionB(const Point& p, const Line& l) {
  return l.GetA() * p.GetX() + l.GetB() * p.GetY() + l.GetC() == 0;
}

Point NullPoint(const Line& l) {
  long double x, y;
  if (l.GetA() == 0) {
    x = 0;
    y = -l.GetC() / l.GetB();
  } else if (l.GetB() == 0) {
    x = -l.GetC() / l.GetA();
    y = 0;
  } else {
    x = -(l.GetC()) / (2 * l.GetA());
    y = -(l.GetC()) / (2 * l.GetB());
  }
  return Point(x, y);
}

Point IntersectionP(const Line& l1, const Line& l2) {
  long double delta = l1.GetA() * l2.GetB() - l1.GetB() * l2.GetA();
  long double delta_x = -l1.GetC() * l2.GetB() + l1.GetB() * l2.GetC();
  long double delta_y = -l1.GetA() * l2.GetC() + l1.GetC() * l2.GetA();
  long double x = delta_x / delta;
  long double y = delta_y / delta;
  return Point(x, y);
}

Point PerpendicularP(const Line& l, const Point& p) {
  auto r_p = Vector(p);
  auto r_0 = Vector(NullPoint(l));
  auto a = GuidingVector(l);
  return Point(r_0 + ((ScalarProduct(a, r_p - r_0)) / (ScalarProduct(a, a))) * a);
}

long double Distance(const Line& l1, const Line& l2) {
  auto r1 = Vector(NullPoint(l1));
  auto r2 = Vector(NullPoint(l2));
  auto r = r1 - r2;
  auto n = NormalVector(l2);
  return static_cast<long double>(abs(ScalarProduct(r, n))) / n.GetL();
}

long double Distance(const Line& l, const Point& p) {
  return (static_cast<long double>(abs(l.GetA() * p.GetX() + l.GetB() * p.GetY() + l.GetC()))) /
         (sqrt(l.GetA() * l.GetA() + l.GetB() * l.GetB()));
}

long double Distance(const Point& p, const Line& l) {
  return (static_cast<long double>(abs(l.GetA() * p.GetX() + l.GetB() * p.GetY() + l.GetC()))) /
         (sqrt(l.GetA() * l.GetA() + l.GetB() * l.GetB()));
}

bool operator==(const Line& l1, const Line& l2) {
  return (l1.GetA() * l2.GetB() == l1.GetB() * l2.GetA()) && (l1.GetB() * l2.GetC() == l1.GetC() * l2.GetB());
}

std::istream& operator>>(std::istream& is, Line& l) {
  is >> l.a_ >> l.b_ >> l.c_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Line& l) {
  os << l.GetA() << " " << l.GetB() << " " << l.GetC() << "\n";
  return os;
}

// Segment

Segment::Segment() {
  a_ = Point();
  b_ = Point();
}

Segment::Segment(const Point& a, const Point& b) {
  a_ = a;
  b_ = b;
}

Point Segment::GetA() const {
  return a_;
}

Point Segment::GetB() const {
  return b_;
}

long double Distance(const Segment& sg, const Point& p) {
  auto ap = Vector(sg.GetA(), p);
  auto ab = Vector(sg.GetA(), sg.GetB());
  auto bp = Vector(sg.GetB(), p);
  auto ba = Vector(sg.GetB(), sg.GetA());
  if (ScalarProduct(ap, ab) <= 0) {
    return ap.GetL();
  }
  if (ScalarProduct(bp, ba) <= 0) {
    return bp.GetL();
  }
  Line l = Line(sg.GetA(), sg.GetB());
  return Distance(l, p);
}

long double Distance(const Point& p, const Segment& sg) {
  auto ap = Vector(sg.GetA(), p);
  auto ab = Vector(sg.GetA(), sg.GetB());
  auto bp = Vector(sg.GetB(), p);
  auto ba = Vector(sg.GetB(), sg.GetA());
  if (ScalarProduct(ap, ab) <= 0) {
    return ap.GetL();
  }
  if (ScalarProduct(bp, ba) <= 0) {
    return bp.GetL();
  }
  Line l = Line(sg.GetA(), sg.GetB());
  return Distance(l, p);
}

bool IntersectionB(const Segment& sg, const Point& p) {
  auto ap = Vector(sg.GetA(), p);
  auto pb = Vector(p, sg.GetB());
  return VectorProduct(ap, pb) == 0 && ScalarProduct(ap, pb) >= 0;
}

bool IntersectionB(const Point& p, const Segment& sg) {
  auto ap = Vector(sg.GetA(), p);
  auto pb = Vector(p, sg.GetB());
  return VectorProduct(ap, pb) == 0 && ScalarProduct(ap, pb) >= 0;
}

bool IntersectionB(const Segment& sg, const Line& l) {
  auto a = sg.GetA();
  auto b = sg.GetB();
  return (l.GetA() * a.GetX() + l.GetB() * a.GetY() + l.GetC()) *
             (l.GetA() * b.GetX() + l.GetB() * b.GetY() + l.GetC()) <=
         0;
}

bool IntersectionB(const Line& l, const Segment& sg) {
  auto a = sg.GetA();
  auto b = sg.GetB();
  return (l.GetA() * a.GetX() + l.GetB() * a.GetY() + l.GetC()) *
             (l.GetA() * b.GetX() + l.GetB() * b.GetY() + l.GetC()) <=
         0;
}

bool IntersectionC(const Segment& sg, const Line& l) {
  auto a = sg.GetA();
  auto b = sg.GetB();
  return (l.GetA() * a.GetX() + l.GetB() * a.GetY() + l.GetC()) == 0 &&
         (l.GetA() * b.GetX() + l.GetB() * b.GetY() + l.GetC()) == 0;
}

bool IntersectionC(const Line& l, const Segment& sg) {
  auto a = sg.GetA();
  auto b = sg.GetB();
  return (l.GetA() * a.GetX() + l.GetB() * a.GetY() + l.GetC()) == 0 &&
         (l.GetA() * b.GetX() + l.GetB() * b.GetY() + l.GetC()) == 0;
}

bool IntersectionB(const Segment& sg1, const Segment& sg2) {
  auto l1 = Line(sg1);
  auto l2 = Line(sg2);
  if (IntersectionB(sg1, l2) && IntersectionB(sg2, l1)) {
    if (IntersectionC(sg1, l2) && IntersectionC(sg2, l1)) {
      return (IntersectionB(sg1, sg2.GetA())) || (IntersectionB(sg1, sg2.GetB())) || (IntersectionB(sg2, sg1.GetA())) ||
             (IntersectionB(sg2, sg1.GetB()));
    }
    return true;
  }
  return false;
}

bool IntersectionB(const Segment& sg, const Ray& r) {
  auto l = Line(r.GetP(), r.GetV());
  if (IntersectionB(sg, l)) {
    auto ao = r.GetP() - sg.GetA();
    auto v = r.GetV();
    auto ab = sg.GetB() - sg.GetA();
    return VectorProduct(ao, ab) * VectorProduct(v, ab) < 0 || (VectorProduct(ao, ab) == 0) ||
           (VectorProduct(ao, ab) == 0 && VectorProduct(v, ab) == 0);
  }
  return false;
}

bool IntersectionB(const Ray& r, const Segment& sg) {
  auto l = Line(r.GetP(), r.GetV());
  if (IntersectionB(sg, l)) {
    auto ao = r.GetP() - sg.GetA();
    auto v = r.GetV();
    auto ab = sg.GetB() - sg.GetA();
    return VectorProduct(ao, ab) * VectorProduct(v, ab) < 0 || (VectorProduct(ao, ab) == 0) ||
           (VectorProduct(ao, ab) == 0 && VectorProduct(v, ab) == 0);
  }
  return false;
}

long double Distance(const Segment& sg1, const Segment& sg2) {
  if (IntersectionB(sg1, sg2)) {
    return 0;
  }
  if (sg1.GetA() == sg1.GetB()) {
    if (sg2.GetA() == sg2.GetB()) {
      return Distance(sg1.GetA(), sg2.GetA());
    }
    return Distance(sg2, sg1.GetA());
  }
  if (sg2.GetA() == sg2.GetB()) {
    return Distance(sg1, sg2.GetA());
  }
  long double d = Distance(sg1.GetA(), sg2);
  d = std::min(d, Distance(sg1.GetB(), sg2));
  d = std::min(d, Distance(sg2.GetA(), sg1));
  d = std::min(d, Distance(sg2.GetB(), sg1));
  return d;
}

std::istream& operator>>(std::istream& is, Segment& sg) {
  std::cin >> sg.a_ >> sg.b_;
  return is;
}

// Ray

Ray::Ray() {
  p_ = Point();
  v_ = Vector();
}

Ray::Ray(const Point& p, const Vector& v) {
  p_ = p;
  v_ = v;
}

Ray::Ray(const Point& a, const Point& b) {
  Vector t = Vector(a, b);
  p_ = a;
  v_ = t;
}

Vector Ray::GetV() const {
  return v_;
}

Point Ray::GetP() const {
  return p_;
}

bool IntersectionB(const Ray& r, const Point& p) {
  auto op = Vector(r.GetP(), p);
  return ScalarProduct(r.GetV(), op) >= 0 && VectorProduct(r.GetV(), op) == 0;
}

bool IntersectionB(const Point& p, const Ray& r) {
  auto op = Vector(r.GetP(), p);
  return ScalarProduct(r.GetV(), op) >= 0 && VectorProduct(r.GetV(), op) == 0;
}

long double Distance(const Ray& r, const Point& p) {
  auto op = Vector(r.GetP(), p);
  if (ScalarProduct(r.GetV(), op) > 0) {
    return static_cast<long double>(abs(VectorProduct(r.GetV(), op))) / r.GetV().GetL();
  }
  return op.GetL();
}

long double Distance(const Point& p, const Ray& r) {
  auto op = Vector(r.GetP(), p);
  if (ScalarProduct(r.GetV(), op) > 0) {
    return static_cast<long double>(abs(VectorProduct(r.GetV(), op))) / r.GetV().GetL();
  }
  return op.GetL();
}

// Polygon

Polygon::Polygon(uint64_t n) {
  points_ = new Point[n];
  n_ = n;
}

uint64_t Polygon::Size() const {
  return n_;
}

Point* Polygon::Points() const {
  return points_;
}

long double Polygon::Area() const {
  long double s = 0;
  for (uint64_t i = 0; i < n_; ++i) {
    auto a = Vector(points_[i]);
    auto b = Vector(points_[(i + 1) % n_]);
    s += VectorProduct(b, a);
  }
  return static_cast<long double>(abs(s)) / 2;
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

bool IsInside(const Polygon& pol, const Point& p) {
  auto r = Ray(p, Point(p.GetX() + 1000000000, p.GetY() + 1));
  uint64_t cnt = 0;
  for (uint64_t i = 0; i < pol.Size(); ++i) {
    if (!(pol.Points()[i] == pol.Points()[(i + 1) % pol.Size()])) {
      auto sg = Segment(pol.Points()[i], pol.Points()[(i + 1) % pol.Size()]);
      if (IntersectionB(p, sg)) {
        return true;
      }
      if (IntersectionB(r, sg)) {
        ++cnt;
      }
    }
  }
  bool isline = true;
  for (uint64_t i = 0; i < pol.Size(); ++i) {
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

std::istream& operator>>(std::istream& is, Polygon& pol) {
  for (uint64_t i = 0; i < pol.Size(); ++i) {
    is >> pol.points_[i];
  }
  return is;
}

int main() {
  Segment sg1 = Segment();
  Segment sg2 = Segment();
  std::cin >> sg1 >> sg2;
  std::cout << std::fixed;
  std::cout << std::setprecision(6);
  std::cout << Distance(sg1, sg2) << "\n";
  return 0;
}