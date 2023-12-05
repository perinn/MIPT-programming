#include <iostream>
#include <iomanip>
#include <cmath>

class Point2D {
  double x_, y_;

 public:
  Point2D();
  Point2D(double, double);
  Point2D(const Point2D&);
  double GetX() const;
  double GetY() const;
  friend std::istream& operator>>(std::istream&, Point2D&);
  friend std::ostream& operator<<(std::ostream&, const Point2D&);
};

Point2D::Point2D() {
  x_ = 0;
  y_ = 0;
}

Point2D::Point2D(double x, double y) {
  x_ = x;
  y_ = y;
}

Point2D::Point2D(const Point2D& p) {
  x_ = p.GetX();
  y_ = p.GetY();
}

double Point2D::GetX() const {
  return x_;
}

double Point2D::GetY() const {
  return y_;
}

std::istream& operator>>(std::istream& is, Point2D& point) {
  is >> point.x_ >> point.y_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Point2D& point) {
  os << point.x_ << " " << point.y_;
  return os;
}

class Vector2D {
  double x_, y_;

 public:
  Vector2D();
  Vector2D(double, double);
  Vector2D(double, double, double, double);
  Vector2D(const Point2D& a, const Point2D& b);
  Vector2D(const Vector2D&);
  double GetX() const;
  double GetY() const;
  double Lenght(const Vector2D&);
  double ScalarProduct(const Vector2D&, const Vector2D&);
  double VectorProduct(const Vector2D&, const Vector2D&);
  friend Vector2D operator+(const Vector2D&, const Vector2D&);
  friend Vector2D operator-(const Vector2D&, const Vector2D&);
  friend std::istream& operator>>(std::istream&, Vector2D&);
  friend std::ostream& operator<<(std::ostream&, const Vector2D&);
};

Vector2D::Vector2D() {
  x_ = 0;
  y_ = 0;
}

Vector2D::Vector2D(double x_0, double y_0) {
  x_ = x_0;
  y_ = y_0;
}

Vector2D::Vector2D(double x_0, double y_0, double x_1, double y_1) {
  x_ = x_1 - x_0;
  y_ = y_1 - y_0;
}

Vector2D::Vector2D(const Point2D& a, const Point2D& b) {
  x_ = b.GetX() - a.GetX();
  y_ = b.GetY() - a.GetY();
}

Vector2D::Vector2D(const Vector2D& v) {
  x_ = v.GetX();
  y_ = v.GetY();
}

double Vector2D::GetX() const {
  return x_;
}

double Vector2D::GetY() const {
  return y_;
}

double Lenght(const Vector2D& a) {
  return sqrt(a.GetX() * a.GetX() + a.GetY() * a.GetY());
}

double ScalarProduct(const Vector2D& a, const Vector2D& b) {
  return a.GetX() * b.GetX() + a.GetY() * b.GetY();
}

double VectorProduct(const Vector2D& a, const Vector2D& b) {
  return a.GetX() * b.GetY() - a.GetY() * b.GetX();
}

Vector2D operator+(const Vector2D& a, const Vector2D& b) {
  Vector2D c = Vector2D(a.GetX() + b.GetX(), a.GetY() + b.GetY());
  return c;
}

Vector2D operator-(const Vector2D& a, const Vector2D& b) {
  Vector2D c = Vector2D(a.GetX() - b.GetX(), a.GetY() - b.GetY());
  return c;
}

std::istream& operator>>(std::istream& is, Vector2D& a) {
  double start_x, start_y, end_x, end_y;
  is >> start_x >> start_y >> end_x >> end_y;
  a.x_ = end_x - start_x;
  a.y_ = end_y - start_y;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Vector2D& a) {
  os << a.GetX() << " " << a.GetY();
  return os;
}

class Line2D {
  double a_, b_, c_;

