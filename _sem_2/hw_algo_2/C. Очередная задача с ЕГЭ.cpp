#include <iostream>
#include <vector>
#include <deque>

class Graph {
  std::vector<uint64_t> parent_;
  uint64_t start_;
  uint64_t end_;

 public:
  Graph(uint64_t, uint64_t);
  uint64_t Count(uint64_t n) const;
  void Lenght(uint64_t n) const;
  void BFS();
};

Graph::Graph(uint64_t start, uint64_t end) {
  start_ = start;
  end_ = end;
  parent_ = std::vector<uint64_t>(10000);
}

uint64_t Graph::Count(uint64_t n) const {
  if (n <= 0) {
    return 0;
  }
  return 1 + Count(parent_[n]);
}

void Graph::Lenght(uint64_t n) const {
  if (n <= 0) {
    return;
  }
  Lenght(parent_[n]);
  std::cout << n << '\n';
}

void Graph::BFS() {
  std::vector<uint64_t> current(10000, 0);
  std::deque<uint64_t> deque;
  uint64_t could, now;
  current[start_] = 1;
  deque.push_front(start_);
  while (!deque.empty()) {
    now = deque.front();
    deque.pop_front();
    if (now == end_) {
      break;
    }
    for (int i = 0; i < 4; ++i) {
      if (i == 0) {
        could = now / 1000 != 9 ? now + 1000 : now;
      } else if (i == 1) {
        could = (now % 10 != 1) ? now - 1 : now;
      } else if (i == 2) {
        could = (now % 1000) * 10 + now / 1000;
      } else {
        could = (now % 10) * 1000 + now / 10;
      }
      if (current[could] == 0) {
        deque.push_back(could);
        parent_[could] = now;
        current[could] = 1;
      }
    }
  }
}

int main() {
  uint64_t start, end;
  std::cin >> start >> end;
  Graph graph = Graph(start, end);
  graph.BFS();
  std::cout << graph.Count(end) << '\n';
  graph.Lenght(end);
  return 0;
}