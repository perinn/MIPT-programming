#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <utility>

class Edge;
class Graph;
class DSU;

class Edge {
  int64_t u_;
  int64_t v_;
  int64_t w_;

 public:
  Edge();
  Edge(int64_t, int64_t, int64_t);
  friend bool operator!=(const Edge&, const Edge&);
  friend bool operator<(const Edge&, const Edge&);
  friend Graph;
};

Edge::Edge() {
  u_ = 0;
  v_ = 0;
  w_ = 1000000001;
}

Edge::Edge(int64_t u, int64_t v, int64_t w) {
  u_ = u;
  v_ = v;
  w_ = w;
}

bool operator!=(const Edge& e1, const Edge& e2) {
  return e1.u_ != e2.u_ || e1.v_ != e2.v_ || e1.w_ != e2.w_;
}

bool operator<(const Edge& e1, const Edge& e2) {
  return (e1.w_ != e2.w_) ? (e1.w_ < e2.w_) : ((e1.u_ != e2.u_) ? (e1.u_ < e2.u_) : ((e1.v_ < e2.v_)));
}

class Graph {
  int64_t n_;
  int64_t m_;
  std::vector<Edge> data_;
  std::set<Edge> mst_;
  std::vector<Edge> min_edge_;

 public:
  Graph(int64_t, int64_t);
  int64_t Boruvka();
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int64_t n, int64_t m) {
  n_ = n;
  m_ = m;
  data_.resize(m + 1);
  min_edge_.resize(n + 1);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int64_t u = 0;
  int64_t v = 0;
  int64_t w = 0;
  for (int64_t i = 0; i < graph.m_; ++i) {
    std::cin >> u >> v >> w;
    graph.data_[i] = Edge(u, v, w);
  }
  return is;
}

class DSU {
  std::vector<int64_t> parent_;
  std::vector<int64_t> rank_;
  int64_t size_;

 public:
  explicit DSU(int64_t);
  void MakeSet(int64_t);
  int64_t FindSet(int64_t);
  void Union(int64_t, int64_t);
  int64_t SetCount();
};

DSU::DSU(int64_t n) {
  size_ = n;
  parent_.resize(n + 1);
  rank_.resize(n + 1);
  for (int i = 0; i <= n; ++i) {
    MakeSet(i);
  }
}

void DSU::MakeSet(int64_t x) {
  parent_[x] = x;
  rank_[x] = 1;
}

int64_t DSU::FindSet(int64_t x) {
  if (x == parent_[x]) {
    return x;
  }
  return parent_[x] = FindSet(parent_[x]);
}

void DSU::Union(int64_t x, int64_t y) {
  x = FindSet(x);
  y = FindSet(y);
  if (x != y) {
    if (rank_[x] < rank_[y]) {
      std::swap(x, y);
    } else if (rank_[x] == rank_[y]) {
      ++rank_[x];
    }
    parent_[y] = x;
    --size_;
  }
}

int64_t DSU::SetCount() {
  return size_;
}

int64_t Graph::Boruvka() {
  DSU dsu = DSU(n_);
  while (dsu.SetCount() > 1) {
    for (int64_t i = 0; i < n_ + 1; ++i) {
      min_edge_[i] = Edge();
    }
    for (auto v : data_) {
      int64_t component_v = dsu.FindSet(v.u_);
      int64_t component_u = dsu.FindSet(v.v_);
      if (component_u != component_v) {
        if (v.w_ < min_edge_[component_v].w_) {
          min_edge_[component_v] = v;
        }
        if (v.w_ < min_edge_[component_u].w_) {
          min_edge_[component_u] = v;
        }
      }
    }
    for (auto v : min_edge_) {
      if (v.u_ == 0) {
        continue;
      }
      mst_.insert(v);
      dsu.Union(v.u_, v.v_);
    }
  }
  int64_t ans = 0;
  for (auto v : mst_) {
    ans += v.w_;
  }
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  std::cout << graph.Boruvka();
  return 0;
}