#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

std::vector<int32_t> PrefixFunction(std::string s) {
  std::vector<int32_t> p(static_cast<int32_t>(s.size()), 0);
  int32_t k = 0;
  for (int32_t i = 1; i < static_cast<int32_t>(s.size()); ++i) {
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

std::vector<int32_t> KMP(std::string s, std::string p) {
  auto p_size = static_cast<int32_t>(p.size());
  std::vector<int32_t> ans;
  std::vector<int32_t> pi = PrefixFunction(p + "#" + s);
  for (int32_t i = p_size + 1; i <= p_size + static_cast<int32_t>(s.size()); ++i) {
    if (pi[i] == p_size) {
      ans.push_back(i - 2 * p_size);
    }
  }
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string str;
  std::string pat;
  std::cin >> str >> pat;
  std::vector<int32_t> output = KMP(str, pat);
  for (auto i : output) {
    std::cout << i << '\n';
  }
  return 0;
}