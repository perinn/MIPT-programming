#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t lenght_of_line = 0;
  int64_t current_sum = 0;
  int64_t left_border = 0;
  int64_t right_border = 0;
  int64_t position = -1;
  std::cin >> lenght_of_line;
  std::vector<int64_t> vector_of_smeshariki(lenght_of_line);
  for (int64_t index = 0; index < lenght_of_line; ++index) {
    std::cin >> vector_of_smeshariki[index];
  }
  int64_t final_sum = vector_of_smeshariki[0];
  for (int64_t index = 0; index < lenght_of_line; ++index) {
    current_sum += vector_of_smeshariki[index];
    if (current_sum > final_sum) {
      final_sum = current_sum;
      left_border = position + 1;
      right_border = index;
    }
    if (current_sum < 0) {
      current_sum = 0;
      position = index;
    }
  }
  std::cout << left_border + 1 << ' ' << right_border + 1 << ' ' << final_sum;
  return 0;
}