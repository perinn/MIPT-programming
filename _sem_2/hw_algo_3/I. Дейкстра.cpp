#include <iostream>
#include <queue>
#include <vector>

struct Graph {
  std::vector<std::vector<std::pair<int64_t, int64_t>>> data;
  std::vector<bool> point_in;
  std::vector<int64_t> dist;
  int64_t n;
  void AddEdge(int64_t, int64_t);
  explicit Graph(int64_t);
  void Dijkstra(int64_t);
};

Graph::Graph(int64_t count_vertex) {
  n = count_vertex;
  data.resize(n);
  point_in.resize(n);
  dist.resize(n, 2009000999);
}

void Graph::AddEdge(int64_t a, int64_t w) {
  data[a].emplace_back(w, b);
  data[b].emplace_back(w, a);
}

void Graph::Dijkstra(int64_t s) {
  dist[s] = 0;
  std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>,
                      std::greater<std::pair<int64_t, int64_t>>>
      queue;
  queue.emplace(0, s);
  while (!queue.empty()) {
    auto v = queue.top();
    queue.pop();
    if (v.first > dist[v.second]) {
      continue;
    }
    for (auto u : data[v.second]) {
      if ((dist[u.second] > u.first + dist[v.second])) {
        dist[u.second] = u.first + dist[v.second];
        queue.emplace(dist[u.second], u.second);
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t k = 0;
  int64_t n = 0;
  int64_t m = 0;
  int64_t s = 0;
  int64_t a = 0;
  int64_t b = 0;
  int64_t w = 0;
  std::cin >> k;
  for (int64_t i = 0; i < k; ++i) {
    std::cin >> n >> m;
    Graph graph(n);
    for (int64_t i = 0; i < m; ++i) {
      std::cin >> a >> b >> w;
      graph.AddEdge(a, b, w);
    }
    std::cin >> s;
    graph.Dijkstra(s);
    for (int64_t i = 0; i < n; ++i) {
      std::cout << graph.dist[i] << ' ';
    }
  }
  return 0;
}