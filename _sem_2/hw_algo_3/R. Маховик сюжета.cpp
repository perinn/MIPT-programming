#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
  int64_t start;
  int64_t end;
  int64_t time_in;
  int64_t time_out;
  Edge(int64_t, int64_t, int64_t, int64_t);
};

Edge::Edge(int64_t start0, int64_t time_in0, int64_t end0, int64_t time_out0) {
  start = start0;
  end = end0;
  time_in = time_in0;
  time_out = time_out0;
}

bool Comparator(const Edge& a, const Edge& b) {
  return a.time_in > b.time_in;
}

class Graph {
  std::vector<Edge> data_;
  int64_t n_;
  int64_t m_;

 public:
  Graph(int64_t, int64_t);
  friend std::istream& operator>>(std::istream&, Graph&);
  int64_t MinTime(int64_t, int64_t);
};

Graph::Graph(int64_t n, int64_t k) {
  n_ = n;
  m_ = k;
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int64_t start = 0;
  int64_t end = 0;
  int64_t time_in = 0;
  int64_t time_out = 0;
  for (int i = 0; i < graph.m_; ++i) {
    std::cin >> start >> time_in >> end >> time_out;
    graph.data_.emplace_back(--start, time_in, --end, time_out);
  }
  return is;
}

int64_t Graph::MinTime(int64_t a, int64_t b) {
  --a;
  --b;
  std::sort(data_.begin(), data_.end(), Comparator);
  std::vector<int64_t> dist(n_, INT64_MAX);
  dist[a] = 0;
  for (int64_t i = 0; i < n_; ++i) {
    for (int64_t j = 0; j < m_; ++j) {
      if (dist[data_[j].start] < INT64_MAX && data_[j].time_in >= dist[data_[j].start] &&
          dist[data_[j].end] > data_[j].time_out) {
        dist[data_[j].end] = data_[j].time_out;
      }
    }
  }
  return dist[b];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t a = 0;
  int64_t b = 0;
  int64_t k = 0;
  std::cin >> n >> a >> b >> k;
  Graph graph = Graph(n, k);
  std::cin >> graph;
  std::cout << graph.MinTime(a, b);
  return 0;
}