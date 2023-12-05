#include <iostream>
#include <vector>
#include <algorithm>

bool Comparator(const std::vector<int>& a, const std::vector<int>& b) {
  if (a[0] == b[0]) {
    if (a[1] == b[1]) {
      return a[2] < b[2];
    }
    return a[1] < b[1];
  }
  return a[0] > b[0];
}

int main() {
  int n, s, t;
  std::vector<std::vector<int>> arr;
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> s >> t;
    arr.push_back({s, t, i});
  }
  std::sort(arr.begin(), arr.end(), Comparator);
  for (size_t i = 0; i < arr.size(); ++i) {
    std::cout << arr[i][2] << '\n';
  }
}