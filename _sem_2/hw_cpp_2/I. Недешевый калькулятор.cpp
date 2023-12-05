#include <iostream>
#include <queue>

int main() {
  int n, i;
  float ans = 0, first_num, second_num;
  std::priority_queue<float, std::vector<float>, std::greater<float>> priority_queue;
  std::cin >> n;
  for (i = 0; i < n; ++i) {
    std::cin >> first_num;
    priority_queue.push(first_num);
  }
  while (priority_queue.size() > 1) {
    first_num = priority_queue.top();
    priority_queue.pop();
    second_num = priority_queue.top();
    priority_queue.pop();
    ans += (first_num + second_num) * 0.05;
    priority_queue.push(first_num + second_num);
  }
  std::cout << ans;
  return 0;
}