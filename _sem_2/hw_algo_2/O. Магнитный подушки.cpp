#include <iostream>
#include <vector>
#include <set>

class Graph {
  std::vector<std::vector<int>> data_;
  int count_vertex_;
  int count_pillows_;
  int count_edges_;

 public:
  Graph(int, int);
  void DFS(int, int, std::vector<bool>&, std::vector<int>&, std::vector<int>&, std::set<int>&) const;
  void PointsOfArticulation() const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int count_vertex, int count_pillows) {
  count_vertex_ = count_vertex;
  count_pillows_ = count_pillows;
  data_.resize(count_vertex_ + count_pillows_ + 1);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  int a, b, c;
  for (int i = graph.count_vertex_ + 1; i < graph.count_vertex_ + graph.count_pillows_ + 1; ++i) {
    is >> a >> b >> c;
    graph.data_[i].push_back(a);
    graph.data_[a].push_back(i);
    graph.data_[i].push_back(b);
    graph.data_[b].push_back(i);
    graph.data_[i].push_back(c);
    graph.data_[c].push_back(i);
  }
  return is;
}

void Graph::DFS(int first, int parameter, std::vector<bool>& used, std::vector<int>& height,
                std::vector<int>& destination, std::set<int>& points) const {
  used[first] = true;
  destination[first] = height[first] = (parameter == -1 ? 0 : height[parameter] + 1);
  int child = 0;
  for (int second : data_[first]) {
    if (second != parameter) {
      if (used[second]) {
        destination[first] = std::min(destination[first], height[second]);
      } else {
        DFS(second, first, used, height, destination, points);
        destination[first] = std::min(destination[first], destination[second]);
        if (height[first] <= destination[second] && parameter != -1 && first > count_vertex_) {
          points.emplace(first);
        }
        child++;
      }
    }
  }
  if (parameter == -1 && child > 1 && first > count_vertex_) {
    points.emplace(first);
  }
}

void Graph::PointsOfArticulation() const {
  std::vector<bool> used(count_vertex_ + count_pillows_ + 1, false);
  std::vector<int> height(count_vertex_ + count_pillows_ + 1);
  std::vector<int> destination(count_vertex_ + count_pillows_ + 1);
  std::set<int> points;
  for (size_t i = 1; i < data_.size(); ++i) {
    if (!used[i]) {
      DFS(i, -1, used, height, destination, points);
    }
  }
  std::cout << points.size() << '\n';
  for (auto i : points) {
    std::cout << i - count_vertex_ << '\n';
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n, m);
  std::cin >> graph;
  graph.PointsOfArticulation();
  return 0;
}