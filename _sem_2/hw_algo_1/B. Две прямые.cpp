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

class Line {
  double a_, b_, c_;

 public:
  Line();
  Line(double, double, double);
  Line(const Point&, const Vector&);
  Line(const Point&, const Point&);
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

std::istream& operator>>(std::istream& is, Point& point) {
  is >> point.x_ >> point.y_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
  os << point.GetX() << " " << point.GetY();
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

Vector::Vector(const Point& point) {
  x_ = point.GetX();
  y_ = point.GetY();
}

Vector::Vector(const Point& point1, const Point& point2) {
  x_ = point2.GetX() - point1.GetX();
  y_ = point2.GetY() - point1.GetY();
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

double ScalarProduct(const Vector& vector1, const Vector& vector2) {
  return vector1.GetX() * vector2.GetX() + vector1.GetY() * vector2.GetY();
}

double VectorProduct(const Vector& vector1, const Vector& vector2) {
  return vector1.GetX() * vector2.GetY() - vector1.GetY() * vector2.GetX();
}

Vector operator+(const Vector& vector1, const Vector& vector2) {
  return Vector(vector1.GetX() + vector2.GetX(), vector1.GetY() + vector2.GetY());
}

Vector operator-(const Vector& vector1, const Vector& vector2) {
  return Vector(vector1.GetX() - vector2.GetX(), vector1.GetY() - vector2.GetY());
}

std::istream& operator>>(std::istream& is, Vector& vector) {
  double start_x, start_y, end_x, end_y;
  is >> start_x >> start_y >> end_x >> end_y;
  vector.x_ = end_x - start_x;
  vector.y_ = end_y - start_y;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {
  os << vector.GetX() << " " << vector.GetY();
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

Line::Line(const Point& point, const Vector& vector) {
  a_ = vector.GetY();
  b_ = -vector.GetX();
  c_ = vector.GetX() * point.GetY() - vector.GetY() * point.GetX();
}

Line::Line(const Point& point1, const Point& point2) {
  Vector vector = Vector(point1, point2);
  a_ = vector.GetY();
  b_ = -vector.GetX();
  c_ = vector.GetX() * point1.GetY() - vector.GetY() * point1.GetX();
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

Vector GuidingVector(const Line& line) {
  Vector vector = Vector(-line.GetB(), line.GetA());
  return vector;
}

Vector NormalVector(const Line& line) {
  Vector vector = Vector(line.GetA(), line.GetB());
  return vector;
}

bool Parallel(const Line& line1, const Line& line2) {
  Vector v1 = GuidingVector(line1);
  Vector v2 = GuidingVector(line2);
  return VectorProduct(v1, v2) == 0;
}

bool Equals(const Line& line1, const Line& line2) {
  return (line1.GetA() * line2.GetB() == line1.GetB() * line2.GetA()) &&
         (line1.GetB() * line2.GetC() == line1.GetC() * line2.GetB());
}

bool IntersectionB(const Line& line1, const Line& line2) {
  if (Equals(line1, line2)) {
    return true;
  }
  return line1.GetA() * line2.GetB() != line1.GetB() * line2.GetA();
}

Point IntersectionP(const Line& line1, const Line& line2) {
  double delta = line1.GetA() * line2.GetB() - line1.GetB() * line2.GetA();
  double delta_x = -line1.GetC() * line2.GetB() + line1.GetB() * line2.GetC();
  double delta_y = -line1.GetA() * line2.GetC() + line1.GetC() * line2.GetA();
  double x = delta_x / delta;
  double y = delta_y / delta;
  Point point = Point(x, y);
  return point;
}

double Distance(const Line& line1, const Line& line2) {
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
  Vector r1 = Vector(x1, y1);
  Vector r2 = Vector(x2, y2);
  Vector r = r1 - r2;
  Vector n = NormalVector(line2);
  return static_cast<double>(abs(ScalarProduct(r, n))) / n.GetL();
}

std::istream& operator>>(std::istream& is, Line& line) {
  is >> line.a_ >> line.b_ >> line.c_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Line& line) {
  os << line.GetA() << " " << line.GetB() << " " << line.GetC() << "\n";
  return os;
}

bool IntersectionB(const Line& line, const Point& point) {
  return line.GetA() * point.GetX() + line.GetB() * point.GetY() + line.GetC() == 0;
}

double Distance(const Line& line, const Point& point) {
  return (static_cast<double>(abs(line.GetA() * point.GetX() + line.GetB() * point.GetY() + line.GetC()))) /
         (sqrt(line.GetA() * line.GetA() + line.GetB() * line.GetB()));
}

int main() {
  Line line1 = Line();
  Line line2 = Line();
  std::cin >> line1 >> line2;
  std::cout << std::fixed;
  std::cout << std::setprecision(6);
  std::cout << GuidingVector(line1) << "\n";
  std::cout << GuidingVector(line2) << "\n";
  if (Parallel(line1, line2)) {
    std::cout << Distance(line1, line2);
  } else {
    std::cout << IntersectionP(line1, line2);
  }
  return 0;
}