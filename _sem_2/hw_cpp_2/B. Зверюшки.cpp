#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int n, m, color;
  std::cin >> n;
  std::vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    std::cin >> color;
    std::cout << std::upper_bound(arr.begin(), arr.end(), color) - std::lower_bound(arr.begin(), arr.end(), color)
              << ' ';
  }
}