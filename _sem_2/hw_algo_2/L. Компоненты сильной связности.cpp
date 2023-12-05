#include <iostream>
#include <vector>

class Graph {
  std::vector<std::vector<int>> data_;
  int cnt_vertex_;

 public:
  explicit Graph(int);
  void AddEdge(int a, int b);
  int GetcntOfVertex() const;
  void DFS1(int, std::vector<bool>&, std::vector<int>&);
  void DFS2(int, std::vector<bool>&, std::vector<int>&);
};

Graph::Graph(int cnt_vertex) {
  cnt_vertex_ = cnt_vertex;
  data_.resize(cnt_vertex_);
}

void Graph::AddEdge(int a, int b) {
  data_[a].push_back(b);
}

int Graph::GetcntOfVertex() const {
  return cnt_vertex_;
}

void Graph::DFS1(int v, std::vector<bool>& used, std::vector<int>& order) {
  used[v] = true;
  for (size_t i = 0; i < data_[v].size(); ++i) {
    if (!used[data_[v][i]]) {
      DFS1(data_[v][i], used, order);
    }
  }
  order.push_back(v);
}

void Graph::DFS2(int v, std::vector<bool>& used, std::vector<int>& component) {
  used[v] = true;
  component.push_back(v);
  for (size_t i = 0; i < data_[v].size(); ++i) {
    if (!used[data_[v][i]]) {
      DFS2(data_[v][i], used, component);
    }
  }
}

void ComponentsOfStrongConnectivity(Graph& graph, Graph& another_graph) {
  int cnt = 0, n = graph.GetcntOfVertex(), v, i;
  std::vector<bool> used;
  std::vector<int> component;
  std::vector<int> order;
  std::vector<std::vector<int>> components;
  used.assign(n, false);
  for (i = 0; i < n; ++i) {
    if (!used[i]) {
      graph.DFS1(i, used, order);
    }
  }
  used.assign(n, false);
  for (i = 0; i < n; ++i) {
    v = order[n - i - 1];
    if (!used[v]) {
      another_graph.DFS2(v, used, component);
      components.push_back(component);
      ++cnt;
      component.clear();
    }
  }
  std::cout << cnt << '\n';
  std::vector<int> ans(n);
  for (i = 0; i < cnt; ++i) {
    for (auto j : components[i]) {
      ans[j] = i;
    }
  }
  for (i = 0; i < n; ++i) {
    std::cout << ans[i] + 1 << ' ';
  }
}

int main() {
  int n, m, a, b, i;
  std::cin >> n >> m;
  Graph graph = Graph(n);
  Graph another_graph = Graph(n);
  for (i = 0; i < m; ++i) {
    std::cin >> a >> b;
    graph.AddEdge(--a, --b);
    another_graph.AddEdge(b, a);
  }
  ComponentsOfStrongConnectivity(graph, another_graph);
  return 0;
}