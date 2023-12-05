#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int64_t PrefixFunction(std::string string) {
  std::vector<int64_t> p(static_cast<int64_t>(string.size()), 0);
  int64_t k = 0;
  int64_t max_pf = -1;
  for (int64_t i = 1; i < static_cast<int64_t>(string.size()); ++i) {
    k = p[i - 1];
    while (string[i] != string[k] && k > 0) {
      k = p[k - 1];
    }
    if (string[i] == string[k]) {
      p[i] = k + 1;
    }
    max_pf = std::max(max_pf, p[i]);
  }
  return max_pf;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string input;
  std::cin >> input;
  auto unique_words = static_cast<int64_t>(input.size());
  for (int64_t i = 1; i < static_cast<int64_t>(input.size()); ++i) {
    unique_words +=
        i - PrefixFunction(input[i] + std::string(std::make_reverse_iterator(input.begin() + i), input.rend()));
  }
  std::cout << unique_words;
  return 0;
}