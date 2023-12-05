#include <iostream>
#include <iomanip>
#include <cmath>

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
  long double GetX() const;
  long double GetY() const;
  long double Distance(const Point&, const Point&);
  friend std::istream& operator>>(std::istream&, Point&);
  friend std::ostream& operator<<(std::ostream&, const Point&);
  friend bool operator==(const Point&, const Point&);
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
  Point GetP() const;
  long double ScalarProduct(const Vector&, const Vector&);
  long double VectorProduct(const Vector&, const Vector&);
  friend Vector operator*(long double, const Vector&);
  friend Vector operator/(const Vector&, long double n);
  friend Vector operator+(const Vector&, const Vector&);
  friend Vector operator-(const Vector&, const Vector&);
  friend std::istream& operator>>(std::istream&, Vector&);
  friend std::ostream& operator<<(std::ostream&, const Vector&);
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
  bool IntersectionB(const Segment&, const Point&);
  bool IntersectionB(const Segment&, const Line&);
  bool IntersectionB(const Segment&, const Segment&);
  bool IntersectionC(const Segment&, const Segment&);
  long double Distance(const Segment&, const Segment&);
  friend std::istream& operator>>(std::istream&, Segment&);
  Segment& operator=(const Segment&);
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
  bool Equals(const Line&, const Line&);
  bool IntersectionB(const Line&, const Line&);
  bool IntersectionB(const Line&, const Point&);
  Point NullPoint(const Line&);
  Point IntersectionP(const Line&, const Line&);
  Point PerpendicularP(const Line&, const Point&);
  long double Distance(const Line&, const Line&);
  long double Distance(const Line&, const Point&);
  friend std::istream& operator>>(std::istream&, Line&);
  friend std::ostream& operator<<(std::ostream&, const Line&);
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
  long double Distance(const Ray&, const Point&);
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

Point Vector::GetP() const {
  Point p = Point(x_, y_);
  return p;
}

long double ScalarProduct(const Vector& a, const Vector& b) {
  return a.GetX() * b.GetX() + a.GetY() * b.GetY();
}

long double VectorProduct(const Vector& a, const Vector& b) {
  return a.GetX() * b.GetY() - a.GetY() * b.GetX();
}

Vector operator*(long double n, const Vector& v) {
  Vector a = Vector(v.GetX() * n, v.GetY() * n);
  return a;
}

Vector operator/(const Vector& v, long double n) {
  Vector a = Vector(v.GetX() / n, v.GetY() / n);
  return a;
}

Vector operator+(const Vector& a, const Vector& b) {
  Vector c = Vector(a.GetX() + b.GetX(), a.GetY() + b.GetY());
  return c;
}

Vector operator-(const Vector& a, const Vector& b) {
  Vector c = Vector(a.GetX() - b.GetX(), a.GetY() - b.GetY());
  return c;
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
  Vector v = Vector(a, b);
  a_ = v.GetY();
  b_ = -v.GetX();
  c_ = v.GetX() * a.GetY() - v.GetY() * a.GetX();
}

Line::Line(const Segment& sg) {
  Point a = sg.GetA();
  Point b = sg.GetB();
  Vector t = Vector(a, b);
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
  Vector v = Vector(-l.GetB(), l.GetA());
  return v;
}

Vector NormalVector(const Line& l) {
  Vector v = Vector(l.GetA(), l.GetB());
  return v;
}

bool Parallel(const Line& l1, const Line& l2) {
  Vector v1 = GuidingVector(l1);
  Vector v2 = GuidingVector(l2);
  return VectorProduct(v1, v2) == 0;
}

bool Equals(const Line& l1, const Line& l2) {
  return (l1.GetA() * l2.GetB() == l1.GetB() * l2.GetA()) && (l1.GetB() * l2.GetC() == l1.GetC() * l2.GetB());
}

bool IntersectionB(const Line& l1, const Line& l2) {
  if (Equals(l1, l2)) {
    return true;
  }
  return l1.GetA() * l2.GetB() != l1.GetB() * l2.GetA();
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
  Point p = Point(x, y);
  return p;
}

Point PerpendicularP(const Line& l, const Point p) {
  auto r_p = Vector(p);
  Vector r_0 = Vector(NullPoint(l));
  Vector a = GuidingVector(l);
  return (((ScalarProduct(a, r_p - r_0)) / (ScalarProduct(a, a))) * a).GetP();
}

long double Distance(const Line& l1, const Line& l2) {
  Vector r1 = Vector(NullPoint(l1));
  Vector r2 = Vector(NullPoint(l2));
  Vector r = r1 - r2;
  Vector n = NormalVector(l2);
  return static_cast<long double>(abs(ScalarProduct(r, n))) / n.GetL();
}

std::istream& operator>>(std::istream& is, Line& l) {
  is >> l.a_ >> l.b_ >> l.c_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Line& l) {
  os << l.GetA() << " " << l.GetB() << " " << l.GetC() << "\n";
  return os;
}

bool IntersectionB(const Line& l, const Point& p) {
  return l.GetA() * p.GetX() + l.GetB() * p.GetY() + l.GetC() == 0;
}

