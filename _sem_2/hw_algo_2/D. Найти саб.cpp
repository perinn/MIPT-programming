#include <iostream>
#include <vector>
#include <queue>

struct Dot {
  int x = 0;
  int y = 0;
};

class Graph {
  std::vector<std::vector<int>> data_;
  std::queue<Dot> queue_;
  int height_;
  int lenght_;

 public:
  Graph(int, int);
  void TheShortestWayToSub();
  friend std::istream& operator>>(std::istream&, Graph&);
  friend std::ostream& operator<<(std::ostream&, Graph&);
};

Graph::Graph(int n, int m) {
  height_ = n;
  lenght_ = m;
  data_ = std::vector<std::vector<int>>(n + 2, std::vector<int>(m + 2, 0));
}

void Graph::TheShortestWayToSub() {
  int dist = 1;
  std::queue<Dot> another_queue;
  while (!queue_.empty()) {
    ++dist;
    while (!queue_.empty()) {
      Dot v = queue_.front();
      queue_.pop();
      for (int x = -1; x < 2; ++x) {
        for (int y = -1; y < 2; ++y) {
          if (abs(x) + abs(y) == 1) {
            if (data_[v.x + x][v.y + y] == 0) {
              if (v.x + x > 0 && v.x + x < height_ + 1 && v.y + y > 0 && v.y + y < lenght_ + 1) {
                another_queue.push({v.x + x, v.y + y});
              }
              data_[v.x + x][v.y + y] = dist;
            }
          }
        }
      }
    }
    queue_ = another_queue;
    while (!another_queue.empty()) {
      another_queue.pop();
    }
  }
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  for (int i = 1; i <= graph.height_; ++i) {
    for (int j = 1; j <= graph.lenght_; ++j) {
      std::cin >> graph.data_[i][j];
      if (graph.data_[i][j] == 1) {
        graph.queue_.push({i, j});
      }
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, Graph& graph) {
  for (int i = 1; i <= graph.height_; ++i) {
    for (int j = 1; j <= graph.lenght_; ++j) {
      std::cout << graph.data_[i][j] - 1 << ' ';
    }
    std::cout << '\n';
  }
  return os;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  graph.TheShortestWayToSub();
  std::cout << graph;
}