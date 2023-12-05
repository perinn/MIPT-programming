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

int Cost(Graph& graph, std::vector<int>& arr, int n) {
  int ans = 0;
  graph.Sort();
  for (auto i : graph.Data()) {
    if (arr[i.second.second] != arr[i.second.first]) {
      ans += i.first;
      int t = arr[i.second.first];
      for (int j = 0; j <= n; ++j) {
        if (arr[j] == t) {
          arr[j] = arr[i.second.second];
        }
      }
    }
  }
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int w = 0;
  Graph graph;
  std::cin >> n;
  std::vector<int> arr(n + 1);
  for (int i = 0; i <= n; ++i) {
    arr[i] = i;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> w;
      if (i > j) {
        graph.AddEdge(i, j, w);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> w;
    graph.AddEdge(i, n, w);
  }
  std::cout << Cost(graph, arr, n);
  return 0;
}