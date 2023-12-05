#include <iostream>
#include <vector>
#include <cmath>

int64_t Parent(int64_t i) {
  return std::floor((i - 1) / 2);
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
  std::vector<int64_t> tree_;
  int64_t neutral_ = 0;
  int64_t n_;
  int64_t Operation(int64_t a, int64_t b) {
    return std::max(a, b);
  }

 public:
  explicit SegmentTree(const std::vector<int64_t>&);
  void Query(int64_t, int64_t);
  void Update(int64_t, int64_t);
};

SegmentTree::SegmentTree(const std::vector<int64_t>& arr) {
  n_ = RoundToTwo(static_cast<int64_t>(arr.size()));
  tree_ = std::vector<int64_t>(2 * n_ - 1, neutral_);
  for (int64_t i = n_ - 1; i < 2 * n_ - 1; ++i) {
    if (i - n_ + 1 < static_cast<int64_t>(arr.size())) {
      tree_[i] = arr[i - n_ + 1];
    }
  }
  for (int64_t i = n_ - 2; i >= 0; --i) {
    tree_[i] = Operation(tree_[Left(i)], tree_[Right(i)]);
  }
}

void SegmentTree::Query(int64_t l, int64_t r) {
  int64_t cnt = 0;
  l += n_ - 1;
  r += n_ - 1;
  int64_t l_old = l;
  int64_t r_old = r;
  int64_t left_res = neutral_;
  int64_t right_res = neutral_;
  while (l < r) {
    if (IsRightSon(l)) {
      left_res = Operation(left_res, tree_[l]);
    }
    if (IsLeftSon(r)) {
      right_res = Operation(tree_[r], right_res);
    }
    l = Parent(l + 1);
    r = Parent(r - 1);
  }
  if (l == r) {
    left_res = Operation(left_res, tree_[l]);
  }
  int64_t ans = Operation(left_res, right_res);
  for (int64_t i = l_old; i < r_old + 1; ++i) {
    if (tree_[i] == ans) {
      ++cnt;
    }
  }
  std::cout << ans << ' ' << cnt << '\n';
}

void SegmentTree::Update(int64_t i, int64_t v) {
  i += n_ - 1;
  tree_[i] = v;
  while (i != 0) {
    i = Parent(i);
    tree_[i] = Operation(tree_[Left(i)], tree_[Right(i)]);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t q = 0;
  int64_t l = 0;
  int64_t r = 0;
  std::cin >> n;
  std::vector<int64_t> input(n);
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> input[i];
  }
  SegmentTree segment_tree = SegmentTree(input);
  std::cin >> q;
  for (int64_t i = 0; i < q; ++i) {
    std::cin >> l >> r;
    segment_tree.Query(l - 1, r - 1);
  }
  return 0;
}