#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t count_of_sculptures = 0;
  int64_t count_of_questions = 0;
  int64_t left_border = 0;
  int64_t right_border = 0;
  std::cin >> count_of_sculptures;
  std::vector<int64_t> vector_of_sculptures(count_of_sculptures);
  std::cin >> vector_of_sculptures[0];
  for (int64_t index = 1; index < count_of_sculptures; ++index) {
    std::cin >> vector_of_sculptures[index];
    vector_of_sculptures[index] += vector_of_sculptures[index - 1];
  }
  std::cin >> count_of_questions;
  for (int64_t index = 0; index < count_of_questions; ++index) {
    std::cin >> left_border >> right_border;
    if (left_border != 1) {
      std::cout << vector_of_sculptures[right_border - 1] - vector_of_sculptures[left_border - 2] << ' ';
    } else {
      std::cout << vector_of_sculptures[right_border - 1] << ' ';
    }
  }
  return 0;
}