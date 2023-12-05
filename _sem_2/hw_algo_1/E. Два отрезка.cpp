#include <iostream>
#include <iomanip>
#include <cmath>

class Point {
  double x_, y_;

 public:
  Point();
  Point(double, double);
  double GetX() const;
  double GetY() const;
  friend std::istream& operator>>(std::istream&, Point&);
  friend std::ostream& operator<<(std::ostream&, const Point&);
};

class Vector {
  double x_, y_;

 public:
  Vector();
  Vector(double, double);
  Vector(double, double, double, double);
  explicit Vector(const Point&);
  Vector(const Point&, const Point&);
  double GetX() const;
  double GetY() const;
  double GetL() const;
  double ScalarProduct(const Vector&, const Vector&);
  double VectorProduct(const Vector&, const Vector&);
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
  double Distance(const Segment&, const Point&);
  bool IntersectionB(const Segment&, const Point&);
  // bool IntersectionB(const Segment&, Line&);
  bool IntersectionB(const Segment&, Segment&);
  bool IntersectionC(const Segment&, Segment&);
  friend std::istream& operator>>(std::istream&, Segment&);
};

class Line {
  double a_, b_, c_;

 public:
  Line();
  Line(double, double, double);
  Line(const Point&, const Vector&);
  Line(const Point&, const Point&);
  explicit Line(const Segment&);
  double GetA() const;
  double GetB() const;
  double GetC() const;
  Vector GuidingVector(const Line&);
  Vector NormalVector(const Line&);
  bool Parallel(const Line&, const Line&);
  bool Equals(const Line&, const Line&);
  bool IntersectionB(const Line&, const Line&);
  bool IntersectionB(const Line&, const Point&);
  Point IntersectionP(const Line&, const Line&);
  double Distance(const Line&, const Line&);
  double Distance(const Line&, const Point&);
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
  double Distance(const Ray&, const Point&);
};

class Polygon {
  Point* points_;
  int n_;

 public:
  explicit Polygon(int);
  int Size() const;
  Point* Points() const;
  friend std::istream& operator>>(std::istream&, Polygon&);
  double Area() const;
  ~Polygon() {
    delete[] points_;
  }
};

Point::Point() {
  x_ = 0;
  y_ = 0;
}

Point::Point(double x, double y) {
  x_ = x;
  y_ = y;
}

double Point::GetX() const {
  return x_;
}

double Point::GetY() const {
  return y_;
}

std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x_ >> p.y_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << p.GetX() << " " << p.GetY();
  return os;
}

Vector::Vector() {
  x_ = 0;
  y_ = 0;
}

Vector::Vector(double x, double y) {
  x_ = x;
  y_ = y;
}

Vector::Vector(double x0, double y0, double x1, double y1) {
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

double Vector::GetX() const {
  return x_;
}

double Vector::GetY() const {
  return y_;
}

double Vector::GetL() const {
  return sqrt(x_ * x_ + y_ * y_);
}

double ScalarProduct(const Vector& a, const Vector& b) {
  return a.GetX() * b.GetX() + a.GetY() * b.GetY();
}

double VectorProduct(const Vector& a, const Vector& b) {
  return a.GetX() * b.GetY() - a.GetY() * b.GetX();
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
  double start_x, start_y, end_x, end_y;
  is >> start_x >> start_y >> end_x >> end_y;
  v.x_ = end_x - start_x;
  v.y_ = end_y - start_y;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
  os << v.GetX() << " " << v.GetY();
  return os;
}

Line::Line() {
  a_ = 0;
  b_ = 0;
  c_ = 0;
}

Line::Line(double a, double b, double c) {
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

double Line::GetA() const {
  return a_;
}

double Line::GetB() const {
  return b_;
}

double Line::GetC() const {
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

Point IntersectionP(const Line& l1, const Line& l2) {
  double delta = l1.GetA() * l2.GetB() - l1.GetB() * l2.GetA();
  double delta_x = -l1.GetC() * l2.GetB() + l1.GetB() * l2.GetC();
  double delta_y = -l1.GetA() * l2.GetC() + l1.GetC() * l2.GetA();
  double x = delta_x / delta;
  double y = delta_y / delta;
  Point p = Point(x, y);
  return p;
}

double Distance(const Line& l1, const Line& l2) {
  double x1, y1, x2, y2;
  if (l1.GetA() == 0) {
    x1 = 0;
    y1 = -l1.GetC() / l1.GetB();
  } else if (l1.GetB() == 0) {
    x1 = -l1.GetC() / l1.GetA();
    y1 = 0;
  } else {
    x1 = -(l1.GetC()) / (2 * l1.GetA());
    y1 = -(l1.GetC()) / (2 * l1.GetB());
  }
  if (l2.GetA() == 0) {
    x2 = 0;
    y2 = -l2.GetC() / l2.GetB();
  } else if (l2.GetB() == 0) {
    x2 = -l2.GetC() / l2.GetA();
    y2 = 0;
  } else {
    x2 = -(l2.GetC()) / (2 * l2.GetA());
    y2 = -(l2.GetC()) / (2 * l2.GetB());
  }
  Vector r1 = Vector(x1, y1);
  Vector r2 = Vector(x2, y2);
  Vector r = r1 - r2;
  Vector n = NormalVector(l2);
  return static_cast<double>(abs(ScalarProduct(r, n))) / n.GetL();
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

double Distance(const Line& l, const Point& p) {
  return (static_cast<double>(abs(l.GetA() * p.GetX() + l.GetB() * p.GetY() + l.GetC()))) /
         (sqrt(l.GetA() * l.GetA() + l.GetB() * l.GetB()));
}

Polygon::Polygon(int n) {
  points_ = new Point[n];
  n_ = n;
}

int Polygon::Size() const {
  return n_;
}

Point* Polygon::Points() const {
  return points_;
}

double Polygon::Area() const {
  double s = 0;
  for (int i = 0; i < n_ - 1; ++i) {
    auto a = Vector(points_[i]);
    auto b = Vector(points_[i + 1]);
    s += VectorProduct(b, a);
  }
  s += VectorProduct(Vector(points_[0]), Vector(points_[n_ - 1]));
  return s / 2;
}

std::istream& operator>>(std::istream& is, Polygon& pol) {
  for (int i = 0; i < pol.Size(); ++i) {
    is >> pol.points_[i];
  }
  return is;
}

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

double Distance(const Ray& r, const Point& p) {
  Vector op = Vector(r.GetP(), p);
  if (ScalarProduct(r.GetV(), op) > 0) {
    return static_cast<double>(abs(VectorProduct(r.GetV(), op))) / r.GetV().GetL();
  }
  return op.GetL();
}

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

double Distance(const Segment& sg, const Point& p) {
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

int main() {
  Segment sg1, sg2;
  std::cin >> sg1 >> sg2;
  if (IntersectionB(sg1, sg2)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}