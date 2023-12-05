#include <iostream>
#include <vector>

class DSU {
  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> weight_;

 public:
  explicit DSU(int);
  void MakeSet(int);
  int FindSet(int);
  void Union(int, int);
  int Weight(int) const;
  void AddWeight(int, int);
};

DSU::DSU(int n) {
  parent_.resize(n);
  rank_.resize(n);
  weight_.resize(n);
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
  if (x != y) {
    if (rank_[x] < rank_[y]) {
      std::swap(x, y);
    } else if (rank_[x] == rank_[y]) {
      ++rank_[x];
    }
    parent_[y] = x;
    weight_[x] += weight_[y];
  }
}

int DSU::Weight(int x) const {
  return weight_[x];
}

void DSU::AddWeight(int x, int w) {
  weight_[x] += w;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  int com = 0;
  int x = 0;
  int y = 0;
  int w = 0;
  std::cin >> n >> m;
  DSU dsu = DSU(1000000);
  for (int i = 0; i < n; ++i) {
    dsu.MakeSet(i);
  }
  for (int i = 0; i < m; ++i) {
    std::cin >> com;
    switch (com) {
      case 1:
        std::cin >> x >> y >> w;
        dsu.Union(--x, --y);
        x = dsu.FindSet(x);
        dsu.AddWeight(x, w);
        break;
      case 2:
        std::cin >> x;
        std::cout << dsu.Weight(dsu.FindSet(--x)) << '\n';
        break;
    }
  }
  return 0;
}