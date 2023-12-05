#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

bool Comparator(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
  if (a.first == b.first) {
    for (size_t i = 0; i < std::min(a.second.size(), b.second.size()); ++i) {
      if (a.second[i] < b.second[i]) {
        return true;
      }
      if (a.second[i] > b.second[i]) {
        return false;
      }
    }
    return a.second.size() < b.second.size();
  }
  return a.first > b.first;
}

int main() {
  std::unordered_map<std::string, int> map;
  std::string word;
  while (std::cin >> word) {
    if (map.find(word) != map.end()) {
      ++map[word];
    } else {
      map[word] = 1;
    }
  }
  std::vector<std::pair<int, std::string>> list;
  for (auto obj : map) {
    list.emplace_back(obj.second, obj.first);
  }
  std::sort(list.begin(), list.end(), Comparator);
  for (size_t i = 0; i < list.size(); ++i) {
    std::cout << list[i].second << '\n';
  }
}