#include <iostream>
#include <vector>

std::vector<int> PalindromeFunction(const std::vector<int>& arr) {
  std::vector<int> pal(arr.size(), 0);
  int left = 0;
  int right = 0;
  for (int i = 1; i < static_cast<int>(arr.size()); ++i) {
    if (i <= right) {
      pal[i] = std::max(std::min(pal[right - i + 1 + left], right - i + 1), static_cast<int>(0));
    }
    while ((arr[i + pal[i]] == arr[i - pal[i] - 1]) && (i + pal[i] < static_cast<int>(arr.size())) &&
           (i - pal[i] >= 1)) {
      ++pal[i];
    }
    if (i + pal[i] > right + 1) {
      right = i + pal[i] - 1;
      left = i - pal[i];
    }
  }
  return pal;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<int> input(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> input[i];
  }
  std::vector<int> pal = PalindromeFunction(input);
  for (int i = n - 1; i >= 0; --i) {
    if (pal[i] == i) {
      std::cout << n - pal[i] << ' ';
    }
  }
  return 0;
}