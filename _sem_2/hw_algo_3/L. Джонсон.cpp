#include <iostream>
#include <queue>

class Edge;
class Graph;

class Edge {
  int64_t a_;
  int64_t b_;
  int64_t w_;

 public:
  Edge();
  Edge(int64_t, int64_t, int64_t);
  friend Graph;
};

Edge::Edge() {
  a_ = 0;
  b_ = 0;
  w_ = 0;
}

Edge::Edge(int64_t a, int64_t b, int64_t w) {
  a_ = a;
  b_ = b;
  w_ = w;
}

class Graph {
  int64_t n_;
  int64_t m_;
  std::vector<std::vector<std::pair<int64_t, int64_t>>> data_;
  std::vector<Edge> edge_data_;
  std::vector<int64_t> dist_;
  std::vector<int64_t> dist_ford_;
  std::vector<bool> point_in_;

 public:
  Graph(int64_t, int64_t);
  friend std::istream& operator>>(std::istream&, Graph&);
  void Dijkstra(int64_t);
  bool Relax(const Edge&);
  void BellmanFord();
  void FixWeight();
  int64_t Max();
};

Graph::Graph(int64_t n, int64_t m) {
  n_ = n;
  m_ = m;
  data_.resize(n);
  dist_.resize(n, INT64_MAX);
  dist_ford_.resize(n, 0);
}

bool Graph::Relax(const Edge& m) {
  if (dist_ford_[m.b_] > dist_ford_[m.a_] + m.w_) {
    dist_ford_[m.b_] = (dist_ford_[m.a_] + m.w_);
    return true;
  }
  return false;
}

void Graph::BellmanFord() {
  for (int64_t i = 0; i < n_; ++i) {
    for (auto edge : edge_data_) {
      Relax(edge);
    }
  }
}

void Graph::FixWeight() {
  for (int64_t i = 0; i < n_; ++i) {
    for (auto& v : data_[i]) {
      v.first += (dist_ford_[i] - dist_ford_[v.second]);
    }
  }
}

void Graph::Dijkstra(int64_t vertex_first) {
  dist_[vertex_first] = 0;
  std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>,
                      std::greater<std::pair<int64_t, int64_t>>>
      queue;
  queue.push({0, vertex_first});
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

int64_t Graph::Max() {
  BellmanFord();
  FixWeight();
  int64_t ans = 0;
  for (int64_t i = 0; i < n_; ++i) {
    Dijkstra(i);
    int64_t max = 0;
    for (int64_t j = 0; j < n_; ++j) {
      if (dist_[j] - dist_ford_[i] + dist_ford_[j] > max && dist_[j] != INT64_MAX) {
        max = dist_[j] - (dist_ford_[i] - dist_ford_[j]);
      }
    }
    for (int64_t i = 0; i < n_; ++i) {
      dist_[i] = INT64_MAX;
    }
    if (ans < max) {
      ans = max;
    }
  }
  return ans;
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int64_t a = 0;
  int64_t b = 0;
  int64_t w = 0;
  for (int64_t i = 0; i < graph.m_; ++i) {
    std::cin >> a >> b >> w;
    auto edge = Edge(a, b, w);
    graph.data_[a].emplace_back(w, b);
    graph.edge_data_.emplace_back(edge);
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