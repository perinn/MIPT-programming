#include <iostream>
#include <vector>
#include <queue>

class Graph {
  std::vector<std::vector<std::pair<uint64_t, bool>>> oriented_data_;
  std::vector<std::vector<uint64_t>> not_oriented_data_;
  std::vector<std::vector<uint64_t>> sub_data_;
  uint64_t min_vertex_;
  uint64_t count_of_vertex_;
  uint64_t count_of_routes_;

 public:
  Graph(uint64_t, uint64_t);
  void Dfs(uint64_t, std::vector<bool>&) const;
  void DfsEuler(uint64_t, std::vector<uint64_t>&, std::vector<uint64_t>&);
  void BusRoutes();
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(uint64_t count_of_vertex, uint64_t count_of_routes) {
  min_vertex_ = UINT64_MAX;
  count_of_vertex_ = count_of_vertex;
  oriented_data_.resize(count_of_vertex_ + 1);
  not_oriented_data_.resize(count_of_vertex_ + 1);
  sub_data_.resize(count_of_vertex_ + 1);
  count_of_routes_ = count_of_routes;
}

void Graph::Dfs(uint64_t v, std::vector<bool>& used) const {
  used[v] = true;
  for (auto u : not_oriented_data_[v]) {
    if (!used[u]) {
      Dfs(u, used);
    }
  }
}

void Graph::DfsEuler(uint64_t v, std::vector<uint64_t>& euler, std::vector<uint64_t>& cnt) {
  for (auto i = cnt[v]; i < oriented_data_[v].size(); ++i) {
    if (cnt[v] >= oriented_data_[v].size()) {
      break;
    }
    if (!oriented_data_[v][i].second) {
      oriented_data_[v][i].second = true;
      ++cnt[v];
      DfsEuler(oriented_data_[v][i].first, euler, cnt);
    }
  }
  euler.push_back(v);
}

void Graph::BusRoutes() {
  bool flag = true;
  std::vector<bool> used(count_of_vertex_ + 1, false);
  std::vector<uint64_t> cnt(count_of_vertex_ + 1, 0);
  std::vector<uint64_t> euler;
  if (min_vertex_ == UINT64_MAX || oriented_data_[min_vertex_].empty()) {
    flag = false;
  }
  if (flag) {
    Dfs(min_vertex_, used);
    for (uint64_t i = 1; i <= count_of_vertex_; ++i) {
      if (!used[i] && !oriented_data_[i].empty()) {
        flag = false;
        break;
      }
    }
    if (flag) {
      for (uint64_t i = 1; i <= count_of_vertex_; ++i) {
        if (oriented_data_[i].size() != sub_data_[i].size()) {
          std::cout << i << '\n';
          flag = false;
          break;
        }
      }
    }
  }
  if (!flag) {
    std::cout << 0;
    return;
  }
  DfsEuler(min_vertex_, euler, cnt);
  uint64_t s = euler.size();
  std::cout << s << ' ';
  for (size_t i = 0; i < euler.size(); ++i) {
    std::cout << euler[euler.size() - i - 1] << ' ';
  }
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  uint64_t way, a, b;
  for (uint64_t i = 0; i < graph.count_of_routes_; ++i) {
    is >> way >> a;
    if (a < graph.min_vertex_) {
      graph.min_vertex_ = a;
    }
    for (uint64_t i = 0; i < way; ++i) {
      is >> b;
      if (b < graph.min_vertex_) {
        graph.min_vertex_ = b;
      }
      graph.oriented_data_[a].emplace_back(b, false);
      graph.sub_data_[b].push_back(a);
      graph.not_oriented_data_[a].push_back(b);
      graph.not_oriented_data_[b].push_back(a);
      a = b;
    }
  }
  return is;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  uint64_t n, m;
  std::cin >> n >> m;
  Graph graph = Graph(m, n);
  std::cin >> graph;
  graph.BusRoutes();
  return 0;
}