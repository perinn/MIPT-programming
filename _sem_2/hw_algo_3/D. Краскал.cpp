#include <iostream>
#include <vector>
#include <algorithm>

bool Comparator(const std::pair<int, std::pair<int, int>>& a, const std::pair<int, std::pair<int, int>>& b) {
  return a.first < b.first;
}

class Graph {
  std::vector<std::pair<int, std::pair<int, int>>> data_;

 public:
  void AddEdge(int, int, int);
  void Sort();
  std::vector<std::pair<int, std::pair<int, int>>>& Data();
};

void Graph::AddEdge(int a, int b, int w) {
  data_.push_back({w, {a, b}});
}

void Graph::Sort() {
  std::sort(data_.begin(), data_.end(), Comparator);
}

std::vector<std::pair<int, std::pair<int, int>>>& Graph::Data() {
  return data_;
}

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
  if (x != y) {
    if (rank_[x] < rank_[y]) {
      std::swap(x, y);
    } else if (rank_[x] == rank_[y]) {
      ++rank_[x];
    }
    parent_[y] = x;
  }
}

int Kraskal(Graph& graph, int n) {
  int ans = 0;
  graph.Sort();
  DSU dsu = DSU(n);
  for (int i = 0; i < n; ++i) {
    dsu.MakeSet(i);
  }
  for (auto edge : graph.Data()) {
    if (dsu.FindSet(edge.second.first) != dsu.FindSet(edge.second.second)) {
      dsu.Union(edge.second.first, edge.second.second);
      ans += edge.first;
    }
  }
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  int a = 0;
  int b = 0;
  int w = 0;
  Graph graph;
  std::cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b >> w;
    graph.AddEdge(--a, --b, w);
  }
  std::cout << Kraskal(graph, n);
  return 0;
}