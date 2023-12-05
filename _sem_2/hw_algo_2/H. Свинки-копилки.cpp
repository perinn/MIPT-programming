#include <iostream>
#include <vector>
#include <queue>

enum used_types { unused, used };

class Graph {
  std::vector<std::vector<uint64_t>> data_;
  uint64_t count_vertex_;
  uint64_t count_edges_;

 public:
  explicit Graph(uint64_t);
  void DFS(uint64_t, std::vector<used_types>&) const;
  uint64_t CountOfConnectivityComponents() const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(uint64_t count_vertex) {
  count_vertex_ = count_vertex;
  count_edges_ = 0;
  data_.resize(count_vertex_ + 1);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  uint64_t a;
  for (uint64_t i = 1; i <= graph.count_vertex_; ++i) {
    std::cin >> a;
    graph.data_[a].push_back(i);
    graph.data_[i].push_back(a);
    ++graph.count_edges_;
  }
  return is;
}

void Graph::DFS(uint64_t v, std::vector<used_types>& used_arr) const {
  used_arr[v] = used;
  for (auto i : data_[v]) {
    if (used_arr[i] == unused) {
      DFS(i, used_arr);
    }
  }
}

uint64_t Graph::CountOfConnectivityComponents() const {
  std::vector<used_types> used_arr(count_vertex_ + 1, unused);
  uint64_t ans = 0;
  for (uint64_t i = 1; i <= count_vertex_; ++i) {
    if (used_arr[i] == unused) {
      DFS(i, used_arr);
      ++ans;
    }
  }
  return ans;
}

int main() {
  uint64_t n;
  std::cin >> n;
  Graph graph = Graph(n);
  std::cin >> graph;
  std::cout << graph.CountOfConnectivityComponents();
  return 0;
}