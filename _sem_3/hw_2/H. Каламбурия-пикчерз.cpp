#include <iostream>
#include <vector>
#include <string>

int64_t PrefixFunction(std::string string) {
  std::vector<int64_t> p(static_cast<int64_t>(string.size()), 0);
  int64_t k = 0;
  for (int64_t i = 1; i < static_cast<int64_t>(string.size()); ++i) {
    k = p[i - 1];
    while (string[i] != string[k] && k > 0) {
      k = p[k - 1];
    }
    if (string[i] == string[k]) {
      p[i] = k + 1;
    }
  }
  return p[static_cast<int64_t>(string.size()) - 1];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  std::string cur;
  std::string next;
  std::string tmp;
  std::cin >> n >> cur;
  for (int64_t i = 2; i <= n; ++i) {
    std::cin >> next;
    if (cur.size() > next.size()) {
      tmp = std::string(cur.begin() + static_cast<int64_t>(cur.size() - next.size()), cur.end());
    } else {
      tmp = cur;
    }
    cur += next.substr(PrefixFunction(next + '#' + tmp));
  }
  std::cout << cur;
  return 0;
}