#include <iostream>
#include <queue>

class Edge {
  int64_t start_;
  int64_t end_;
  int64_t weight_;

 public:
  Edge();
  Edge(int64_t, int64_t, int64_t);
};

Edge::Edge() {
  start_ = 0;
  end_ = 0;
  weight_ = 0;
}

Edge::Edge(int64_t start, int64_t end, int64_t l) {
  start_ = start;
  end_ = end;
  weight_ = l;
}

class Graph {
  int64_t n_;
  int64_t m_;
  int64_t k_;
  std::vector<std::vector<std::pair<int64_t, int64_t>>> data_;
  std::vector<int64_t> virus_;
  std::vector<int64_t> dist_;

 public:
  Graph(int64_t, int64_t, int64_t);
  void Dijkstra(int64_t);
  int64_t Min(int64_t);
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int64_t n, int64_t m, int64_t k) {
  n_ = n;
  m_ = m;
  k_ = k;
  data_.resize(n + 1);
  dist_.resize(n + 1, INT64_MAX);
}

void Graph::Dijkstra(int64_t start) {
  std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>,
                      std::greater<std::pair<int64_t, int64_t>>>
      queue;
  queue.push({0, start});
  dist_[start] = 0;
  while (!queue.empty()) {
    auto v = queue.top();
    queue.pop();
    if (v.first > dist_[v.second]) {
      continue;
    }
    for (auto u : data_[v.second]) {
      if (dist_[u.second] > u.first + dist_[v.second]) {
        dist_[u.second] = u.first + dist_[v.second];
        queue.push({dist_[u.second], u.second});
      }
    }
  }
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int64_t x = 0;
  int64_t y = 0;
  int64_t l = 0;
  for (int64_t i = 0; i < graph.k_; ++i) {
    std::cin >> x;
    graph.virus_.push_back(x);
  }
  for (int64_t i = 0; i < graph.m_; ++i) {
    std::cin >> x >> y >> l;
    graph.data_[x].emplace_back(l, y);
    graph.data_[y].emplace_back(l, x);
  }
  return is;
}

int64_t Graph::Min(int64_t s) {
  for (auto v : virus_) {
    if (dist_[v] <= dist_[s]) {
      return -1;
    }
  }
  return dist_[s];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t m = 0;
  int64_t k = 0;
  std::cin >> n >> m >> k;
  Graph graph = Graph(n, m, k);
  std::cin >> graph;
  int64_t s = 0;
  int64_t t = 0;
  std::cin >> s >> t;
  graph.Dijkstra(t);
  std::cout << graph.Min(s);
  return 0;
}