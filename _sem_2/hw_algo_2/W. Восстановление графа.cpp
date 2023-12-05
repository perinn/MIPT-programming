#include <iostream>
#include <vector>
#include <set>

class Graph {
  std::vector<std::vector<std::pair<int64_t, int64_t>>> data_;
  int64_t count_of_vertex_, count_of_edges_;

 public:
  Graph(int64_t, int64_t);
  void Dfs(int64_t, bool, int64_t, std::vector<int64_t>&, std::vector<bool>&, std::vector<bool>&);
  void Recovery();
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int64_t count_of_vertex, int64_t count_of_edges) {
  count_of_vertex_ = count_of_vertex;
  count_of_edges_ = count_of_edges;
  data_.resize(count_of_vertex_ + 1);
}

void Graph::Dfs(int64_t v, bool sign, int64_t summand, std::vector<int64_t>& sum, std::vector<bool>& used,
                std::vector<bool>& signes) {
  sum[v] = summand;
  used[v] = true;
  signes[v] = sign;
  for (auto i : data_[v]) {
    if (!used[i.first]) {
      summand = i.second - sum[v];
      Dfs(i.first, !sign, summand, sum, used, signes);
    }
  }
}

void Graph::Recovery() {
  std::vector<bool> used(count_of_vertex_ + 1, false), signes(count_of_vertex_ + 1);
  std::vector<int64_t> sum(count_of_vertex_ + 1), p(count_of_vertex_ + 1);
  int64_t min_positive = INT64_MAX, min_negative = INT64_MAX, a = 0, b = 0;
  bool flag = true;
  bool check = false;
  Dfs(1, true, 0, sum, used, signes);
  for (int64_t i = 1; i <= count_of_vertex_; ++i) {
    if (signes[i] && sum[i] < min_positive) {
      min_positive = sum[i];
      a = 1 - sum[i];
    }
    if (!signes[i] && sum[i] < min_negative) {
      min_negative = sum[i];
      b = sum[i] - 1;
    }
  }
  for (int64_t i = 1; i <= count_of_vertex_; ++i) {
    if (signes[i]) {
      p[i] = sum[i] + a;
    } else {
      p[i] = sum[i] - a;
    }
    if (p[i] > count_of_vertex_ || p[i] < 1) {
      flag = false;
    }
  }
  for (int64_t v = 1; v <= count_of_vertex_; ++v) {
    for (auto u : data_[v]) {
      if (p[v] + p[u.first] != u.second) {
        flag = false;
        break;
      }
    }
  }
  if (static_cast<int64_t>(std::set<int64_t>(p.begin() + 1, p.end()).size()) != count_of_vertex_) {
    flag = false;
  }
  if (flag) {
    check = true;
  }
  if (!check) {
    for (int64_t i = 1; i <= count_of_vertex_; ++i) {
      if (signes[i]) {
        p[i] = sum[i] + b;
      } else {
        p[i] = sum[i] - b;
      }
    }
  }
  for (int64_t i = 1; i <= count_of_vertex_; ++i) {
    std::cout << p[i] << ' ';
  }
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int64_t u, v, c;
  for (int64_t i = 0; i < graph.count_of_edges_; ++i) {
    is >> u >> v >> c;
    graph.data_[u].emplace_back(v, c);
    graph.data_[v].emplace_back(u, c);
  }
  return is;
}

int main() {
  int64_t n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  graph.Recovery();
  return 0;
}