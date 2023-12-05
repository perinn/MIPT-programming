#include <iostream>
#include <vector>

class Graph {
  std::vector<std::vector<int>> data_;
  int count_vertex_;

 public:
  explicit Graph(int);
  bool DFS(int, std::vector<int>&, std::vector<int>&, int&, int&) const;
  bool HasCycles() const;
  void AddEdge(int, int);
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int count_vertex) {
  count_vertex_ = count_vertex;
  data_.resize(count_vertex_ + 1);
}

void Graph::AddEdge(int a, int b) {
  data_[a].push_back(b);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  char input;
  for (int i = 1; i < graph.count_vertex_; ++i) {
    for (int j = i + 1; j <= graph.count_vertex_; ++j) {
      std::cin >> input;
      if (input == 'B') {
        graph.AddEdge(i, j);
      } else {
        graph.AddEdge(j, i);
      }
    }
  }
  return is;
}

bool Graph::DFS(int first, std::vector<int>& color, std::vector<int>& path, int& start, int& end) const {
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
  std::vector<int> color(count_vertex_ + 1, 0);
  std::vector<int> path(count_vertex_ + 1, -1);
  int start = -1, end;
  for (int i = 0; i <= count_vertex_; ++i) {
    if (DFS(i, color, path, start, end)) {
      break;
    }
  }
  return start != -1;
}

int main() {
  int n;
  std::cin >> n;
  Graph graph = Graph(n);
  std::cin >> graph;
  if (graph.HasCycles()) {
    std::cout << "NO";
  } else {
    std::cout << "YES";
  }
}