#include <iostream>
#include <vector>
#include <string>

struct Node {
  int cbs_cnt = 0;
  int unused_lb_cnt = 0;
  int unused_rb_cnt = 0;

  Node() = default;

  void Merge(Node from1, Node from2) {
    int diff = std::min(from1.unused_lb_cnt, from2.unused_rb_cnt);
    cbs_cnt = from1.cbs_cnt + from2.cbs_cnt + diff;
    unused_lb_cnt = from1.unused_lb_cnt + from2.unused_lb_cnt - diff;
    unused_rb_cnt = from1.unused_rb_cnt + from2.unused_rb_cnt - diff;
  }
};

struct SegmentTree {
  size_t size = 0;
  std::vector<Node> st;

  SegmentTree() : size(0), st(0){};

  explicit SegmentTree(std::string bs) {
    size_t temp_size = 2 << (31 - __builtin_clz(bs.length()));
    if (temp_size == 2 * bs.length()) {
      size = 2 * bs.length();
    } else {
      size = 2 * temp_size;
    }
    st.resize(size);
    for (size_t i = (size + 1) / 2; i < bs.length() + (size + 1) / 2; ++i) {
      if (bs[i - (size + 1) / 2] == ')') {
        st[i].unused_rb_cnt = 1;
      } else {
        st[i].unused_lb_cnt = 1;
      }
    }
    for (size_t i = bs.length() + (size + 1) / 2; i < size; ++i) {
      st[i].unused_lb_cnt = 1;
    }
    for (int i = static_cast<int>((size + 1)) / 2 - 1; i > 0; --i) {
      st[i].Merge(st[2 * i], st[2 * i + 1]);
    }
  }

  int Query(int l, int r) {
    return Query(l, r, 1, 1, static_cast<int>(size / 2)).cbs_cnt;
  }

  Node Query(int l, int r, int vertex, int tl, int tr) {
    if (tl >= l && tr <= r) {
      return st[vertex];
    }
    if (tl > r || tr < l) {
      Node null_node;
      return null_node;
    }
    int tm = (tl + tr) / 2;
    Node la = Query(l, r, 2 * vertex, tl, tm);
    Node ra = Query(l, r, 2 * vertex + 1, tm + 1, tr);
    Node res;
    res.Merge(la, ra);
    return res;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string brackets_sequence;
  std::cin >> brackets_sequence;
  SegmentTree st(brackets_sequence);
  int m = 0;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    int l = 0;
    int r = 0;
    std::cin >> l >> r;
    std::cout << 2 * st.Query(l, r) << '\n';
  }
  return 0;
}