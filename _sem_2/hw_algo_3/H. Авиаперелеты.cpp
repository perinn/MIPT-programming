#include <iostream>
#include <vector>

class Graph {
  std::vector<std::pair<int64_t, std::pair<int64_t, int64_t>>> data_;
  std::vector<std::vector<int64_t>> mat_;
  int64_t n_;
  int64_t m_;

 public:
  Graph(int64_t, int64_t);
  void AddEdge(int64_t, int64_t, int64_t);
  friend std::istream& operator>>(std::istream&, Graph&);
  int64_t MinCost(int64_t, int64_t, int64_t);
};

Graph::Graph(int64_t n, int64_t m) {
  mat_.resize(n, std::vector<int64_t>(n, INT64_MAX));
  n_ = n;
  m_ = m;
}

void Graph::AddEdge(int64_t a, int64_t b, int64_t w) {
  data_.push_back({w, {a, b}});
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int64_t a = 0;
  int64_t b = 0;
  int64_t w = 0;
  for (int64_t i = 0; i < graph.m_; ++i) {
    std::cin >> a >> b >> w;
    --a;
    --b;
    if (w < graph.mat_[a][b]) {
      graph.mat_[a][b] = w;
    }
  }
  for (int64_t i = 0; i < graph.n_; ++i) {
    for (int64_t j = 0; j < graph.n_; ++j) {
      if (graph.mat_[i][j] < INT64_MAX) {
        graph.AddEdge(i, j, graph.mat_[i][j]);
      }
    }
  }
  return is;
}

int64_t Graph::MinCost(int64_t k, int64_t s, int64_t f) {
  std::vector<std::vector<int64_t>> dist(n_, std::vector<int64_t>(k + 1, INT64_MAX));
  --s;
  --f;
  dist[s][0] = 0;
  for (int a = 0; a < n_; ++a) {
    for (int i = 0; i < k; ++i) {
      for (size_t j = 0; j < data_.size(); ++j) {
        if (dist[data_[j].second.first][i] < INT64_MAX &&
            dist[data_[j].second.second][i + 1] > dist[data_[j].second.first][i] + data_[j].first) {
          dist[data_[j].second.second][i + 1] = dist[data_[j].second.first][i] + data_[j].first;
        }
      }
    }
  }
  int64_t min = INT64_MAX;
  for (int64_t i = 0; i <= k; ++i) {
    if (dist[f][i] < min) {
      min = dist[f][i];
    }
  }
  return min == INT64_MAX ? -1 : min;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t m = 0;
  int64_t k = 0;
  int64_t s = 0;
  int64_t f = 0;
  std::cin >> n >> m >> k >> s >> f;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  std::cout << graph.MinCost(k, s, f);
  return 0;
}