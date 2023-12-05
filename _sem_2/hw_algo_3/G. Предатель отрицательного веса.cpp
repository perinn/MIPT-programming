#include <iostream>
#include <vector>
#include <algorithm>

bool Comparator(const std::pair<int, std::pair<int, int>>& a, const std::pair<int, std::pair<int, int>>& b) {
  return a.first < b.first;
}

class Graph {
  std::vector<std::pair<int, std::pair<int, int>>> data_;

 public:
  void AddEdge(int, int, int);
  void Sort();
  std::vector<std::pair<int, std::pair<int, int>>>& Data();
};

void Graph::AddEdge(int a, int b, int w) {
  data_.push_back({w, {a, b}});
}

void Graph::Sort() {
  std::sort(data_.begin(), data_.end(), Comparator);
}

std::vector<std::pair<int, std::pair<int, int>>>& Graph::Data() {
  return data_;
}

void Ways(Graph& graph, int n, int m) {
  std::vector<int> dist(n);
  for (int i = 1; i < n; i++) {
    dist[i] = 30000;
  }
  dist[0] = 0;
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (dist[graph.Data()[j].second.first] < 30000) {
        if (dist[graph.Data()[j].second.second] > dist[graph.Data()[j].second.first] + graph.Data()[j].first) {
          dist[graph.Data()[j].second.second] = dist[graph.Data()[j].second.first] + graph.Data()[j].first;
        }
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    std::cout << dist[i] << ' ';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  int a = 0;
  int b = 0;
  int w = 0;
  Graph graph;
  std::cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b >> w;
    graph.AddEdge(--a, --b, w);
  }
  Ways(graph, n, m);
  return 0;
}