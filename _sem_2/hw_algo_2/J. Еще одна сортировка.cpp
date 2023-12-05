#include <iostream>
#include <vector>

class Graph {
  std::vector<std::vector<int64_t>> data_;
  int64_t count_vertex_;
  int64_t count_edges_;

 public:
  Graph(int64_t, int64_t);
  void DFS1(int64_t, std::vector<bool>&, std::vector<int64_t>&) const;
  bool DFS(int64_t, std::vector<int64_t>&, std::vector<int64_t>&, int64_t&, int64_t&) const;
  bool HasCycles() const;
  void TopologicalSort() const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int64_t count_vertex, int64_t count_edges) {
  count_vertex_ = count_vertex;
  count_edges_ = count_edges;
  data_.resize(count_vertex_ + 1);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int64_t a, b;
  for (int64_t i = 0; i < graph.count_edges_; ++i) {
    is >> a >> b;
    graph.data_[a].push_back(b);
  }
  return is;
}

void Graph::DFS1(int64_t first, std::vector<bool>& used, std::vector<int64_t>& arr) const {
  used[first] = true;
  for (auto second : data_[first]) {
    if (!used[second]) {
      DFS1(second, used, arr);
    }
  }
  arr.push_back(first);
}

bool Graph::DFS(int64_t first, std::vector<int64_t>& color, std::vector<int64_t>& path, int64_t& start,
                int64_t& end) const {
  color[first] = 1;
  for (auto second : data_[first]) {
    if (color[second] == 0) {
      path[second] = first;
      if (DFS(second, color, path, start, end)) {
        return true;
      }
    } else if (color[second] == 1) {
      end = first;
      start = second;
      return true;
    }
  }
  color[first] = 2;
  return false;
}

bool Graph::HasCycles() const {
  std::vector<int64_t> color(count_vertex_ + 1, 0);
  std::vector<int64_t> path(count_vertex_ + 1, -1);
  int64_t start = -1, end;
  for (int64_t i = 0; i <= count_vertex_; ++i) {
    if (DFS(i, color, path, start, end)) {
      break;
    }
  }
  return start != -1;
}

void Graph::TopologicalSort() const {
  if (HasCycles()) {
    std::cout << -1;
    return;
  }
  std::vector<int64_t> arr;
  std::vector<bool> used(count_vertex_ + 1, false);
  for (int64_t i = 1; i <= count_vertex_; ++i) {
    if (!used[i]) {
      DFS1(i, used, arr);
    }
  }
  for (int64_t i = arr.size() - 1; i >= 0; --i) {
    std::cout << arr[i] << ' ';
  }
}

int main() {
  int64_t n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  graph.TopologicalSort();
  return 0;
}