#include <iostream>
#include <vector>
#include <cmath>

class SparseTable2D {
  std::vector<std::vector<std::vector<std::vector<int32_t>>>> st_;

 public:
  explicit SparseTable2D(std::vector<std::vector<int32_t>>);
  int32_t Query(int32_t, int32_t, int32_t, int32_t);
};

SparseTable2D::SparseTable2D(std::vector<std::vector<int32_t>> arr) {
  auto m = static_cast<int32_t>(arr.size());
  auto n = static_cast<int32_t>(arr[0].size());
  int32_t k1_max = std::floor(std::log2(m));
  int32_t k2_max = std::floor(std::log2(n));
  st_ = std::vector<std::vector<std::vector<std::vector<int32_t>>>>(
      m, std::vector<std::vector<std::vector<int32_t>>>(
             n, std::vector<std::vector<int32_t>>(k1_max + 1, std::vector<int32_t>(k2_max + 1, INT32_MAX))));
  for (int32_t i = 0; i < m; ++i) {
    for (int32_t j = 0; j < n; ++j) {
      st_[i][j][0][0] = arr[i][j];
    }
  }
  for (int32_t i = 0; i < m; ++i) {
    for (int32_t k2 = 1; k2 < k2_max + 1; ++k2) {
      for (int32_t j = 0; j < n - (1 << k2) + 1; ++j) {
        st_[i][j][0][k2] = std::min(st_[i][j + (1 << (k2 - 1))][0][k2 - 1], st_[i][j][0][k2 - 1]);
      }
    }
  }
  for (int32_t k1 = 1; k1 <= k1_max; ++k1) {
    for (int32_t i = 0; i <= m - (1 << k1); ++i) {
      for (int32_t k2 = 0; k2 <= k2_max; ++k2) {
        for (int32_t j = 0; j <= n - (1 << k2); ++j) {
          st_[i][j][k1][k2] = std::min(st_[i + (1 << (k1 - 1))][j][k1 - 1][k2], st_[i][j][k1 - 1][k2]);
        }
      }
    }
  }
}

int32_t SparseTable2D::Query(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
  int32_t k1 = std::floor(std::log2(x2 - x1 + 1));
  int32_t k2 = std::floor(std::log2(y2 - y1 + 1));
  return std::min(std::min(st_[x2 - (1 << k1) + 1][y2 - (1 << k2) + 1][k1][k2], st_[x1][y2 - (1 << k2) + 1][k1][k2]),
                  std::min(st_[x2 - (1 << k1) + 1][y1][k1][k2], st_[x1][y1][k1][k2]));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t m = 0;
  int32_t n = 0;
  int32_t q = 0;
  int32_t x1 = 0;
  int32_t y1 = 0;
  int32_t x2 = 0;
  int32_t y2 = 0;
  std::cin >> m >> n;
  std::vector<std::vector<int32_t>> input(m, std::vector<int32_t>(n, 0));
  for (int32_t i = 0; i < m; ++i) {
    for (int32_t j = 0; j < n; ++j) {
      std::cin >> input[i][j];
    }
  }
  SparseTable2D st = SparseTable2D(input);
  std::cin >> q;
  for (int32_t i = 0; i < q; ++i) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << st.Query(x1 - 1, y1 - 1, x2 - 1, y2 - 1) << '\n';
  }
  return 0;
}