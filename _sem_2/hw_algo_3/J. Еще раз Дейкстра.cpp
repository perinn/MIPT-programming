#include <iostream>
#include <queue>
#include <vector>

struct Graph {
  std::vector<std::vector<std::pair<int64_t, int64_t>>> data;
  std::vector<bool> point_in;
  std::vector<int64_t> dist;
  int64_t n;
  void AddEdge(int64_t, int64_t, int64_t);
  explicit Graph(int64_t);
  int64_t Dijkstra(int64_t, int64_t);
};

Graph::Graph(int64_t count_vertex) {
  n = count_vertex;
  data.resize(n);
  point_in.resize(n);
  dist.resize(n, INT64_MAX);
}

void Graph::AddEdge(int64_t a, int64_t b, int64_t w) {
  data[a].emplace_back(w, b);
}

int64_t Graph::Dijkstra(int64_t s, int64_t f) {
  dist[s] = 0;
  std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>,
                      std::greater<std::pair<int64_t, int64_t>>>
      queue;
  queue.emplace(0, s);
  while (!queue.empty()) {
    auto v = queue.top();
    queue.pop();
    if (v.second == f) {
      break;
    }
    for (auto u : data[v.second]) {
      if ((dist[u.second] > u.first + dist[v.second])) {
        dist[u.second] = u.first + dist[v.second];
        queue.emplace(dist[u.second], u.second);
      }
    }
  }
  if (dist[f] == INT64_MAX) {
    return -1;
  }
  return dist[f];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int s = 0;
  int f = 0;
  int w = 0;
  std::cin >> n >> s >> f;
  Graph graph = Graph(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> w;
      if (w > 0) {
        graph.AddEdge(i, j, w);
      }
    }
  }
  std::cout << graph.Dijkstra(--s, --f);
  return 0;
}