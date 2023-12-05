#include <iostream>
#include <vector>
#include <queue>

class Graph {
  std::vector<std::vector<uint64_t>> data_;
  uint64_t count_vertex_;
  uint64_t count_edges_;

 public:
  Graph(uint64_t, uint64_t);
  void DFS(uint64_t, std::vector<bool>&, std::vector<uint64_t>&) const;
  void ConnectivityComponents() const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(uint64_t count_vertex, uint64_t count_edges) {
  count_vertex_ = count_vertex;
  count_edges_ = count_edges;
  data_.resize(count_vertex_ + 1);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  uint64_t a, b;
  for (uint64_t i = 1; i <= graph.count_edges_; ++i) {
    std::cin >> a >> b;
    graph.data_[a].push_back(b);
    graph.data_[b].push_back(a);
  }
  return is;
}

void Graph::DFS(uint64_t v, std::vector<bool>& used, std::vector<uint64_t>& connectivity_component) const {
  used[v] = true;
  connectivity_component.push_back(v);
  for (auto i : data_[v]) {
    if (!used[i]) {
      DFS(i, used, connectivity_component);
    }
  }
}

void Graph::ConnectivityComponents() const {
  std::vector<bool> used(count_vertex_ + 1);
  std::vector<std::vector<uint64_t>> connectivity_components;
  for (uint64_t i = 1; i <= count_vertex_; ++i) {
    if (!used[i]) {
      connectivity_components.emplace_back();
      DFS(i, used, connectivity_components[connectivity_components.size() - 1]);
    }
  }
  std::cout << connectivity_components.size() << '\n';
  for (auto connectivity_component : connectivity_components) {
    std::cout << connectivity_component.size() << '\n';
    for (auto i : connectivity_component) {
      std::cout << i << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  uint64_t n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  graph.ConnectivityComponents();  
  return 0;
}