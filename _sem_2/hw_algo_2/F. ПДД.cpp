#include <iostream>
#include <vector>
#include <deque>

struct Dot {
  int start = 0;
  int end = 0;
};

class Graph {
  std::vector<std::vector<Dot>> data_;
  int count_vertex_;
  int count_edges_;

 public:
  Graph(int, int);
  int Cost(int, int) const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int count_vertex, int count_edges) {
  count_vertex_ = count_vertex;
  count_edges_ = count_edges;
  data_.resize(count_vertex_ + 1);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int a, b;
  for (int i = 0; i < graph.count_edges_; ++i) {
    is >> a >> b;
    graph.data_[a].push_back(Dot{0, b});
    graph.data_[b].push_back(Dot{1, a});
  }
  return is;
}

int Graph::Cost(int a, int b) const {
  std::vector<int> dist(count_vertex_ + 1, 1000000);
  std::vector<int> parent(count_vertex_ + 1, 0);
  std::deque<int> deque;
  deque.push_front(a);
  dist[a] = 0;
  while (!deque.empty()) {
    int first = deque.front();
    deque.pop_front();
    for (size_t i = 0; i < data_[first].size(); ++i) {
      int second = data_[first][i].end;
      int third = data_[first][i].start;
      if (dist[first] + third < dist[second]) {
        dist[second] = dist[first] + third;
        parent[second] = first;
        if (third == 0) {
          deque.push_front(second);
        } else {
          deque.push_back(second);
        }
      }
    }
  }
  if (dist[b] == 1000000) {
    return -1;
  }
  return dist[b];
}

int main() {
  int n, m, k, a, b;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph >> k;
  for (int i = 0; i < k; ++i) {
    std::cin >> a >> b;
    std::cout << graph.Cost(a, b) << '\n';
  }
}