 public:
  Line2D();
  Line2D(double, double, double);
  Line2D(const Point2D&, const Vector2D&);
  Line2D(const Point2D&, const Point2D&);
  double GetA() const;
  double GetB() const;
  double GetC() const;
  Vector2D GuidingVector2D(const Line2D&);
  Vector2D NormalVector2D(const Line2D&);
  double DistanceLine2DLine2D(const Line2D&, const Line2D&);
  Point2D IntersectionLine2DLine2D(const Line2D&, const Line2D&);
  bool IntersectionLine2DPoint2D(const Line2D&, const Point2D&);
  double DistanceLine2DPoint2D(const Line2D&, const Point2D&);
  friend std::istream& operator>>(std::istream&, Line2D&);
  friend std::ostream& operator<<(std::ostream&, const Line2D&);
};

Line2D::Line2D() {
  a_ = 0;
  b_ = 0;
  c_ = 0;
}

Line2D::Line2D(double a, double b, double c) {
  a_ = a;
  b_ = b;
  c_ = c;
}

Line2D::Line2D(const Point2D& p, const Vector2D& a) {
  a_ = a.GetY();
  b_ = -a.GetX();
  c_ = -p.GetX() * a.GetY() + p.GetY() * a.GetX();
}

Line2D::Line2D(const Point2D& a, const Point2D& b) {
  Vector2D t = Vector2D(a, b);
  a_ = t.GetY();
  b_ = -t.GetX();
  c_ = -a.GetX() * t.GetY() + a.GetY() * t.GetX();
}

double Line2D::GetA() const {
  return a_;
}

double Line2D::GetB() const {
  return b_;
}

double Line2D::GetC() const {
  return c_;
}

Vector2D GuidingVector2D(const Line2D& line) {
  Vector2D a = Vector2D(-line.GetB(), line.GetA());
  return a;
}

Vector2D NormalVector2D(const Line2D& line) {
  Vector2D a = Vector2D(line.GetA(), line.GetB());
  return a;
}

double DistanceLine2DLine2D(const Line2D& line1, const Line2D& line2) {
  if (VectorProduct(GuidingVector2D(line1), GuidingVector2D(line2)) != 0) {
    return 0;
  }
  double x1, y1, x2, y2;
  if (line1.GetA() == 0) {
    x1 = 0;
    y1 = -line1.GetC() / line1.GetB();
  } else if (line1.GetB() == 0) {
    x1 = -line1.GetC() / line1.GetA();
    y1 = 0;
  } else {
    x1 = -(line1.GetC()) / (2 * line1.GetA());
    y1 = -(line1.GetC()) / (2 * line1.GetB());
  }
  if (line2.GetA() == 0) {
    x2 = 0;
    y2 = -line2.GetC() / line2.GetB();
  } else if (line2.GetB() == 0) {
    x2 = -line2.GetC() / line2.GetA();
    y2 = 0;
  } else {
    x2 = -(line2.GetC()) / (2 * line2.GetA());
    y2 = -(line2.GetC()) / (2 * line2.GetB());
  }
  Vector2D r1 = Vector2D(x1, y1);
  Vector2D r2 = Vector2D(x2, y2);
  Vector2D r = r1 - r2;
  Vector2D n = NormalVector2D(line2);
  return static_cast<double>(abs(ScalarProduct(r, n))) / Lenght(n);
}

Point2D IntersectionLine2DLine2D(const Line2D& line1, const Line2D& line2) {
  Point2D point = Point2D((-line1.GetC() * line2.GetB() + line1.GetB() * line2.GetC()) /
                              (line1.GetA() * line2.GetB() - line1.GetB() * line2.GetA()),
                          (-line1.GetA() * line2.GetC() + line1.GetC() * line2.GetA()) /
                              (line1.GetA() * line2.GetB() - line1.GetB() * line2.GetA()));
  return point;
}

std::istream& operator>>(std::istream& is, Line2D& line) {
  is >> line.a_ >> line.b_ >> line.c_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Line2D& line) {
  os << line.a_ << " " << line.b_ << " " << line.c_ << "\n";
  return os;
}

bool IntersectionLine2DPoint2D(const Line2D& line, const Point2D& point) {
  return line.GetA() * point.GetX() + line.GetB() * point.GetY() + line.GetC() == 0;
}

double DistanceLine2DPoint2D(const Line2D& l, const Point2D& p) {
  return (static_cast<double>(abs(l.GetA() * p.GetX() + l.GetB() * p.GetY() + l.GetC()))) /
         (sqrt(l.GetA() * l.GetA() + l.GetB() * l.GetB()));
}

