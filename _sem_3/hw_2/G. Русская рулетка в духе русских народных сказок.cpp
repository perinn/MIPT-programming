#include <iostream>
#include <vector>
#include <string>

#include <unordered_set>

std::vector<int64_t> PrefixFunction(std::string s) {
  std::vector<int64_t> p(static_cast<int64_t>(s.size()), 0);
  int64_t k = 0;
  for (int64_t i = 1; i < static_cast<int64_t>(s.size()); ++i) {
    k = p[i - 1];
    while (s[i] != s[k] && k > 0) {
      k = p[k - 1];
    }
    if (s[i] == s[k]) {
      p[i] = k + 1;
    }
  }
  return p;
}

int64_t KMP(std::string s, std::string p) {
  auto p_size = static_cast<int64_t>(p.size());
  int64_t ans = 0;
  std::vector<int64_t> pi = PrefixFunction(p + "#" + s);
  for (int64_t i = p_size + 1; i <= p_size + static_cast<int64_t>(s.size()); ++i) {
    if (pi[i] == p_size) {
      ++ans;
    }
  }
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  std::string a;
  std::string b;
  std::cin >> n >> a >> b;
  bool flag0 = (KMP(b + "0" + b, a) == 1);
  bool flag1 = (KMP(b + "1" + b, a) == 1);
  if (flag0 xor flag1) {
    std::cout << (flag0 ? "No" : "Yes");
  } else {
    std::cout << "Random";
  }
  return 0;
}