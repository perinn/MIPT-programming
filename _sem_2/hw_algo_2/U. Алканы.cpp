#include <iostream>
#include <vector>

class Graph {
  std::vector<std::pair<char, std::vector<std::pair<int, int>>>> data_;
  int count_vertex_;
  int count_edges_;
  bool is_alkan_;

 public:
  Graph(int, int);
  bool DFS(std::pair<int, int>, std::vector<int>&, std::vector<int>&) const;
  bool HasCycles() const;
  void DFS1(int, std::vector<int>&, std::vector<int>&) const;
  int CountOfConnectivityComponents() const;
  bool IsAlkan() const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int count_vertex, int count_edges) {
  count_vertex_ = count_vertex;
  count_edges_ = count_edges;
  is_alkan_ = true;
  data_.resize(count_vertex_ + 1);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  for (int i = 1; i <= graph.count_vertex_; ++i) {
    std::cin >> graph.data_[i].first;
  }
  int a, b;
  for (int i = 1; i <= graph.count_edges_; ++i) {
    is >> a >> b;
    if ((graph.data_[a].first == 'H' && graph.data_[b].first == 'H') || (a == b)) {
      graph.is_alkan_ = false;
    }
    graph.data_[a].second.emplace_back(b, i);
    graph.data_[b].second.emplace_back(a, i);
  }
  return is;
}

bool Graph::DFS(std::pair<int, int> v, std::vector<int>& color, std::vector<int>& parent) const {
  color[v.first] = 1;
  for (auto neighdour : data_[v.first].second) {
    int u = neighdour.first;
    if (color[u] == 1 && parent[v.first] != u) {
      return true;
    }
    if (color[u] == 1 && parent[v.first] == u && neighdour.second != v.second) {
      return true;
    }
    if (color[u] == 0) {
      parent[u] = v.first;
      if (DFS(neighdour, color, parent)) {
        return true;
      }
    }
  }
  color[v.first] = 2;
  return false;
}

bool Graph::HasCycles() const {
  std::vector<int> color(count_vertex_ + 1, 0);
  std::vector<int> parent(count_vertex_ + 1, 0);
  for (int i = 1; i <= count_vertex_; ++i) {
    if (color[i] == 0) {
      if (DFS({i, -1}, color, parent)) {
        return true;
      }
    }
  }
  return false;
}

void Graph::DFS1(int v, std::vector<int>& color, std::vector<int>& parent) const {
  color[v] = 1;
  for (auto u : data_[v].second) {
    parent[u.first] = v;
    if (color[u.first] == 0) {
      DFS1(u.first, color, parent);
    }
  }
  color[v] = 2;
}

int Graph::CountOfConnectivityComponents() const {
  std::vector<int> color(count_vertex_ + 1, 0);
  std::vector<int> parent(count_vertex_ + 1, 0);
  int ans = 0;
  for (int i = 1; i <= count_vertex_; ++i) {
    if (color[i] == 0) {
      DFS1(i, color, parent);
      ++ans;
    }
  }
  return ans;
}

bool Graph::IsAlkan() const {
  if (!is_alkan_) {
    return false;
  }
  for (int i = 1; i <= count_vertex_; ++i) {
    if (data_[i].first == 'H' && data_[i].second.size() != 1) {
      return false;
    }
    if (data_[i].first == 'C' && data_[i].second.size() != 4) {
      return false;
    }
  }
  if (HasCycles()) {
    return false;
  }
  if (CountOfConnectivityComponents() != 1) {
    return false;
  }
  return true;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  if (graph.IsAlkan()) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  return 0;
}