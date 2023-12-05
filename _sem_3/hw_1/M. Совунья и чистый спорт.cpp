#include <iostream>
#include <vector>

class SegmentTree {
  std::vector<uint32_t> tree_;
  uint32_t a_;
  uint32_t b_;
  uint32_t cur_;

 public:
  SegmentTree(uint32_t, uint32_t, uint32_t);
  uint32_t NextRand();
  void UpdateMTimes(uint32_t);
  uint32_t ResultOfQQuery(uint32_t);
  std::vector<uint32_t> TwoStepsAgo();
};

SegmentTree::SegmentTree(uint32_t n, uint32_t a, uint32_t b) {
  tree_ = std::vector<uint32_t>(n, 0);
  a_ = a;
  b_ = b;
  cur_ = 0;
}

uint32_t SegmentTree::NextRand() {
  cur_ = cur_ * a_ + b_;
  return cur_ >> 8;
}

void SegmentTree::UpdateMTimes(uint32_t m) {
  uint32_t add = 0;
  uint32_t l = 0;
  uint32_t r = 0;
  for (uint32_t i = 0; i < m; ++i) {
    add = NextRand();
    l = NextRand();
    r = NextRand();
    if (l > r) {
      std::swap(l, r);
    }
    if (r != tree_.size() - 1) {
      tree_[r + 1] -= add;
    }
    tree_[l] += add;
  }
}

std::vector<uint32_t> SegmentTree::TwoStepsAgo() {
  std::vector<uint32_t> step_ago(tree_.size());
  step_ago[0] = tree_[0];
  for (uint32_t i = 1; i < tree_.size(); ++i) {
    step_ago[i] = step_ago[i - 1] + tree_[i];
  }
  std::vector<uint32_t> two_step_ago(tree_.size());
  two_step_ago[0] = step_ago[0];
  for (uint32_t i = 1; i < tree_.size(); ++i) {
    two_step_ago[i] = two_step_ago[i - 1] + step_ago[i];
  }
  return two_step_ago;
}

uint32_t SegmentTree::ResultOfQQuery(uint32_t q) {
  uint32_t l = 0;
  uint32_t r = 0;
  uint64_t res = 0;
  auto two_step_ago = TwoStepsAgo();
  for (uint32_t i = 0; i < q; ++i) {
    l = NextRand();
    r = NextRand();
    if (l > r) {
      std::swap(l, r);
    }
    res = (res + (two_step_ago[r]));
    if (l != 0) {
      res = (res - two_step_ago[l - 1]);
    }
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  uint32_t m = 0;
  uint32_t q = 0;
  uint32_t a = 0;
  uint32_t b = 0;
  std::cin >> m >> q >> a >> b;
  SegmentTree st = SegmentTree(1 << 24, a, b);
  st.UpdateMTimes(m);
  std::cout << st.ResultOfQQuery(q);
  return 0;
}