long double Distance(const Line& l, const Point& p) {
  return (static_cast<long double>(abs(l.GetA() * p.GetX() + l.GetB() * p.GetY() + l.GetC()))) /
         (sqrt(l.GetA() * l.GetA() + l.GetB() * l.GetB()));
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
  for (uint64_t i = 0; i < n_ - 1; ++i) {
    auto a = Vector(points_[i]);
    auto b = Vector(points_[i + 1]);
    s += VectorProduct(b, a);
  }
  s += VectorProduct(Vector(points_[0]), Vector(points_[n_ - 1]));
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

std::istream& operator>>(std::istream& is, Polygon& pol) {
  for (uint64_t i = 0; i < pol.Size(); ++i) {
    is >> pol.points_[i];
  }
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
  Vector op = Vector(r.GetP(), p);
  return ScalarProduct(r.GetV(), op) >= 0 && VectorProduct(r.GetV(), op) == 0;
}

long double Distance(const Ray& r, const Point& p) {
  Vector op = Vector(r.GetP(), p);
  if (ScalarProduct(r.GetV(), op) > 0) {
    return static_cast<long double>(abs(VectorProduct(r.GetV(), op))) / r.GetV().GetL();
  }
  return op.GetL();
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

bool IntersectionB(const Segment& sg, const Point& p) {
  Vector ap = Vector(sg.GetA(), p);
  Vector pb = Vector(p, sg.GetB());
  return VectorProduct(ap, pb) == 0 && ScalarProduct(ap, pb) >= 0;
}

long double Distance(const Segment& sg, const Point& p) {
  Vector ap = Vector(sg.GetA(), p);
  Vector ab = Vector(sg.GetA(), sg.GetB());
  Vector bp = Vector(sg.GetB(), p);
  Vector ba = Vector(sg.GetB(), sg.GetA());
  if (ScalarProduct(ap, ab) <= 0) {
    return ap.GetL();
  }
  if (ScalarProduct(bp, ba) <= 0) {
    return bp.GetL();
  }
  Line line = Line(sg.GetA(), sg.GetB());
  return Distance(line, p);
}

std::istream& operator>>(std::istream& is, Segment& sg) {
  std::cin >> sg.a_ >> sg.b_;
  return is;
}

bool IntersectionB(const Segment& sg, const Line& line) {
  Point a = sg.GetA();
  Point b = sg.GetB();
  return (line.GetA() * a.GetX() + line.GetB() * a.GetY() + line.GetC()) *
             (line.GetA() * b.GetX() + line.GetB() * b.GetY() + line.GetC()) <=
         0;
}

bool IntersectionC(const Segment& sg, const Line& line) {
  Point a = sg.GetA();
  Point b = sg.GetB();
  return (line.GetA() * a.GetX() + line.GetB() * a.GetY() + line.GetC()) == 0 &&
         (line.GetA() * b.GetX() + line.GetB() * b.GetY() + line.GetC()) == 0;
}

bool IntersectionB(const Segment& sg1, const Segment& sg2) {
  auto line1 = Line(sg1);
  auto line2 = Line(sg2);
  if (IntersectionB(sg1, line2) && IntersectionB(sg2, line1)) {
    if (IntersectionC(sg1, line2) && IntersectionC(sg2, line1)) {
      return (IntersectionB(sg1, sg2.GetA())) || (IntersectionB(sg1, sg2.GetB())) || (IntersectionB(sg2, sg1.GetA())) ||
             (IntersectionB(sg2, sg1.GetB()));
    }
    return true;
  }
  return false;
}

long double Distance(const Segment& sg1, const Segment& sg2) {
  if (IntersectionB(sg1, sg2)) {
    return 0;
  }
  auto l1 = Line(sg1);
  auto l2 = Line(sg2);
  long double ans = 0;
  if (IntersectionB(sg2, PerpendicularP(l2, sg1.GetA()))) {
    ans = Distance(l2, sg1.GetA());
  } else {
    ans = std::min(Distance(sg1.GetA(), sg2.GetA()), Distance(sg1.GetA(), sg2.GetB()));
  }
  if (IntersectionB(sg2, PerpendicularP(l2, sg1.GetB()))) {
    ans = std::min(ans, Distance(l2, sg1.GetB()));
  } else {
    ans = std::min(ans, std::min(Distance(sg1.GetB(), sg2.GetA()), Distance(sg1.GetB(), sg2.GetB())));
  }
  if (IntersectionB(sg1, PerpendicularP(l1, sg2.GetA()))) {
    ans = std::min(ans, Distance(l1, sg2.GetA()));
  } else {
    ans = std::min(ans, std::min(Distance(sg2.GetA(), sg1.GetA()), Distance(sg2.GetA(), sg1.GetB())));
  }
  if (IntersectionB(sg1, PerpendicularP(l2, sg2.GetB()))) {
    ans = std::min(ans, Distance(l1, sg2.GetB()));
  } else {
    ans = std::min(ans, std::min(Distance(sg2.GetB(), sg1.GetA()), Distance(sg2.GetB(), sg1.GetB())));
  }
  return ans;
}

int main() {
  uint64_t n;
  std::cin >> n;
  Polygon pol = Polygon(n);
  std::cin >> pol;
  if (IsConvex(pol)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  return 0;
}