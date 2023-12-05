#include <iostream>
#include <vector>

struct Node {
  int64_t key = 0;
  int64_t priority = 0;
  int64_t idx = 0;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;

  Node(int64_t, int64_t, int64_t);
};

Node::Node(int64_t key, int64_t priority, int64_t idx) {
  this->key = key;
  this->priority = priority;
  this->idx = idx;
}

Node* BuildCertasianTree(std::vector<Node*> arr) {
  auto n = static_cast<int64_t>(arr.size());
  Node* root = arr[0];
  Node* last = root;
  int64_t i = 1;
  while (i < n) {
    Node* cur = last;
    for (; cur && arr[i]->priority < cur->priority;) {
      cur = cur->parent;
    }
    if (cur) {
      arr[i]->left = cur->right;
      if (cur->right) {
        cur->right->parent = arr[i];
      }
      cur->right = arr[i];
      arr[i]->parent = cur;
    } else {
      arr[i]->left = root;
      if (root) {
        root->parent = arr[i];
      }
      root = arr[i];
    }
    last = arr[i];
    ++i;
  }
  return root;
}

void PrintCertasianTree(Node* root) {
  if (root) {
    PrintCertasianTree(root->left);
    std::cout << (root->parent ? root->parent->idx : 0) << " ";
    std::cout << (root->left ? root->left->idx : 0) << " ";
    std::cout << (root->right ? root->right->idx : 0) << "\n";
    PrintCertasianTree(root->right);
  } else {
    return;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t a = 0;
  int64_t b = 0;
  std::cin >> n;
  std::vector<Node*> input(n);
  for (int64_t i = 1; i <= n; ++i) {
    std::cin >> a >> b;
    input[i - 1] = new Node(a, b, i);
  }
  Node* root = BuildCertasianTree(input);
  std::cout << "YES\n";
  PrintCertasianTree(root);
  for (int64_t i = 0; i < n; ++i) {
    delete[] input[i];
  }
  return 0;
}