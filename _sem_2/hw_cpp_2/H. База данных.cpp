#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

bool Comparator(const std::string& a, const std::string& b) {
  for (size_t i = 0; i < std::min(a.size(), b.size()); ++i) {
    if (a[i] < b[i]) {
      return true;
    }
    if (a[i] > b[i]) {
      return false;
    }
  }
  return a.size() < b.size();
}

bool Comparator1(const std::pair<std::string, std::vector<std::pair<std::string, int64_t>>>& a,
                 const std::pair<std::string, std::vector<std::pair<std::string, int64_t>>>& b) {
  return Comparator(a.first, b.first);
}

bool Comparator2(const std::pair<std::string, int64_t>& a, const std::pair<std::string, int64_t>& b) {
  return Comparator(a.first, b.first);
}

int main() {
  std::string name, product;
  int64_t count;
  std::unordered_map<std::string, std::unordered_map<std::string, int64_t>> map;
  // for (int64_t i = 0; i < 6; ++i) {
  while (std::cin >> name >> product >> count) {
    // std::cin >> name >> product >> count;
    if (map.find(name) != map.end()) {
      if (map[name].find(product) != map[name].end()) {
        map[name][product] += count;
      } else {
        map[name][product] = count;
      }
    } else {
      map[name][product] = count;
    }
  }
  std::vector<std::pair<std::string, std::vector<std::pair<std::string, int64_t>>>> list;
  std::vector<std::pair<std::string, int64_t>> tmp_list;
  for (auto person : map) {
    for (auto product : person.second) {
      tmp_list.emplace_back(product.first, product.second);
    }
    list.emplace_back(person.first, tmp_list);
    while (!tmp_list.empty()) {
      tmp_list.pop_back();
    }
  }
  std::sort(list.begin(), list.end(), Comparator1);
  for (size_t i = 0; i < list.size(); ++i) {
    std::sort(list[i].second.begin(), list[i].second.end(), Comparator2);
    std::cout << list[i].first << ":\n";
    for (size_t j = 0; j < list[i].second.size(); ++j) {
      std::cout << list[i].second[j].first << ' ' << list[i].second[j].second << '\n';
    }
  }
  return 0;
}