#include <iostream>
#include <iomanip>
#include <cmath>

class Point {
  int64_t x_, y_;

 public:
  Point();
  Point(int64_t, int64_t);
  int64_t GetX() const;
  int64_t GetY() const;
  friend std::istream& operator>>(std::istream&, Point&);
  friend std::ostream& operator<<(std::ostream&, const Point&);
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
  double GetL() const;
  int64_t ScalarProduct(const Vector&, const Vector&);
  int64_t VectorProduct(const Vector&, const Vector&);
  friend Vector operator+(const Vector&, const Vector&);
  friend Vector operator-(const Vector&, const Vector&);
  friend std::istream& operator>>(std::istream&, Vector&);
  friend std::ostream& operator<<(std::ostream&, const Vector&);
};

class Polygon {
  Point* points_;
  uint64_t n_;

 public:
  explicit Polygon(uint64_t);
  uint64_t Size() const;
  Point* Points() const;
  friend std::istream& operator>>(std::istream&, Polygon&);
  uint64_t TwiceArea() const;
  ~Polygon() {
    delete[] points_;
  }
};

Point::Point() {
  x_ = 0;
  y_ = 0;
}

Point::Point(int64_t x, int64_t y) {
  x_ = x;
  y_ = y;
}

int64_t Point::GetX() const {
  return x_;
}

int64_t Point::GetY() const {
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

Vector::Vector(int64_t x, int64_t y) {
  x_ = x;
  y_ = y;
}

Vector::Vector(int64_t x0, int64_t y0, int64_t x1, int64_t y1) {
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

int64_t Vector::GetX() const {
  return x_;
}

int64_t Vector::GetY() const {
  return y_;
}

double Vector::GetL() const {
  return sqrt(x_ * x_ + y_ * y_);
}

int64_t ScalarProduct(const Vector& a, const Vector& b) {
  return a.GetX() * b.GetX() + a.GetY() * b.GetY();
}

int64_t VectorProduct(const Vector& a, const Vector& b) {
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
  int64_t start_x, start_y, end_x, end_y;
  is >> start_x >> start_y >> end_x >> end_y;
  v.x_ = end_x - start_x;
  v.y_ = end_y - start_y;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
  os << v.GetX() << " " << v.GetY();
  return os;
}

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

uint64_t Polygon::TwiceArea() const {
  uint64_t s_plus = 0;
  uint64_t s_minus = 0;
  int64_t s = 0;
  for (uint64_t i = 0; i < n_ - 1; ++i) {
    auto a = Vector(points_[i]);
    auto b = Vector(points_[i + 1]);
    s = VectorProduct(b, a);
    if (s > 0) {
      s_plus += s;
    } else {
      s_minus += -s;
    }
  }
  s = VectorProduct(Vector(points_[0]), Vector(points_[n_ - 1]));
  if (s > 0) {
    s_plus += s;
  } else {
    s_minus += -s;
  }
  return std::max(s_plus, s_minus) - std::min(s_plus, s_minus);
}

std::istream& operator>>(std::istream& is, Polygon& pol) {
  for (uint64_t i = 0; i < pol.Size(); ++i) {
    is >> pol.points_[i];
  }
  return is;
}

int main() {
  uint64_t n;
  std::cin >> n;
  auto pol = Polygon(n);
  std::cin >> pol;
  std::cout << std::fixed;
  std::cout << std::setprecision(1);
  std::cout << static_cast<long double>(pol.TwiceArea()) / 2;
  return 0;
}