#include <iostream>
#include <vector>
#include <string>

std::vector<int64_t> PrefixFunction(std::string string) {
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
  return p;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string input;
  std::cin >> input;
  std::vector<int64_t> output = PrefixFunction(input);
  for (auto i : output) {
    std::cout << i << ' ';
  }
  return 0;
}