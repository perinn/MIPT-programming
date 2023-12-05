#include <iostream>
#include <vector>
#include <algorithm>

enum color_types { white, gray, black };

class Graph {
  std::vector<std::vector<int64_t>> data_;
  int64_t count_vertex_;
  int64_t count_edges_;

 public:
  Graph(int64_t, int64_t);
  bool DFS(int64_t, std::vector<color_types>&, std::vector<int64_t>&, int64_t&, int64_t&) const;
  void FindCicles() const;
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

bool Graph::DFS(int64_t vertex, std::vector<color_types>& color, std::vector<int64_t>& path, int64_t& start,
                int64_t& end) const {
  color[vertex] = gray;
  for (auto u : data_[vertex]) {
    if (color[u] == 0) {
      path[u] = vertex;
      if (DFS(u, color, path, start, end)) {
        return true;
      }
    } else if (color[u] == gray) {
      end = vertex;
      start = u;
      return true;
    }
  }
  color[vertex] = black;
  return false;
}

void Graph::FindCicles() const {
  std::vector<color_types> color(count_vertex_ + 1, white);
  std::vector<int64_t> path(count_vertex_ + 1, -1);
  int64_t start = -1, end;
  for (int64_t i = 0; i <= count_vertex_; ++i) {
    if (DFS(i, color, path, start, end)) {
      break;
    }
  }
  if (start == -1) {
    std::cout << "NO\n";
    return;
  }
  std::cout << "YES\n";
  std::vector<int64_t> cycle;
  while (end != start) {
    cycle.push_back(end);
    end = path[end];
  }
  cycle.push_back(start);
  std::reverse(cycle.begin(), cycle.end());
  for (auto i : cycle) {
    std::cout << i << ' ';
  }
}

int main() {
  int64_t n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  graph.FindCicles();
  return 0;
}