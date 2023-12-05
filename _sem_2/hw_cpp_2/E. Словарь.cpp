#include <iostream>
#include <unordered_map>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::unordered_map<std::string, std::string> map;
  int n, q;
  std::cin >> n;
  std::string word1, word2;
  for (int i = 0; i < n; ++i) {
    std::cin >> word1 >> word2;
    map[word1] = word2;
    map[word2] = word1;
  }
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::cin >> word1;
    std::cout << map[word1] << '\n';
  }
}