#include <iostream>
#include <vector>

class Graph {
  std::vector<std::vector<int>> data_;

 public:
  explicit Graph(int);
  void AddEdge(int, int);
  void Vertex(int);
};

Graph::Graph(int n) {
  data_.resize(n + 1);
}

void Graph::AddEdge(int a, int b) {
  data_[a].push_back(b);
  data_[b].push_back(a);
}

void Graph::Vertex(int v) {
  for (size_t i = 0; i < data_[v].size(); ++i) {
    std::cout << data_[v][i] << ' ';
  }
  std::cout << '\n';
}

int main() {
  int n, k, comand, a, b;
  std::cin >> n >> k;
  Graph graph = Graph(n);
  for (int i = 0; i < k; ++i) {
    std::cin >> comand;
    if (comand == 1) {
      std::cin >> a >> b;
      graph.AddEdge(a, b);
    } else {
      std::cin >> a;
      graph.Vertex(a);
    }
  }
}