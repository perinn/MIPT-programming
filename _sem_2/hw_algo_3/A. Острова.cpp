#include <iostream>
#include <vector>

class DSU {
  std::vector<int> parent_;
  std::vector<int> rank_;

 public:
  explicit DSU(int);
  void MakeSet(int);
  int FindSet(int);
  void Union(int, int);
};

DSU::DSU(int n) {
  parent_.resize(n);
  rank_.resize(n);
}

void DSU::MakeSet(int x) {
  parent_[x] = x;
  rank_[x] = 1;
}

int DSU::FindSet(int x) {
  if (x == parent_[x]) {
    return x;
  }
  return parent_[x] = FindSet(parent_[x]);
}

void DSU::Union(int x, int y) {
  x = FindSet(x);
  y = FindSet(y);
  if (rank_[x] < rank_[y]) {
    parent_[x] = y;
  } else if (rank_[y] < rank_[x]) {
    parent_[y] = x;
  } else {
    parent_[x] = y;
    ++rank_[y];
  }
}

int main() {
  int n = 0;
  int m = 0;
  int x = 0;
  int y = 0;
  std::cin >> n >> m;
  DSU dsu = DSU(n);
  for (int i = 0; i < n; ++i) {
    dsu.MakeSet(i);
  }
  int cnt = n - 1;
  for (int i = 0; i < m; i++) {
    std::cin >> x >> y;
    if (dsu.FindSet(x) != dsu.FindSet(y)) {
      dsu.Union(x, y);
      --cnt;
      if (cnt == 0) {
        std::cout << i + 1 << '\n';
        break;
      }
    }
  }
  return 0;
}