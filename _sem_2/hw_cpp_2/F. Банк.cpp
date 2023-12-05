  #include <iostream>
  #include <string>
  #include <unordered_map>

  int main() {
    std::unordered_map<std::string, int> bank;
    int n, comand, num;
    std::string name;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
      std::cin >> comand;
      if (comand == 1) {
        std::cin >> name >> num;
        if (bank.find(name) != bank.end()) {
          bank[name] += num;
        } else {
          bank[name] = num;
        }
      } else {
        std::cin >> name;
        if (bank.find(name) != bank.end()) {
          std::cout << bank[name] << '\n';
        } else {
          std::cout << "ERROR\n";
        }
      }
    }
  }