#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct Node {
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  int key = 0;
  int priority = 0;
  int size = 0;

  Node() = default;

  explicit Node(int x) : key(x) {
    priority = std::rand();
    size = 1;
  }
};

int GetSize(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->size;
}

void UpdateSize(Node* node) {
  if (node != nullptr) {
    node->size = GetSize(node->left) + GetSize(node->right) + 1;
  }
}

class Treap {
  Node* root_ = nullptr;

 public:
  Treap() = default;

  explicit Treap(Node* root) : root_(root) {
  }

  Node* Merge(Node* t1, Node* t2) {
    if (t1 == nullptr) {
      return t2;
    }
    if (t2 == nullptr) {
      return t1;
    }
    if (t2->priority < t1->priority) {
      t2->left = Merge(t1, t2->left);
      UpdateSize(t2);
      return t2;
    }
    t1->right = Merge(t1->right, t2);
    UpdateSize(t1);
    return t1;
  }

  std::pair<Node*, Node*> Split(Node* t, const int x) {
    if (t == nullptr) {
      return {nullptr, nullptr};
    }
    if (t->key < x) {
      std::pair<Node*, Node*> pair = Split(t->right, x);
      t->right = pair.first;
      UpdateSize(t);
      return {t, pair.second};
    }
    std::pair<Node*, Node*> pair = Split(t->left, x);
    t->left = pair.second;
    UpdateSize(t);
    return {pair.first, t};
  }

  void ChooseQuery(const std::string& query, const int x) {
    if (query == "insert") {
      if (Exists(x) == nullptr) {
        root_ = Insert(x);
      }
    } else if (query == "delete") {
      if (Exists(x) != nullptr) {
        root_ = Delete(root_, x);
      }
    } else if (query == "exists") {
      if (Exists(x) != nullptr) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
    } else if (query == "next") {
      Next(x);
    } else if (query == "prev") {
      Prev(x);
    } else if (query == "kth") {
      if (x < 0) {
        std::cout << "none\n";
      } else {
        Node* ans = Kth(root_, x);
        if (ans == nullptr) {
          std::cout << "none\n";
        } else {
          std::cout << ans->key << '\n';
        }
      }
    }
  }

  Node* Exists(const int x) {
    if (root_ == nullptr) {
      return nullptr;
    }
    Node* now_node = root_;
    while (now_node != nullptr) {
      if (x == now_node->key) {
        return now_node;
      }
      if (x > now_node->key) {
        now_node = now_node->right;
      } else {
        now_node = now_node->left;
      }
    }
    return nullptr;
  }

  Node* Insert(const int x) {
    Node* node = new Node(x);
    if (root_ == nullptr) {
      return node;
    }
    std::pair<Node*, Node*> pair = Split(root_, node->key);
    return Merge(Merge(pair.first, node), pair.second);
  }

  Node* Delete(Node* now_node, const int x) {
    if (now_node == nullptr) {
      return nullptr;
    }
    if (now_node->key < x) {
      now_node->right = Delete(now_node->right, x);
      UpdateSize(now_node);
      return now_node;
    }
    if (now_node->key > x) {
      now_node->left = Delete(now_node->left, x);
      UpdateSize(now_node);
      return now_node;
    }
    Node* temp_node = Merge(now_node->left, now_node->right);
    delete now_node;
    return temp_node;
  }

  void Next(const int x) {
    Node* cur = root_;
    Node* last = nullptr;
    while (cur != nullptr) {
      if (cur->key > x) {
        last = cur;
        cur = cur->left;
      } else {
        cur = cur->right;
      }
    }
    if (last == nullptr) {
      std::cout << "none\n";
    } else {
      std::cout << last->key << '\n';
    }
  }

  void Prev(const int x) {
    Node* cur = root_;
    Node* last = nullptr;
    while (cur != nullptr) {
      if (cur->key < x) {
        last = cur;
        cur = cur->right;
      } else {
        cur = cur->left;
      }
    }
    if (last == nullptr) {
      std::cout << "none\n";
    } else {
      std::cout << last->key << '\n';
    }
  }
  Node* Kth(Node* now_node, const int x) {
    if (now_node == nullptr || x >= GetSize(now_node)) {
      return nullptr;
    }
    int size = GetSize(now_node->left);
    if (size < x) {
      return Kth(now_node->right, x - static_cast<int>(size) - 1);
    }
    if (GetSize(now_node->left) > x) {
      return Kth(now_node->left, x);
    }
    return now_node;
  }
};

int main() {
  Treap tree;
  std::string command;
  int x = 0;
  while (std::cin >> command) {
    std::cin >> x;
    tree.ChooseQuery(command, x);
  }
  return 0;
}