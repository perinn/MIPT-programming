#include <iostream>
#include <vector>

class FenwicTree3D {
  std::vector<std::vector<std::vector<int>>> f_;
  int n_;

 public:
  void Update(int, int, int, int);
  int Query(int, int, int);
  int Query(int, int, int, int, int, int);
  explicit FenwicTree3D(int n);
};

void FenwicTree3D::Update(int x, int y, int z, int d) {
  for (int i = x; i < n_; i = i | (i + 1)) {
    for (int j = y; j < n_; j = j | (j + 1)) {
      for (int k = z; k < n_; k = k | (k + 1)) {
        f_[i][j][k] += d;
      }
    }
  }
}

int FenwicTree3D::Query(int x, int y, int z) {
  int sum = 0;
  for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
    for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
      for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
        sum += f_[i][j][k];
      }
    }
  }
  return sum;
}

int FenwicTree3D::Query(int x, int y, int z, int xx, int yy, int zz) {
  return Query(xx, yy, zz) - Query(x - 1, yy, zz) - Query(xx, y - 1, zz) - Query(xx, yy, z - 1) +
         Query(xx, y - 1, z - 1) + Query(x - 1, yy, z - 1) + Query(x - 1, y - 1, zz) - Query(x - 1, y - 1, z - 1);
}

FenwicTree3D::FenwicTree3D(int n) {
  n_ = n;
  f_ = std::vector<std::vector<std::vector<int>>>(n_, std::vector<std::vector<int>>(n_, std::vector<int>(n_, 0)));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  int x = 0;
  int y = 0;
  int z = 0;
  int k = 0;
  int xx = 0;
  int yy = 0;
  int zz = 0;
  std::cin >> n;
  FenwicTree3D ft = FenwicTree3D(n);
  while (true) {
    std::cin >> m;
    if (m == 1) {
      std::cin >> x >> y >> z >> k;
      ft.Update(x, y, z, k);
    } else if (m == 2) {
      std::cin >> x >> y >> z >> xx >> yy >> zz;
      std::cout << ft.Query(x, y, z, xx, yy, zz) << '\n';
    } else if (m == 3) {
      break;
    }
  }
  return 0;
}