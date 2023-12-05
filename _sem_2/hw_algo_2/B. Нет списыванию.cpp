#include <iostream>
#include <vector>
#include <queue>

class Graph {
  std::vector<std::vector<uint64_t>> data_;
  uint64_t count_vertex_;
  uint64_t count_edges_;

 public:
  Graph(uint64_t, uint64_t);
  void TheShortestWay(uint64_t, uint64_t) const;
  bool IsBipartite() const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(uint64_t count_vertex, uint64_t count_edges) {
  count_vertex_ = count_vertex;
  count_edges_ = count_edges;
  data_.resize(count_vertex_ + 1);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  uint64_t a, b;
  for (uint64_t i = 0; i < graph.count_edges_; ++i) {
    is >> a >> b;
    graph.data_[a].push_back(b);
    graph.data_[b].push_back(a);
  }
  return is;
}

void Graph::TheShortestWay(uint64_t a, uint64_t b) const {
  const uint64_t inf = 1000000;
  std::vector<uint64_t> dist(count_vertex_ + 1, inf);
  std::vector<uint64_t> parent(count_vertex_ + 1, 0);
  std::queue<uint64_t> queue;
  queue.push(a);
  std::vector<uint64_t> way;
  dist[a] = 0;
  bool flag = true;
  while (!queue.empty() && flag) {
    uint64_t v = queue.front();
    queue.pop();
    for (uint64_t i = 0; i < data_[v].size() && flag; ++i) {
      uint64_t u = data_[v][i];
      if (dist[u] == inf) {
        dist[u] = dist[v] + 1;
        parent[u] = v;
        queue.push(u);
        if (u == b) {
          flag = false;
        }
      }
    }
  }
  if (dist[b] == inf) {
    std::cout << -1;
    return;
  }
  uint64_t tmp = b;
  while (tmp != a) {
    way.push_back(tmp);
    tmp = parent[tmp];
  }
  way.push_back(a);
  std::cout << dist[b] << '\n';
  for (uint64_t i = 0; i < way.size(); ++i) {
    std::cout << way[way.size() - 1 - i] << ' ';
  }
}

bool Graph::IsBipartite() const {
  enum color_types { white, gray, black };
  std::vector<color_types> colors(count_vertex_ + 1, white);
  std::queue<uint64_t> queue;
  bool flag = true;
  while (flag) {
    flag = false;
    uint64_t s = 1;
    for (uint64_t i = 1; i < data_.size(); ++i) {
      if ((!data_[i].empty()) && colors[i] == 0) {
        flag = true;
        s = i;
        break;
      }
    }
    colors[s] = gray;
    queue.push(s);
    while (!queue.empty()) {
      uint64_t a = queue.front();
      queue.pop();
      for (uint64_t i = 0; i < data_[a].size(); ++i) {
        uint64_t b = data_[a][i];
        if (colors[b] == 0) {
          colors[b] = colors[a] == gray ? black : gray;
          queue.push(b);
        } else if (colors[a] == colors[b]) {
          return false;
        }
      }
    }
  }
  return true;
}

int main() {
  uint64_t n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  if (graph.IsBipartite()) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}