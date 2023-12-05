#include <iostream>
#include <vector>
#include <queue>
#include <set>

class Graph {
  std::vector<std::vector<int64_t>> data_;
  int64_t count_vertex_;
  int64_t count_edges_;

 public:
  Graph(int64_t, int64_t);
  void DFS(int64_t, int64_t, std::vector<bool>&, std::vector<int64_t>&, std::vector<int64_t>&,
           std::set<int64_t>&) const;
  void PointsOfArticulation() const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int64_t count_vertex, int64_t count_edges) {
  count_vertex_ = count_vertex;
  count_edges_ = count_edges;
  data_.resize(count_vertex_ + 1);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int64_t a, b;
  for (int64_t i = 0; i < graph.count_edges_; ++i) {
    is >> a >> b;
    graph.data_[a].push_back(b);
    graph.data_[b].push_back(a);
  }
  return is;
}

void Graph::DFS(int64_t v, int64_t p, std::vector<bool>& used, std::vector<int64_t>& h, std::vector<int64_t>& d,
                std::set<int64_t>& points) const {
  used[v] = true;
  d[v] = h[v] = (p == -1 ? 0 : h[p] + 1);
  int64_t child = 0;
  for (int64_t u : data_[v]) {
    if (u != p) {
      if (used[u]) {
        d[v] = std::min(d[v], h[u]);
      } else {
        DFS(u, v, used, h, d, points);
        d[v] = std::min(d[v], d[u]);
        if (h[v] <= d[u] && p != -1) {
          points.emplace(v);
        }
        child++;
      }
    }
  }
  if (p == -1 && child > 1) {
    points.emplace(v);
  }
}

void Graph::PointsOfArticulation() const {
  std::vector<bool> used(count_vertex_ + 1, false);
  std::vector<int64_t> h(count_vertex_ + 1);
  std::vector<int64_t> d(count_vertex_ + 1);
  std::set<int64_t> points;
  for (uint64_t i = 1; i < data_.size(); ++i) {
    if (!used[i]) {
      DFS(i, -1, used, h, d, points);
    }
  }
  std::cout << points.size() << '\n';
  for (auto i : points) {
    std::cout << i << '\n';
  }
}

int main() {
  int64_t n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  graph.PointsOfArticulation();
  return 0;
}