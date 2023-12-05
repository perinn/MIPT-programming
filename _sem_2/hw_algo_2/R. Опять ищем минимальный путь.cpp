#include <iostream>
#include <vector>
#include <queue>

class Graph {
  std::vector<std::vector<std::pair<uint64_t, uint64_t>>> data_;
  uint64_t count_vertex_;
  uint64_t count_edges_;

 public:
  Graph(uint64_t, uint64_t);
  int64_t TheShortestWay(uint64_t, uint64_t) const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(uint64_t count_vertex, uint64_t count_edges) {
  count_vertex_ = count_vertex;
  count_edges_ = count_edges;
  data_.resize(count_vertex_ + 1);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  uint64_t a, b, t;
  for (uint64_t i = 0; i < graph.count_edges_; ++i) {
    is >> a >> b >> t;
    graph.data_[a].emplace_back(b, t);
  }
  return is;
}

int64_t Graph::TheShortestWay(uint64_t a, uint64_t b) const {
  std::vector<uint64_t> dist(count_vertex_ + 1, UINT64_MAX);
  std::vector<bool> visited(count_vertex_ + 1, false);
  std::priority_queue<std::pair<uint64_t, uint64_t>> priority_queue;
  dist[a] = 0;
  priority_queue.push({0, a});
  while (!priority_queue.empty()) {
    uint64_t v = priority_queue.top().second;
    priority_queue.pop();
    if (visited[v]) {
      continue;
    }
    visited[v] = true;
    for (auto u : data_[v]) {
      uint64_t next = u.first;
      uint64_t weight = u.second;
      if (dist[v] + weight < dist[next]) {
        dist[next] = dist[v] + weight;
        priority_queue.push({-dist[next], next});
      }
    }
  }
  if (dist[b] != UINT64_MAX) {
    return dist[b];
  }
  return -1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  uint64_t n, m, a, b;
  std::cin >> n >> m >> a >> b;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  std::cout << graph.TheShortestWay(a, b);
  return 0;
}