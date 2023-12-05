#include <iostream>
#include <vector>

class Graph {
  std::vector<std::vector<int64_t>> data_;
  int64_t n_, m_;

 public:
  Graph(int64_t, int64_t);
  void Dfs(int64_t, int64_t, bool&, std::vector<std::vector<bool>>&);
  int64_t CountOfDrains();
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int64_t n, int64_t m) {
  n_ = n;
  m_ = m;
  data_ = std::vector<std::vector<int64_t>>(n_ + 2, std::vector<int64_t>(m_ + 2, INT64_MAX));
}

void Graph::Dfs(int64_t x, int64_t y, bool& flag, std::vector<std::vector<bool>>& used) {
  used[x][y] = true;
  for (int64_t i = -1; i <= 1; ++i) {
    for (int64_t j = -1; j <= 1; ++j) {
      if (abs(i) + abs(j) == 1 && data_[x][y] > data_[x + i][y + j]) {
        flag = true;
      }
    }
  }
  for (int64_t i = -1; i <= 1; ++i) {
    for (int64_t j = -1; j <= 1; ++j) {
      if (abs(i) + abs(j) == 1 && data_[x][y] == data_[x + i][y + j] && !used[x + i][y + j]) {
        Dfs(x + i, y + j, flag, used);
      }
    }
  }
}

int64_t Graph::CountOfDrains() {
  std::vector<std::vector<bool>> used(n_ + 2, std::vector<bool>(m_ + 2, false));
  int64_t ans = 0;
  bool flag;
  for (int64_t i = 0; i <= n_ + 1; ++i) {
    used[i][0] = true;
    used[i][m_ + 1] = true;
  }
  for (int64_t i = 0; i <= m_ + 1; ++i) {
    used[0][i] = true;
    used[n_ + 1][i] = true;
  }
  for (int64_t i = 1; i <= n_; ++i) {
    for (int64_t j = 1; j <= m_; ++j) {
      if (!used[i][j]) {
        flag = false;
        Dfs(i, j, flag, used);
        if (!flag) {
          ++ans;
        }
      }
    }
  }
  return ans;
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  for (int64_t i = 1; i <= graph.n_; ++i) {
    for (int64_t j = 1; j <= graph.m_; ++j) {
      is >> graph.data_[i][j];
    }
  }
  return is;
}

int main() {
  int64_t n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  std::cout << graph.CountOfDrains();
  return 0;
}