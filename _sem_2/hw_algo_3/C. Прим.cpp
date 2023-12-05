#include <iostream>
#include <queue>

class Graph;

class Edge {
  int64_t vert_;
  int64_t weight_;

 public:
  Edge();
  Edge(int64_t, int64_t);
  friend bool operator<(const Edge&, const Edge&);
  friend Graph;
};

Edge::Edge() {
  vert_ = 0;
  weight_ = 0;
}

Edge::Edge(int64_t vert, int64_t weight) {
  vert_ = vert;
  weight_ = weight;
}

bool operator<(const Edge& e1, const Edge& e2) {
  return e1.weight_ > e2.weight_;
}

class Graph {
  int64_t n_;
  int64_t m_;
  std::vector<std::vector<Edge>> data_;
  std::vector<bool> used_;

 public:
  Graph(int64_t, int64_t);
  int64_t Prim();
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int64_t n, int64_t m) {
  n_ = n;
  m_ = m;
  data_.resize(n);
  used_.resize(n, false);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int64_t a = 0;
  int64_t b = 0;
  int64_t w = 0;
  for (int64_t i = 0; i < graph.m_; ++i) {
    std::cin >> a >> b >> w;
    --a;
    --b;
    graph.data_[a].emplace_back(Edge(b, w));
    graph.data_[b].emplace_back(Edge(a, w));
  }
  return is;
}

int64_t Graph::Prim() {
  int64_t ans = 0;
  std::priority_queue<Edge> queue;
  queue.push({0, 0});
  while (!queue.empty()) {
    auto v = queue.top();
    queue.pop();
    if (!used_[v.vert_]) {
      ans += v.weight_;
      used_[v.vert_] = true;
      for (auto u : data_[v.vert_]) {
        if (!used_[u.vert_]) {
          queue.push(u);
        }
      }
    }
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
  std::cout << graph.Prim();
  return 0;
}