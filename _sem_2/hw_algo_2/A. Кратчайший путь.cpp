#include <iostream>
#include <vector>
#include <queue>

class Graph {
  std::vector<std::vector<int64_t>> data_;
  int64_t count_vertex_;
  int64_t count_edges_;
  std::vector<int64_t> dist_;
  std::vector<int64_t> parent_;
  std::queue<int64_t> queue_;
  std::vector<int64_t> way_;
  bool flag_;

 public:
  Graph(int64_t, int64_t);
  int64_t TheShortestWayLenght(int64_t, int64_t);
  void TheShortestWay();
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int64_t count_vertex, int64_t count_edges) {
  count_vertex_ = count_vertex;
  count_edges_ = count_edges;
  data_.resize(count_vertex_ + 1);
  dist_ = std::vector<int64_t>(count_vertex_ + 1, 1000000);
  parent_ = std::vector<int64_t>(count_vertex_ + 1, 0);
  flag_ = true;
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int64_t a, b;
  for (int64_t i = 0; i < graph.count_edges_; ++i) {
    is >> a >> b;
    graph.data_[a].push_back(b);
    graph.data_[b].push_back(a);
  }
  return is;
}

int64_t Graph::TheShortestWayLenght(int64_t a, int64_t b) {
  queue_.push(a);
  dist_[a] = 0;
  bool flag = true;
  while (!queue_.empty() && flag) {
    int64_t v = queue_.front();
    queue_.pop();
    for (size_t i = 0; i < data_[v].size() && flag; ++i) {
      int64_t u = data_[v][i];
      if (dist_[u] == 1000000) {
        dist_[u] = dist_[v] + 1;
        parent_[u] = v;
        queue_.push(u);
        if (u == b) {
          flag = false;
        }
      }
    }
  }
  if (dist_[b] == 1000000) {
    flag_ = false;
    return -1;
  }
  int64_t tmp = b;
  while (tmp != a) {
    way_.push_back(tmp);
    tmp = parent_[tmp];
  }
  way_.push_back(a);
  return dist_[b];
}

void Graph::TheShortestWay() {
  if (flag_) {
    for (size_t i = 0; i < way_.size(); ++i) {
      std::cout << way_[way_.size() - 1 - i] << ' ';
    }
  }
}

int main() {
  int64_t n, m, a, b;
  std::cin >> n >> m >> a >> b;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  std::cout << graph.TheShortestWayLenght(a, b) << '\n';
  graph.TheShortestWay();
  return 0;
}