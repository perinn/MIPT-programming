#include <iostream>
#include <vector>
#include <cmath>

int64_t Parent(int64_t i) {
  return static_cast<int64_t>(std::floor((i - 1) / 2));
}

int64_t Left(int64_t i) {
  return 2 * i + 1;
}

int64_t Right(int64_t i) {
  return 2 * i + 2;
}

bool IsLeftSon(int64_t i) {
  return i % 2 == 1;
}

bool IsRightSon(int64_t i) {
  return i % 2 == 0;
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
    int64_t value;
    int64_t promise;
  };
  std::vector<Node> tree_;
  int64_t neutral_ = 0;
  int64_t n_;
  int64_t Max(int64_t a, int64_t b) {
    return std::max(a, b);
  }
  int64_t Plus(int64_t a, int64_t b) {
    return a + b;
  }

 public:
  explicit SegmentTree(const std::vector<int64_t>&);
  void Push(int64_t);
  int64_t Query(int64_t, int64_t, int64_t, int64_t, int64_t);
  void Update(int64_t, int64_t, int64_t, int64_t, int64_t, int64_t);
};

SegmentTree::SegmentTree(const std::vector<int64_t>& arr) {
  n_ = RoundToTwo(static_cast<int64_t>(arr.size()));
  tree_ = std::vector<Node>(2 * n_ - 1, {neutral_, neutral_});
  for (int64_t i = n_ - 1; i < 2 * n_ - 1; ++i) {
    if (i - n_ + 1 < static_cast<int64_t>(arr.size())) {
      tree_[i].value = arr[i - n_ + 1];
    }
  }
  for (int64_t i = n_ - 2; i >= 0; --i) {
    tree_[i].value = Max(tree_[Left(i)].value, tree_[Right(i)].value);
  }
}

void SegmentTree::Push(int64_t node) {
  tree_[node].value = Plus(tree_[node].value, tree_[node].promise);
  tree_[Left(node)].promise = Plus(tree_[Left(node)].promise, tree_[node].promise);
  tree_[Right(node)].promise = Plus(tree_[Right(node)].promise, tree_[node].promise);
  tree_[node].promise = neutral_;
}

int64_t SegmentTree::Query(int64_t l, int64_t r, int64_t node, int64_t a, int64_t b) {
  if (b == -1) {
    b = 2 * n_ - 2;
    l += n_ - 1;
    r += n_ - 1;
    a += n_ - 1;
  }
  if (a >= l && b <= r) {
    return Plus(tree_[node].value, tree_[node].promise);
  }
  if (l > b || a > r) {
    return neutral_;
  }
  Push(node);
  int64_t left = Query(l, r, Left(node), a, static_cast<int64_t>(std::floor((a + b) / 2)));
  int64_t right = Query(l, r, Right(node), static_cast<int64_t>(std::floor((a + b) / 2) + 1), b);
  return Max(left, right);
}

void SegmentTree::Update(int64_t l, int64_t r, int64_t node, int64_t a, int64_t b, int64_t delta) {
  if (b == -1) {
    b = 2 * n_ - 2;
    l += n_ - 1;
    r += n_ - 1;
    a += n_ - 1;
  }
  if (a >= l && b <= r) {
    tree_[node].promise = Plus(tree_[node].promise, delta);
    return;
  }
  if (l > b || a > r) {
    return;
  }
  Push(node);
  Update(l, r, Left(node), a, static_cast<int64_t>(std::floor((a + b) / 2)), delta);
  Update(l, r, Right(node), static_cast<int64_t>(std::floor((a + b) / 2) + 1), b, delta);
  tree_[node].value = Max(Plus(tree_[Left(node)].value, tree_[Left(node)].promise),
                          Plus(tree_[Right(node)].value, tree_[Right(node)].promise));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  std::cin >> n;
  std::vector<int64_t> input(n);
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> input[i];
  }
  SegmentTree segment_tree = SegmentTree(input);
  int64_t q = 0;
  std::cin >> q;
  int64_t l = 0;
  int64_t r = 0;
  int64_t add = 0;
  char com = ' ';
  for (int64_t i = 0; i < q; ++i) {
    std::cin >> com >> l >> r;
    if (com == 'm') {
      std::cout << segment_tree.Query(l - 1, r - 1, 0, 0, -1) << ' ';
    } else if (com == 'a') {
      std::cin >> add;
      segment_tree.Update(l - 1, r - 1, 0, 0, -1, add);
    }
  }
  return 0;
}