#include <iostream>
#include <queue>

class Graph {
  int64_t n_;
  int64_t u_;
  int64_t d_;
  int64_t i_;
  int64_t j_;
  int64_t l_;
  std::vector<std::vector<std::pair<int64_t, int64_t>>> data_;
  std::vector<int64_t> dist_;

 public:
  Graph(int64_t, int64_t, int64_t, int64_t, int64_t, int64_t);
  int64_t Dijkstra(int64_t, int64_t);
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int64_t n, int64_t u, int64_t d, int64_t i, int64_t j, int64_t l) {
  n_ = n;
  u_ = u;
  d_ = d;
  i_ = i;
  j_ = j;
  l_ = l;
  data_.resize(1000501);
  dist_.resize(1000501, INT64_MAX);
}

int64_t Graph::Dijkstra(int64_t start, int64_t end) {
  std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>,
                      std::greater<std::pair<int64_t, int64_t>>>
      queue;
  queue.push({0, start});
  dist_[start] = 0;
  while (!queue.empty()) {
    auto v = queue.top();
    queue.pop();
    if (v.second == end) {
      break;
    }
    for (auto u : data_[v.second]) {
      if (dist_[u.second] > u.first + dist_[v.second]) {
        dist_[u.second] = u.first + dist_[v.second];
        queue.push({dist_[u.second], u.second});
      }
    }
  }
  return dist_[end];
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int64_t max = 0;
  int64_t cnt = 0;
  int64_t vert = 0;
  for (int64_t i = 1; i < graph.l_ + 1; ++i) {
    std::cin >> cnt;
    for (int64_t j = 0; j < cnt; ++j) {
      std::cin >> vert;
      graph.data_[vert].emplace_back(graph.i_, 1000000 + i);
      graph.data_[1000000 + i].emplace_back(graph.j_, vert);
      max = std::max(max, vert);
    }
  }
  graph.data_[1].emplace_back(graph.u_, 2);
  max = std::max(max, graph.n_);
  graph.data_[max].emplace_back(graph.d_, max - 1);
  for (int64_t i = 2; i < max; ++i) {
    graph.data_[i].emplace_back(graph.d_, i - 1);
    graph.data_[i].emplace_back(graph.u_, i + 1);
  }
  return is;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t u = 0;
  int64_t d = 0;
  int64_t i = 0;
  int64_t j = 0;
  int64_t l = 0;
  std::cin >> n >> u >> d >> i >> j >> l;
  Graph graph = Graph(n, u, d, i, j, l);
  std::cin >> graph;
  std::cout << graph.Dijkstra(1, n);
  return 0;
}