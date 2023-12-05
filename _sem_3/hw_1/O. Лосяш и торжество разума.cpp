#include <iostream>
#include <vector>
#include <string>

int64_t Left(int64_t i) {
  return 2 * i + 1;
}

int64_t Right(int64_t i) {
  return 2 * i + 2;
}

int64_t RoundToTwo(int64_t n) {
  int64_t res = 1;
  while (res < n) {
    res <<= 1;
  }
  return res;
}

class SegmentTree {
  struct Node {
    int64_t pairs = 0;
    int64_t open = 0;
    int64_t closed = 0;

    Node() {
      this->closed = 0;
      this->open = 0;
      this->pairs = 0;
    };
  };
  std::vector<Node> tree_;
  int64_t n_;

 public:
  explicit SegmentTree(const std::string&);
  void Build(const std::string&, int64_t, int64_t, int64_t);
  int64_t Query(int64_t, int64_t);
  Node Merge(Node left, Node right) {
    Node parent;
    int64_t min_matched = std::min(left.open, right.closed);
    parent.pairs = left.pairs + right.pairs + min_matched;
    parent.open = left.open + right.open - min_matched;
    parent.closed = left.closed + right.closed - min_matched;
    return parent;
  }
  Node Query(int64_t l, int64_t r, int64_t a, int64_t b, int64_t i) {
    if (l > b || r < a) {
      Node null_node;
      return null_node;
    }
    if (l >= a && r <= b) {
      return tree_[i];
    }
    int64_t mid = (l + r) / 2;
    Node left = Query(l, mid, a, b, Left(i));
    Node right = Query(mid + 1, r, a, b, Right(i));
    Node res = Merge(left, right);
    return res;
  }
};

SegmentTree::SegmentTree(const std::string& str) {
  n_ = static_cast<int64_t>(str.size());
  tree_ = std::vector<Node>(2 * RoundToTwo(n_) - 1);
  Build(str, 0, n_ - 1, 0);
}

void SegmentTree::Build(const std::string& str, int64_t l, int64_t r, int64_t i) {
  if (l == r) {
    tree_[i].pairs = 0;
    tree_[i].open = (str[l] == '(' ? 1 : 0);
    tree_[i].closed = (str[l] == ')' ? 1 : 0);
    return;
  }
  int64_t mid = (l + r) / 2;
  Build(str, l, mid, Left(i));
  Build(str, mid + 1, r, Right(i));
  tree_[i] = Merge(tree_[Left(i)], tree_[Right(i)]);
}

int64_t SegmentTree::Query(int64_t l, int64_t r) {
  Node ans = Query(0, n_ - 1, l, r, 0);
  return 2 * ans.pairs;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string input;
  std::cin >> input;
  SegmentTree st = SegmentTree(input);
  int64_t m = 0;
  int64_t l = 0;
  int64_t r = 0;
  std::cin >> m;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> l >> r;
    std::cout << st.Query(l - 1, r - 1) << '\n';
  }
  return 0;
}