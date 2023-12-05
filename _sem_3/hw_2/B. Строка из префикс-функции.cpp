#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

std::string P2S(std::vector<int32_t> p) {
  std::string s(p.size(), ' ');
  s[0] = 'a';
  int32_t k = 0;
  for (int32_t i = 1; i < static_cast<int32_t>(p.size()); ++i) {
    if (p[i] > 0) {
      s[i] = s[p[i] - 1];
    } else {
      std::unordered_set<char> ban = {};
      k = p[i - 1];
      while (k > 0) {
        ban.insert(s[k]);
        k = p[k - 1];
      }
      for (char symbol = 'b'; symbol <= 'z'; ++symbol) {
        if (ban.find(symbol) == ban.end()) {
          s[i] = symbol;
          break;
        }
      }
    }
  }
  return s;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t n = 0;
  std::cin >> n;
  std::vector<int32_t> input(n);
  for (int32_t i = 0; i < n; ++i) {
    std::cin >> input[i];
  }
  std::string string = P2S(input);
  std::cout << string;
  return 0;
}