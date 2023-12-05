#include <iostream>
#include <iomanip>
#include <cmath>

class Vector2D {
  double x_, y_;

 public:
  Vector2D();
  Vector2D(double, double);
  Vector2D(double, double, double, double);
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

int main() {
  Vector2D a = Vector2D();
  Vector2D b = Vector2D();
  std::cin >> a >> b;
  std::cout << std::fixed;
  std::cout << std::setprecision(6);
  std::cout << Lenght(a) << " " << Lenght(b) << "\n";
  Vector2D c = a + b;
  std::cout << c << "\n";
  std::cout << ScalarProduct(a, b) << " " << VectorProduct(a, b) << "\n";
  std::cout << static_cast<double>(abs(VectorProduct(a, b))) / 2 << "\n";
  return 0;
}