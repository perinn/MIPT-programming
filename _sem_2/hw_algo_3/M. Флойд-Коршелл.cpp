#include <iostream>
#include <vector>

class Graph {
  std::vector<std::vector<int>> data_;
  int n_;

 public:
  explicit Graph(int);
  friend std::istream& operator>>(std::istream&, Graph&);
  std::vector<std::vector<int>> FloydWarshall() const;
};

Graph::Graph(int n) {
  n_ = n;
  data_.resize(n, std::vector<int>(n));
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  for (int i = 0; i < graph.n_; ++i) {
    for (int j = 0; j < graph.n_; ++j) {
      std::cin >> graph.data_[i][j];
    }
  }
  return is;
}

std::vector<std::vector<int>> Graph::FloydWarshall() const {
  std::vector<std::vector<int>> d = data_;
  for (int k = 0; k < n_; ++k) {
    for (int x = 0; x < n_; ++x) {
      for (int y = 0; y < n_; ++y) {
        d[x][y] = std::min(d[x][y], d[x][k] + d[k][y]);
      }
    }
  }
  return d;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  Graph graph = Graph(n);
  std::cin >> graph;
  std::vector<std::vector<int>> floyd = graph.FloydWarshall();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << floyd[i][j] << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}