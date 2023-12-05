#include <iostream>
#include <queue>

class Edge;
class Graph;

class Edge {
  int64_t start_;
  int64_t end_;
  int64_t flow_;
  int64_t max_flow_;
  int64_t index_;
  int64_t id_;

 public:
  Edge();
  Edge(int64_t, int64_t, int64_t, int64_t, int64_t, int64_t);
  friend Graph;
};

Edge::Edge() {
  start_ = 0;
  end_ = 0;
  flow_ = 0;
  max_flow_ = 0;
  index_ = 0;
  id_ = 0;
}

Edge::Edge(int64_t start, int64_t end, int64_t flow, int64_t max_flow, int64_t index, int64_t id) {
  start_ = start;
  end_ = end;
  flow_ = flow;
  max_flow_ = max_flow;
  index_ = index;
  id_ = id;
}

class Graph {
  int64_t n_;
  int64_t m_;
  std::vector<int64_t> dist_;
  std::vector<std::vector<Edge>> data_;
  std::vector<std::pair<int64_t, int64_t>> parent_;
  std::vector<int64_t> flow_;

 public:
  Graph(int64_t, int64_t);
  int64_t BFS(int64_t, int64_t);
  int64_t Max();
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int64_t n, int64_t m) {
  n_ = n;
  m_ = m;
  data_.resize(n + 1);
  parent_.resize(n + 1);
  dist_.resize(n + 1, INT64_MAX);
  flow_.resize(n + 1, INT64_MAX);
}

int64_t Graph::BFS(int64_t a, int64_t b) {
  dist_[a] = 0;
  flow_[a] = INT64_MAX;
  std::queue<int64_t> queque;
  queque.push(a);
  while (!queque.empty()) {
    int64_t v = queque.front();
    queque.pop();
    if (v == b) {
      int64_t v_res = v;
      while (v != 1) {
        auto& u = data_[parent_[v].first][parent_[v].second];
        u.flow_ += flow_[v_res];
        data_[u.end_][u.id_].flow_ -= flow_[v_res];
        v = u.start_;
      }
      return 1;
    }
    for (auto& u : data_[v]) {
      if (u.flow_ < u.max_flow_) {
        if (dist_[u.end_] > dist_[v] + 1) {
          dist_[u.end_] = dist_[v] + 1;
          parent_[u.end_] = {v, u.index_};
          flow_[u.end_] = std::min(flow_[v], u.max_flow_ - u.flow_);
          queque.push(u.end_);
        }
      }
    }
  }
  return 0;
}

int64_t Graph::Max() {
  bool is_not_null = true;
  while (is_not_null) {
    is_not_null = BFS(1, n_);
    for (int64_t i = 0; i < n_ + 1; ++i) {
      dist_[i] = INT64_MAX;
      flow_[i] = INT64_MAX;
    }
  }
  int64_t result = 0;
  for (auto v : data_[1]) {
    result += v.flow_;
  }
  return result;
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int64_t start = 0;
  int64_t end = 0;
  int64_t weight = 0;
  int64_t index = 0;
  int64_t id = 0;
  for (int64_t i = 0; i < graph.m_; ++i) {
    std::cin >> start >> end >> weight;
    index = static_cast<int64_t>(graph.data_[start].size());
    id = static_cast<int64_t>(graph.data_[end].size());
    graph.data_[start].emplace_back(Edge(start, end, 0, weight, index, id));
    index = static_cast<int64_t>(graph.data_[end].size());
    id = static_cast<int64_t>(graph.data_[start].size()) - 1;
    graph.data_[end].emplace_back(Edge(end, start, 0, 0, index, id));
  }
  return is;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  std::cout << graph.Max();
  return 0;
}