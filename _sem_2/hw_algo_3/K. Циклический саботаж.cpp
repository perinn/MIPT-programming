#include <iostream>
#include <vector>

class Graph {
  std::vector<std::pair<int64_t, std::pair<int64_t, int64_t>>> data_;
  std::vector<int64_t> parent_;
  std::vector<int64_t> cycle_data_;
  int64_t n_;
  int64_t cycle_;

 public:
  explicit Graph(int64_t);
  void AddEdge(int64_t, int64_t, int64_t);
  void FindCycles();
  bool HasCycles() const;
  size_t CycleLenght();
  void PrintCycle() const;
};

Graph::Graph(int64_t n) {
  n_ = n;
  parent_.resize(n, -1);
  cycle_ = -1;
}

void Graph::AddEdge(int64_t a, int64_t b, int64_t w) {
  data_.push_back({w, {a, b}});
}

void Graph::FindCycles() {
  std::vector<int64_t> dist(n_, INT64_MAX);
  for (int64_t k = 0; k < n_ && cycle_ == -1; ++k) {
    if (dist[k] == INT64_MAX) {
      dist[k] = 0;
      for (int64_t i = 0; i < n_; ++i) {
        cycle_ = -1;
        for (size_t j = 0; j < data_.size(); ++j) {
          if (dist[data_[j].second.first] < INT64_MAX) {
            if (dist[data_[j].second.second] > dist[data_[j].second.first] + data_[j].first) {
              dist[data_[j].second.second] = dist[data_[j].second.first] + data_[j].first;
              parent_[data_[j].second.second] = data_[j].second.first;
              cycle_ = data_[j].second.first;
            }
          }
        }
      }
    }
  }
}

bool Graph::HasCycles() const {
  return cycle_ != -1;
}

size_t Graph::CycleLenght() {
  for (int64_t i = 0; i < n_; ++i) {
    cycle_ = parent_[cycle_];
  }
  int64_t cycle_start = cycle_;
  cycle_data_.push_back(cycle_);
  cycle_ = parent_[cycle_];
  while (cycle_ != cycle_start) {
    cycle_data_.push_back(cycle_);
    cycle_ = parent_[cycle_];
  }
  cycle_data_.push_back(cycle_start);
  return cycle_data_.size();
}

void Graph::PrintCycle() const {
  for (int64_t i = static_cast<int64_t>(cycle_data_.size()) - 1; i >= 0; --i) {
    std::cout << cycle_data_[i] + 1 << ' ';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t w = 0;
  std::cin >> n;
  Graph graph = Graph(n);
  for (int64_t i = 0; i < n; ++i) {
    for (int64_t j = 0; j < n; ++j) {
      std::cin >> w;
      if (w < 100000) {
        graph.AddEdge(i, j, w);
      }
    }
  }
  graph.FindCycles();
  if (graph.HasCycles()) {
    std::cout << "YES\n";
    std::cout << graph.CycleLenght() << '\n';
    graph.PrintCycle();
  } else {
    std::cout << "NO\n";
  }
  return 0;
}