class Ray2D {
  Point2D p_;
  Vector2D v_;

 public:
  Ray2D();
  Ray2D(const Point2D&, const Vector2D&);
  Ray2D(const Point2D&, const Point2D&);
  Vector2D GetV() const;
  Point2D GetP() const;
  bool IntersectionRay2DPoint2D(const Ray2D&, const Point2D&);
  double DistanceRay2DPoint2D(const Ray2D&, const Point2D&);
};

Ray2D::Ray2D() {
  p_ = Point2D();
  v_ = Vector2D();
}

Ray2D::Ray2D(const Point2D& p, const Vector2D& v) {
  p_ = Point2D(p);
  v_ = Vector2D(v);
}

Ray2D::Ray2D(const Point2D& a, const Point2D& b) {
  Vector2D t = Vector2D(a, b);
  p_ = Point2D(a);
  v_ = Vector2D(t);
}

Vector2D Ray2D::GetV() const {
  return v_;
}

Point2D Ray2D::GetP() const {
  return p_;
}

bool IntersectionRay2DPoint2D(const Ray2D& r, const Point2D& p) {
  Vector2D op = Vector2D(r.GetP(), p);
  return ScalarProduct(r.GetV(), op) >= 0 && VectorProduct(r.GetV(), op) == 0;
}

double DistanceRay2DPoint2D(const Ray2D& r, const Point2D& p) {
  Vector2D op = Vector2D(r.GetP(), p);
  if (ScalarProduct(r.GetV(), op) > 0) {
    return static_cast<double>(abs(VectorProduct(r.GetV(), op))) / Lenght(r.GetV());
  }
  return Lenght(op);
}

class Segment2D {
  Point2D a_;
  Point2D b_;

 public:
  Segment2D();
  Segment2D(const Point2D&, const Point2D&);
  Point2D GetA() const;
  Point2D GetB() const;
  bool IntersectionSegment2DPoint2D(const Segment2D&, const Point2D&);
  double DistanceSegment2DPoint2D(const Segment2D&, const Point2D&);
};

Segment2D::Segment2D() {
  a_ = Point2D();
  b_ = Point2D();
}

Segment2D::Segment2D(const Point2D& a, const Point2D& b) {
  a_ = Point2D(a);
  b_ = Point2D(b);
}

Point2D Segment2D::GetA() const {
  return a_;
}

Point2D Segment2D::GetB() const {
  return b_;
}

bool IntersectionSegment2DPoint2D(const Segment2D& sg, const Point2D& p) {
  Vector2D ap = Vector2D(sg.GetA(), p);
  Vector2D pb = Vector2D(p, sg.GetB());
  return VectorProduct(ap, pb) == 0 && ScalarProduct(ap, pb) >= 0;
}

double DistanceSegment2DPoint2D(const Segment2D& sg, const Point2D& p) {
  Vector2D ap = Vector2D(sg.GetA(), p);
  Vector2D ab = Vector2D(sg.GetA(), sg.GetB());
  Vector2D bp = Vector2D(sg.GetB(), p);
  Vector2D ba = Vector2D(sg.GetB(), sg.GetA());
  if (ScalarProduct(ap, ab) <= 0) {
    return Lenght(ap);
  }
  if (ScalarProduct(bp, ba) <= 0) {
    return Lenght(bp);
  }
  Line2D line = Line2D(sg.GetA(), sg.GetB());
  return DistanceLine2DPoint2D(line, p);
}

int main() {
  Point2D a, b, c;
  std::cin >> c >> a >> b;
  Line2D line = Line2D(a, b);
  Ray2D ray = Ray2D(a, b);
  Segment2D sg = Segment2D(a, b);
  if (IntersectionLine2DPoint2D(line, c)) {
    std::cout << "YES"
              << "\n";
  } else {
    std::cout << "NO"
              << "\n";
  }
  if (IntersectionRay2DPoint2D(ray, c)) {
    std::cout << "YES"
              << "\n";
  } else {
    std::cout << "NO"
              << "\n";
  }
  if (IntersectionSegment2DPoint2D(sg, c)) {
    std::cout << "YES"
              << "\n";
  } else {
    std::cout << "NO"
              << "\n";
  }
  return 0;
}