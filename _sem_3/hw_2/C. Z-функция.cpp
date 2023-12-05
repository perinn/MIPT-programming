#include <iostream>
#include <vector>
#include <string>

std::vector<int32_t> ZFunction(std::string s) {
  std::vector<int32_t> z(s.size(), 0);
  z[0] = static_cast<int32_t>(s.size());
  int32_t left = 0;
  int32_t right = 0;
  for (int32_t i = 1; i < static_cast<int32_t>(s.size()); ++i) {
    if (i < right) {
      z[i] = std::min(z[i - left], right - i);
    }
    while (i + z[i] < static_cast<int32_t>(s.size()) && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }
    if (right < i + z[i]) {
      left = i;
      right = i + z[i];
    }
  }
  return z;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string input;
  std::cin >> input;
  std::vector<int32_t> output = ZFunction(input);
  for (auto i : output) {
    std::cout << i << ' ';
  }
  return 0;
}