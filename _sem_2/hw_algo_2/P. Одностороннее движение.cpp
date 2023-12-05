#include <iostream>
#include <vector>
#include <set>

class Graph {
  std::vector<std::vector<std::pair<int, int>>> data_;
  int count_vertex_;
  int count_edges_;

 public:
  Graph(int, int);
  void DFS(int, int, std::vector<int>&, std::vector<int>&, std::vector<int>&, std::set<int>&, int&) const;
  void Bridges() const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int count_vertex, int count_edges) {
  count_vertex_ = count_vertex;
  count_edges_ = count_edges;
  data_.resize(count_vertex_ + 1);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int a, b;
  for (int i = 1; i <= graph.count_edges_; ++i) {
    is >> a >> b;
    graph.data_[a].emplace_back(b, i);
    graph.data_[b].emplace_back(a, i);
  }
  return is;
}

void Graph::DFS(int v, int p, std::vector<int>& time_in, std::vector<int>& time_up, std::vector<int>& colors,
                std::set<int>& bridges, int& time) const {
  time_up[v] = time_in[v] = ++time;
  colors[v] = 1;
  for (auto u : data_[v]) {
    if (u.first == p) {
      continue;
    }
    if (colors[u.first] == 1) {
      time_up[v] = std::min(time_up[v], time_in[u.first]);
    }
    if (colors[u.first] == 0) {
      DFS(u.first, v, time_in, time_up, colors, bridges, time);
      time_up[v] = std::min(time_up[v], time_up[u.first]);
      if (time_up[u.first] > time_in[v]) {
        int cnt = 0;
        for (auto i : data_[v]) {
          if (i.first == u.first) {
            ++cnt;
          }
        }
        if (cnt == 1) {
          bridges.emplace(u.second);
        }
      }
    }
  }
}

void Graph::Bridges() const {
  int time = 0;
  std::vector<int> colors(count_vertex_ + 1, 0);
  std::vector<int> time_in(count_vertex_ + 1, 0);
  std::vector<int> time_up(count_vertex_ + 1, 0);
  std::set<int> bridges;
  for (int i = 1; i <= count_vertex_; ++i) {
    if (colors[i] == 0) {
      DFS(i, -1, time_in, time_up, colors, bridges, time);
    }
  }
  std::cout << bridges.size() << '\n';
  for (auto i : bridges) {
    std::cout << i << ' ';
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  graph.Bridges();
  return 0;
}