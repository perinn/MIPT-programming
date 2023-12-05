#include <iostream>
#include <vector>
#include <queue>

struct Dot {
  uint64_t start = 0;
  uint64_t end = 0;
};

class Graph {
  std::vector<std::vector<Dot>> data_;
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
    graph.data_[a].push_back(Dot{b, t});
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
    uint64_t first = priority_queue.top().second;
    priority_queue.pop();
    if (visited[first]) {
      continue;
    }
    visited[first] = true;
    for (auto second : data_[first]) {
      uint64_t next = second.start;
      uint64_t weight = second.end;
      if (dist[first] + weight < dist[next]) {
        dist[next] = dist[first] + weight;
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
  uint64_t n, m, a, b;
  std::cin >> n >> m >> a >> b;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  std::cout << graph.TheShortestWay(a, b);
  return 0;
}