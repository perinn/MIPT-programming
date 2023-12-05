#include <iostream>
#include <vector>
#include <string>

struct Node {
  int64_t key = 0;
  int64_t priority = 0;
  int64_t size = 0;
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;

  explicit Node(int64_t);
  int64_t Size(Node*);
  void UpdateSize(Node*);
};

Node::Node(int64_t key) {
  this->key = key;
  this->priority = std::rand();
  this->size = 1;
};

int64_t Size(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->size;
}

void UpdateSize(Node* node) {
  if (node != nullptr) {
    node->size = Size(node->left) + Size(node->right) + 1;
  }
}

class Treap {
  Node* root_ = nullptr;

 public:
  Treap();
  explicit Treap(Node*);
  Node* Merge(Node*, Node*);
  std::pair<Node*, Node*> Split(Node*, int64_t);
  Node* Exists(int64_t);
  Node* Insert(int64_t);
  Node* Delete(Node*, int64_t);
  void Next(int64_t);
  void Prev(int64_t);
  Node* Kth(Node*, int64_t);
  void QueryInsert(int64_t);
  void QueryDelete(int64_t);
  void QueryExists(int64_t);
  void QueryNext(int64_t);
  void QueryPrev(int64_t);
  void QueryKth(int64_t);
};

Treap::Treap() {
  root_ = nullptr;
}

Treap::Treap(Node* root) {
  root_ = root;
}

Node* Treap::Merge(Node* t1, Node* t2) {
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

std::pair<Node*, Node*> Treap::Split(Node* t, int64_t x) {
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

Node* Treap::Exists(int64_t x) {
  if (root_ == nullptr) {
    return nullptr;
  }
  Node* node = root_;
  while (node != nullptr) {
    if (x == node->key) {
      return node;
    }
    if (x > node->key) {
      node = node->right;
    } else {
      node = node->left;
    }
  }
  return nullptr;
}

Node* Treap::Insert(int64_t x) {
  Node* node = new Node(x);
  if (root_ == nullptr) {
    return node;
  }
  std::pair<Node*, Node*> pair = Split(root_, node->key);
  return Merge(Merge(pair.first, node), pair.second);
}

Node* Treap::Delete(Node* node, int64_t x) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->key < x) {
    node->right = Delete(node->right, x);
    UpdateSize(node);
    return node;
  }
  if (node->key > x) {
    node->left = Delete(node->left, x);
    UpdateSize(node);
    return node;
  }
  Node* temp_node = Merge(node->left, node->right);
  delete node;
  return temp_node;
}

void Treap::Next(int64_t x) {
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

void Treap::Prev(int64_t x) {
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

Node* Treap::Kth(Node* node, int64_t x) {
  if (node == nullptr || x >= Size(node)) {
    return nullptr;
  }
  int64_t size = Size(node->left);
  if (size < x) {
    return Kth(node->right, x - static_cast<int64_t>(size) - 1);
  }
  if (Size(node->left) > x) {
    return Kth(node->left, x);
  }
  return node;
}

void Treap::QueryInsert(int64_t x) {
  if (Exists(x) == nullptr) {
    root_ = Insert(x);
  }
}

void Treap::QueryDelete(int64_t x) {
  if (Exists(x) != nullptr) {
    root_ = Delete(root_, x);
  }
}

void Treap::QueryExists(int64_t x) {
  if (Exists(x) != nullptr) {
    std::cout << "true\n";
  } else {
    std::cout << "false\n";
  }
}

void Treap::QueryNext(int64_t x) {
  Next(x);
}

void Treap::QueryPrev(int64_t x) {
  Prev(x);
}

void Treap::QueryKth(int64_t x) {
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

int main() {
  Treap treap = Treap();
  std::string com;
  int64_t x = 0;
  while (std::cin >> com) {
    std::cin >> x;
    if (com == "insert") {
      treap.QueryInsert(x);
    } else if (com == "delete") {
      treap.QueryDelete(x);
    } else if (com == "exists") {
      treap.QueryExists(x);
    } else if (com == "next") {
      treap.QueryNext(x);
    } else if (com == "prev") {
      treap.QueryPrev(x);
    } else if (com == "kth") {
      treap.QueryKth(x);
    }
  }
  return 0;
}