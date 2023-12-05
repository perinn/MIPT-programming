#include <iostream>
#include <vector>
#include <set>

class Graph {
  std::vector<std::vector<std::pair<int, int>>> data_;
  std::vector<std::vector<int>> tree_data_;
  std::vector<std::pair<int, int>> edges_;
  std::vector<int> colors_;
  std::vector<int> time_in_;
  std::vector<int> time_up_;
  std::vector<int> component_;
  std::set<int> bridges_;
  int count_of_vertex_;
  int count_of_edges_;
  int time_;
  int tree_cnt_;

 public:
  Graph(int, int);
  void Dfs(int, int);
  void ConnectivityComponents();
  void DfsVisit(int, int);
  void Bridges();
  int ATwoWayAttack();
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int count_of_vertex, int count_of_edges) {
  count_of_vertex_ = count_of_vertex;
  count_of_edges_ = count_of_edges;
  data_.resize(count_of_vertex_ + 1);
  edges_.resize(count_of_edges_);
  component_.resize(count_of_vertex + 1, -1);
  time_ = 0;
  tree_cnt_ = 0;
}

void Graph::Dfs(int v, int cnt) {
  colors_[v] = 1;
  component_[v] = cnt;
  for (size_t i = 0; i < data_[v].size(); ++i) {
    if (colors_[data_[v][i].first] == 0 && bridges_.find(data_[v][i].second) == bridges_.end()) {
      Dfs(data_[v][i].first, cnt);
    }
  }
}

void Graph::ConnectivityComponents() {
  colors_.assign(count_of_vertex_ + 1, 0);
  int cnt = 1;
  for (int i = 1; i < count_of_vertex_ + 1; ++i) {
    if (colors_[i] == 0) {
      Dfs(i, cnt);
      ++cnt;
    }
  }
  tree_cnt_ = cnt - 1;
}

void Graph::DfsVisit(int v, int p) {
  ++time_;
  time_up_[v] = time_;
  time_in_[v] = time_;
  colors_[v] = 1;
  for (std::pair<int, int> neighbour : data_[v]) {
    int u = neighbour.first;
    if (u == p) {
      continue;
    }
    int cnt = 0;
    if (colors_[u] == 1) {
      time_up_[v] = std::min(time_up_[v], time_in_[u]);
    }
    if (colors_[u] == 0) {
      DfsVisit(u, v);
      time_up_[v] = std::min(time_up_[v], time_up_[u]);
      if (time_up_[u] > time_in_[v]) {
        for (int i = 0; i < static_cast<int>(data_[v].size()); ++i) {
          if (data_[v][i].first == u) {
            ++cnt;
          }
        }
        if (cnt == 1) {
          bridges_.emplace(neighbour.second);
        }
      }
    }
  }
  colors_[v] = 2;
}

void Graph::Bridges() {
  time_ = 0;
  colors_.assign(count_of_vertex_ + 1, 0);
  time_in_.assign(count_of_vertex_ + 1, 0);
  time_up_.assign(count_of_vertex_ + 1, 0);
  for (int i = 1; i < count_of_vertex_; ++i) {
    if (colors_[i] == 0) {
      DfsVisit(i, -1);
    }
  }
}

int Graph::ATwoWayAttack() {
  Bridges();
  ConnectivityComponents();
  int ans = 0;
  tree_data_.resize(tree_cnt_ + 1);
  for (int i : bridges_) {
    tree_data_[component_[edges_[i - 1].first]].push_back(component_[edges_[i - 1].second]);
    tree_data_[component_[edges_[i - 1].second]].push_back(component_[edges_[i - 1].first]);
  }
  for (int i = 1; i < tree_cnt_ + 1; ++i) {
    if (tree_data_[i].size() == 1) {
      ++ans;
    }
    if (tree_data_[i].empty() && tree_cnt_ != 1) {
      ans += 2;
    }
  }
  return ans / 2 + ans % 2;
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int v, u;
  for (int i = 0; i < graph.count_of_edges_; ++i) {
    is >> v >> u;
    graph.edges_[i] = {v, u};
    graph.data_[v].emplace_back(u, i + 1);
    graph.data_[u].emplace_back(v, i + 1);
  }
  return is;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  std::cout << graph.ATwoWayAttack();
  return 0;
}