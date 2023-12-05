#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
  int n, x;
  std::cin >> n;
  std::vector<int> arr(n);
  auto it = arr.begin();
  while (it != arr.end()) {
    std::cin >> *it;
    ++it;
  }
  std::cin >> x;
  std::cout << std::count(arr.begin(), arr.end(), x);
}