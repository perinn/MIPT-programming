#include <iostream>
#include <vector>

class Edge {
 public:
  int64_t index_;
  int64_t n_;
  int64_t flow_;
  int64_t flow_max_;
  Edge(int64_t, int64_t, int64_t, int64_t);
};

Edge::Edge(int64_t n, int64_t flow, int64_t flow_max, int64_t i) {
  n_ = n;
  flow_ = flow;
  flow_max_ = flow_max;
  index_ = i;
}

class Graph {
  int64_t n_;
  int64_t m_;
  std::vector<bool> used_;
  std::vector<std::vector<Edge>> data_;

 public:
  Graph(int64_t, int64_t);
  int64_t DFS(int64_t, int64_t);
  int64_t Max();
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int64_t n, int64_t m) {
  n_ = n;
  m_ = m;
  data_.resize(n + 1);
  used_.resize(n + 1);
}

int64_t Graph::DFS(int64_t start, int64_t finish) {
  if (start == n_) {
    return finish;
  }
  used_[start] = true;
  for (auto& v : data_[start]) {
    if (v.flow_ < v.flow_max_) {
      if (!used_[v.n_]) {
        int64_t dist = v.flow_max_ - v.flow_;
        finish = std::min(finish, dist);
        int64_t real_result = DFS(v.n_, finish);
        if (real_result != 0) {
          v.flow_ += real_result;
          data_[v.n_][v.index_].flow_ -= real_result;
          return real_result;
        }
      }
    }
  }
  return 0;
}

int64_t Graph::Max() {
  bool flag = true;
  while (flag) {
    flag = DFS(1, INT64_MAX);
    for (int64_t i = 0; i < n_ + 1; ++i) {
      used_[i] = false;
    }
  }
  int64_t finish = 0;
  for (auto v : data_[1]) {
    finish += v.flow_;
  }
  return finish;
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int64_t u = 0;
  int64_t v = 0;
  int64_t w = 0;
  int64_t id = 0;
  for (int64_t i = 0; i < graph.m_; ++i) {
    std::cin >> u >> v >> w;
    id = static_cast<int64_t>(graph.data_[v].size());
    graph.data_[u].emplace_back(Edge(v, 0, w, id));
    id = static_cast<int64_t>(graph.data_[u].size()) - 1;
    graph.data_[v].emplace_back(Edge(u, 0, 0, id));
  }
  return is;
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
  std::cout << graph.Max();
  return 0;
}